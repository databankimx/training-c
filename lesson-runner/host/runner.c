/* runner.c: see runner.h. The phases, messages, and rules follow the C++ runner's runner.cpp. */

#include "runner.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Where cmake, ninja, and gcc are installed, from MSYS2's UCRT64 environment. */
#define TOOLCHAIN_BIN "C:\\msys64\\ucrt64\\bin"
#define PATH_BYTES 1024

/* ---- Strings and paths ------------------------------------------------------------------------- */

static char *dup_text(const char *text) {
    size_t length = strlen(text);
    char *copy = (char *)malloc(length + 1);
    if (copy) memcpy(copy, text, length + 1);
    return copy;
}

static char *join_path(const char *folder, const char *name) {
    size_t folder_length = strlen(folder);
    size_t name_length = strlen(name);
    char *joined = (char *)malloc(folder_length + name_length + 2);
    if (!joined) return NULL;
    memcpy(joined, folder, folder_length);
    joined[folder_length] = '\\';
    memcpy(joined + folder_length + 1, name, name_length + 1);
    return joined;
}

/* The last part of a path: the step's folder name. Points into the path, so it is not freed. */
static const char *base_name(const char *path) {
    const char *slash = strrchr(path, '\\');
    return slash ? slash + 1 : path;
}

/* Creates a folder and any missing parents above it. */
static void make_folders(const char *path) {
    char buffer[PATH_BYTES];
    snprintf(buffer, sizeof buffer, "%s", path);
    for (char *p = buffer + 1; *p; p++) {
        if (*p == '\\') {
            *p = '\0';
            CreateDirectoryA(buffer, NULL);
            *p = '\\';
        }
    }
    CreateDirectoryA(buffer, NULL);
}

/* A growing text buffer, used to build command lines. */
typedef struct {
    char *text;
    size_t length;
    size_t capacity;
} Buffer;

static void buffer_append(Buffer *buffer, const char *text) {
    size_t needed = buffer->length + strlen(text) + 1;
    if (needed > buffer->capacity) {
        size_t capacity = buffer->capacity ? buffer->capacity : 256;
        while (capacity < needed) capacity *= 2;
        char *grown = (char *)realloc(buffer->text, capacity);
        if (!grown) return;
        buffer->text = grown;
        buffer->capacity = capacity;
        if (buffer->length == 0) buffer->text[0] = '\0';
    }
    strcat(buffer->text, text);
    buffer->length += strlen(text);
}

/* NAME=value, where NAME is a plain identifier, such as IGNORE_CASE=1. */
static int is_assignment(const char *arg) {
    const char *equals = strchr(arg, '=');
    if (!equals || equals == arg) return 0;
    if (isdigit((unsigned char)arg[0])) return 0;
    for (const char *p = arg; p < equals; p++) {
        if (!(isalnum((unsigned char)*p) || *p == '_')) return 0;
    }
    return 1;
}

/* ---- Runner state ------------------------------------------------------------------------------ */

struct LessonRunner {
    HWND window;
    char *repo_root;
    CRITICAL_SECTION lock; /* guards the event queue, the job, and the input pipe */
    LessonEvent *events_head;
    LessonEvent *events_tail;
    HANDLE job;            /* the running process's job object, or NULL */
    HANDLE input;          /* the running program's input pipe, or NULL */
    volatile LONG running;
    volatile LONG cancelled;
    HANDLE worker;
};

/* Everything a worker thread needs: the runner, the request, and the environment variables for this run. */
typedef struct {
    LessonRunner *runner;
    RunRequest *request;
    char **env_names;
    char **env_values;
    size_t env_count;
} WorkerContext;

/* ---- Events ------------------------------------------------------------------------------------ */

static void emit(LessonRunner *runner, const char *name, cJSON *payload) {
    LessonEvent *event = (LessonEvent *)malloc(sizeof *event);
    if (!event) {
        cJSON_Delete(payload);
        return;
    }
    event->name = dup_text(name);
    event->payload = payload;
    event->next = NULL;

    EnterCriticalSection(&runner->lock);
    if (runner->events_tail) {
        runner->events_tail->next = event;
    } else {
        runner->events_head = event;
    }
    runner->events_tail = event;
    LeaveCriticalSection(&runner->lock);

    /* The window's thread sends queued events to the page, so the page is only touched there. */
    PostMessageA(runner->window, LESSON_RUNNER_EVENTS_MESSAGE, 0, 0);
}

/* Output text, which may contain any bytes, is copied into a NUL-terminated string first. */
static void emit_output(LessonRunner *runner, const char *stream, const char *bytes, size_t length) {
    char *text = (char *)malloc(length + 1);
    if (!text) return;
    memcpy(text, bytes, length);
    text[length] = '\0';
    cJSON *payload = cJSON_CreateObject();
    cJSON_AddStringToObject(payload, "stream", stream);
    cJSON_AddStringToObject(payload, "text", text);
    free(text);
    emit(runner, "run-output", payload);
}

static void emit_status(LessonRunner *runner, const char *line) {
    char text[1024];
    snprintf(text, sizeof text, "%s\n", line);
    emit_output(runner, "stdout", text, strlen(text));
}

static void emit_error(LessonRunner *runner, const char *message, DWORD error) {
    char text[1024];
    snprintf(text, sizeof text, "%s (error %lu)\n", message, (unsigned long)error);
    emit_output(runner, "stderr", text, strlen(text));
}

/* The run is over. A null code means the run was stopped on purpose. */
static void finish(LessonRunner *runner, int has_code, DWORD code) {
    cJSON *payload = cJSON_CreateObject();
    if (has_code) {
        cJSON_AddNumberToObject(payload, "code", (double)(int)code);
    } else {
        cJSON_AddNullToObject(payload, "code");
    }
    InterlockedExchange(&runner->running, 0);
    emit(runner, "run-finished", payload);
}

/* ---- Files: copying the step, and finding what a run changed ------------------------------------ */

static void copy_tree(const char *source, const char *target, int skip_build) {
    make_folders(target);
    char pattern[PATH_BYTES];
    snprintf(pattern, sizeof pattern, "%s\\*", source);
    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA(pattern, &data);
    if (find == INVALID_HANDLE_VALUE) return;
    do {
        if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) continue;
        if (skip_build && strcmp(data.cFileName, "build") == 0) continue;
        char *from = join_path(source, data.cFileName);
        char *to = join_path(target, data.cFileName);
        if (from && to) {
            if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                copy_tree(from, to, 0);
            } else {
                CopyFileA(from, to, FALSE);
            }
        }
        free(from);
        free(to);
    } while (FindNextFileA(find, &data));
    FindClose(find);
}

/* The work folder for a step: <repo>\.lesson-runner\work\<step name>. Returned as a new string. */
static char *work_folder_for(const LessonRunner *runner, const char *step) {
    char folder[PATH_BYTES];
    snprintf(folder, sizeof folder, "%s\\.lesson-runner\\work\\%s", runner->repo_root, base_name(step));
    return dup_text(folder);
}

/* Copies the step to the work folder, without its build folder, and writes the edited main.c into it. */
static char *prepare_work_copy(const LessonRunner *runner, const RunRequest *request) {
    char *work = work_folder_for(runner, request->step);
    if (!work) return NULL;
    copy_tree(request->step, work, 1);
    if (request->source) {
        char *src = join_path(work, "src");
        make_folders(src);
        char *path = join_path(src, "main.c");
        FILE *file = path ? fopen(path, "wb") : NULL;
        if (file) {
            fwrite(request->source, 1, strlen(request->source), file);
            fclose(file);
        }
        free(path);
        free(src);
    }
    return work;
}

typedef struct {
    char *path;
    FILETIME time;
} FileEntry;

typedef struct {
    FileEntry *items;
    size_t count;
} Snapshot;

static void snapshot_add(Snapshot *snapshot, const char *path, FILETIME time) {
    FileEntry *grown = (FileEntry *)realloc(snapshot->items, (snapshot->count + 1) * sizeof(FileEntry));
    if (!grown) return;
    snapshot->items = grown;
    snapshot->items[snapshot->count].path = dup_text(path);
    snapshot->items[snapshot->count].time = time;
    snapshot->count++;
}

/* Every file under a folder, recursively. The build folder at the top is skipped, since it holds compiler output. */
static void snapshot_walk(Snapshot *snapshot, const char *folder, int depth) {
    char pattern[PATH_BYTES];
    snprintf(pattern, sizeof pattern, "%s\\*", folder);
    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA(pattern, &data);
    if (find == INVALID_HANDLE_VALUE) return;
    do {
        if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) continue;
        char *path = join_path(folder, data.cFileName);
        if (!path) continue;
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (!(depth == 0 && strcmp(data.cFileName, "build") == 0)) snapshot_walk(snapshot, path, depth + 1);
        } else {
            snapshot_add(snapshot, path, data.ftLastWriteTime);
        }
        free(path);
    } while (FindNextFileA(find, &data));
    FindClose(find);
}

static void snapshot_free(Snapshot *snapshot) {
    for (size_t i = 0; i < snapshot->count; i++) free(snapshot->items[i].path);
    free(snapshot->items);
    snapshot->items = NULL;
    snapshot->count = 0;
}

/* The files a run created or changed, as a JSON array of { name, path } objects. */
static cJSON *changed_files(const Snapshot *before, const Snapshot *after) {
    cJSON *changed = cJSON_CreateArray();
    for (size_t i = 0; i < after->count; i++) {
        const FileEntry *now = &after->items[i];
        int unchanged = 0;
        for (size_t j = 0; j < before->count; j++) {
            if (strcmp(before->items[j].path, now->path) == 0) {
                unchanged = CompareFileTime(&before->items[j].time, &now->time) == 0;
                break;
            }
        }
        if (!unchanged) {
            cJSON *entry = cJSON_CreateObject();
            cJSON_AddStringToObject(entry, "name", base_name(now->path));
            cJSON_AddStringToObject(entry, "path", now->path);
            cJSON_AddItemToArray(changed, entry);
        }
    }
    return changed;
}

/* ---- Running a process ------------------------------------------------------------------------- */

typedef struct {
    LessonRunner *runner;
    HANDLE pipe;
    const char *stream;
} PumpArgs;

/* Reads a pipe until the program closes it, and queues each piece of output. */
static DWORD WINAPI pump_main(LPVOID arg) {
    PumpArgs *args = (PumpArgs *)arg;
    char buffer[4096];
    DWORD read = 0;
    while (ReadFile(args->pipe, buffer, sizeof buffer, &read, NULL) && read > 0) {
        emit_output(args->runner, args->stream, buffer, read);
    }
    return 0;
}

/* Runs one process with its output on pipes, and waits for it. Returns 1 and its exit code if it ran, or 0 if it
 * couldn't start, after reporting why. When interactive, its standard input is a pipe that send_input writes to. */
static int run_child(LessonRunner *runner, const char *command, const char *folder, int interactive, const char *what,
                     DWORD *exit_code) {
    SECURITY_ATTRIBUTES inherit = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    HANDLE out_read = NULL, out_write = NULL, err_read = NULL, err_write = NULL;
    HANDLE in_read = NULL, in_write = NULL;
    HANDLE job = NULL;
    HANDLE out_thread = NULL, err_thread = NULL;
    PROCESS_INFORMATION process;
    STARTUPINFOA startup;
    int started = 0;

    if (!CreatePipe(&out_read, &out_write, &inherit, 0)) {
        emit_error(runner, "Could not create the output pipe.", GetLastError());
        goto cleanup;
    }
    SetHandleInformation(out_read, HANDLE_FLAG_INHERIT, 0);
    if (!CreatePipe(&err_read, &err_write, &inherit, 0)) {
        emit_error(runner, "Could not create the error pipe.", GetLastError());
        goto cleanup;
    }
    SetHandleInformation(err_read, HANDLE_FLAG_INHERIT, 0);
    if (interactive) {
        if (!CreatePipe(&in_read, &in_write, &inherit, 0)) {
            emit_error(runner, "Could not create the input pipe.", GetLastError());
            goto cleanup;
        }
        SetHandleInformation(in_write, HANDLE_FLAG_INHERIT, 0);
    } else {
        in_read = CreateFileA("NUL", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, &inherit, OPEN_EXISTING, 0, NULL);
        if (in_read == INVALID_HANDLE_VALUE) {
            in_read = NULL;
            emit_error(runner, "Could not open the input.", GetLastError());
            goto cleanup;
        }
    }

    /* A job object holds the process and anything it starts. Stop ends the job, which ends the whole tree. */
    job = CreateJobObjectA(NULL, NULL);
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION limits;
    memset(&limits, 0, sizeof limits);
    limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
    SetInformationJobObject(job, JobObjectExtendedLimitInformation, &limits, sizeof limits);

    memset(&startup, 0, sizeof startup);
    startup.cb = sizeof startup;
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = in_read;
    startup.hStdOutput = out_write;
    startup.hStdError = err_write;

    /* CreateProcess may change its command line buffer, so it gets a copy. */
    char *line = dup_text(command);
    started = line && CreateProcessA(NULL, line, NULL, NULL, TRUE, CREATE_SUSPENDED | CREATE_NO_WINDOW, NULL,
                                     folder, &startup, &process);
    DWORD start_error = GetLastError();
    free(line);
    if (!started) {
        char message[512];
        if (interactive) {
            snprintf(message, sizeof message,
                     "Windows would not start %s. It was built, but security software may have blocked or removed it. "
                     "See the troubleshooting section of QUICKSTART",
                     what);
        } else {
            snprintf(message, sizeof message,
                     "Could not start %s. Is the toolchain installed in C:\\msys64\\ucrt64?", what);
        }
        emit_error(runner, message, start_error);
        goto cleanup;
    }

    /* The child has its own copies of these ends now, so this process closes its copies. */
    CloseHandle(out_write);
    out_write = NULL;
    CloseHandle(err_write);
    err_write = NULL;
    CloseHandle(in_read);
    in_read = NULL;

    AssignProcessToJobObject(job, process.hProcess);
    ResumeThread(process.hThread);
    CloseHandle(process.hThread);

    EnterCriticalSection(&runner->lock);
    runner->job = job;
    runner->input = interactive ? in_write : NULL;
    LeaveCriticalSection(&runner->lock);
    /* Stop may have been asked for before the job was recorded, so it is checked again here. */
    if (InterlockedCompareExchange(&runner->cancelled, 0, 0)) TerminateJobObject(job, 1);

    PumpArgs out_args = {runner, out_read, "stdout"};
    PumpArgs err_args = {runner, err_read, "stderr"};
    out_thread = CreateThread(NULL, 0, pump_main, &out_args, 0, NULL);
    err_thread = CreateThread(NULL, 0, pump_main, &err_args, 0, NULL);

    WaitForSingleObject(process.hProcess, INFINITE);
    GetExitCodeProcess(process.hProcess, exit_code);
    CloseHandle(process.hProcess);

    if (out_thread) {
        WaitForSingleObject(out_thread, INFINITE);
        CloseHandle(out_thread);
    }
    if (err_thread) {
        WaitForSingleObject(err_thread, INFINITE);
        CloseHandle(err_thread);
    }

    EnterCriticalSection(&runner->lock);
    runner->job = NULL;
    runner->input = NULL;
    LeaveCriticalSection(&runner->lock);

cleanup:
    if (out_write) CloseHandle(out_write);
    if (err_write) CloseHandle(err_write);
    if (in_read) CloseHandle(in_read);
    if (in_write) CloseHandle(in_write);
    if (out_read) CloseHandle(out_read);
    if (err_read) CloseHandle(err_read);
    if (job) CloseHandle(job);
    return started;
}

/* ---- The run ------------------------------------------------------------------------------------ */

/* Reports a phase that failed, or a run that was stopped. Returns 1 when the run is over. */
static int phase_over(LessonRunner *runner, int started, DWORD code) {
    if (InterlockedCompareExchange(&runner->cancelled, 0, 0)) {
        finish(runner, 0, 0);
        return 1;
    }
    if (!started || code != 0) {
        finish(runner, 1, started ? code : 1);
        return 1;
    }
    return 0;
}

static void work(LessonRunner *runner, const WorkerContext *context) {
    const RunRequest *request = context->request;

    char *folder = prepare_work_copy(runner, request);
    if (!folder) {
        emit_error(runner, "Could not prepare the work folder.", GetLastError());
        finish(runner, 1, 1);
        return;
    }
    char *build = join_path(folder, "build");

    /* Configure: the same options the C++ runner passes, plus the page's option checkboxes. */
    emit_status(runner, "Configuring...");
    Buffer configure = {NULL, 0, 0};
    buffer_append(&configure, "cmake -S \"");
    buffer_append(&configure, folder);
    buffer_append(&configure, "\" -B \"");
    buffer_append(&configure, build);
    buffer_append(&configure, "\" -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -DLESSON_BACKTRACE=");
    buffer_append(&configure, request->backtrace ? "ON" : "OFF");
    for (size_t i = 0; i < request->option_count; i++) {
        buffer_append(&configure, " -D");
        buffer_append(&configure, request->option_names[i]);
        buffer_append(&configure, request->option_values[i] ? "=ON" : "=OFF");
    }
    DWORD code = 0;
    int started = run_child(runner, configure.text ? configure.text : "", folder, 0, "CMake", &code);
    free(configure.text);
    if (phase_over(runner, started, code)) goto done;

    emit_status(runner, "Building...");
    Buffer build_command = {NULL, 0, 0};
    buffer_append(&build_command, "cmake --build \"");
    buffer_append(&build_command, build);
    buffer_append(&build_command, "\"");
    started = run_child(runner, build_command.text ? build_command.text : "", folder, 0, "CMake", &code);
    free(build_command.text);
    if (phase_over(runner, started, code)) goto done;

    if (request->test) {
        emit_status(runner, "Testing...");
        Buffer test_command = {NULL, 0, 0};
        buffer_append(&test_command, "ctest --test-dir \"");
        buffer_append(&test_command, build);
        buffer_append(&test_command, "\" --output-on-failure");
        started = run_child(runner, test_command.text ? test_command.text : "", folder, 0, "CTest", &code);
        free(test_command.text);
        if (InterlockedCompareExchange(&runner->cancelled, 0, 0)) {
            finish(runner, 0, 0);
        } else {
            finish(runner, 1, started ? code : 1);
        }
        goto done;
    }

    char *program = join_path(build, "program.exe");
    if (!program || GetFileAttributesA(program) == INVALID_FILE_ATTRIBUTES) {
        static const char kNoProgram[] = "This step didn't build a program. Its CMakeLists.txt should build an executable "
                                         "named program.\n";
        emit_output(runner, "stderr", kNoProgram, sizeof kNoProgram - 1);
        free(program);
        finish(runner, 1, 1);
        goto done;
    }

    Buffer command = {NULL, 0, 0};
    buffer_append(&command, "\"");
    buffer_append(&command, program);
    buffer_append(&command, "\"");
    for (size_t i = 0; i < request->arg_count; i++) {
        buffer_append(&command, " \"");
        buffer_append(&command, request->args[i]);
        buffer_append(&command, "\"");
    }

    for (size_t i = 0; i < context->env_count; i++) {
        SetEnvironmentVariableA(context->env_names[i], context->env_values[i]);
    }

    Snapshot before = {NULL, 0};
    snapshot_walk(&before, folder, 0);
    emit_status(runner, "Running program.exe");
    /* A blank line sets the program's output off from the build lines above it. */
    emit_output(runner, "stdout", "\n", 1);
    started = run_child(runner, command.text ? command.text : "", folder, 1, "program.exe", &code);
    free(command.text);

    for (size_t i = 0; i < context->env_count; i++) SetEnvironmentVariableA(context->env_names[i], NULL);

    /* Files the program created or changed are offered to the page, to open in their default application. */
    Snapshot after = {NULL, 0};
    snapshot_walk(&after, folder, 0);
    emit(runner, "output-files", changed_files(&before, &after));
    snapshot_free(&before);
    snapshot_free(&after);

    if (InterlockedCompareExchange(&runner->cancelled, 0, 0)) {
        finish(runner, 0, 0);
    } else {
        finish(runner, 1, started ? code : 1);
    }

done:
    free(build);
    free(folder);
}

static DWORD WINAPI worker_main(LPVOID arg) {
    WorkerContext *context = (WorkerContext *)arg;
    work(context->runner, context);
    for (size_t i = 0; i < context->env_count; i++) {
        free(context->env_names[i]);
        free(context->env_values[i]);
    }
    free(context->env_names);
    free(context->env_values);
    lesson_free_request(context->request);
    free(context->request);
    free(context);
    return 0;
}

/* ---- Public functions -------------------------------------------------------------------------- */

LessonRunner *lesson_runner_create(HWND window, const char *repo_root) {
    LessonRunner *runner = (LessonRunner *)calloc(1, sizeof *runner);
    if (!runner) return NULL;
    runner->window = window;
    runner->repo_root = dup_text(repo_root);
    InitializeCriticalSection(&runner->lock);

    /* Every child process finds the build tools on PATH, so the toolchain folder goes first. */
    DWORD size = GetEnvironmentVariableA("PATH", NULL, 0);
    char *current = (char *)calloc(size ? size : 1, 1);
    if (current && size > 0) GetEnvironmentVariableA("PATH", current, size);
    size_t length = strlen(TOOLCHAIN_BIN) + 1 + strlen(current ? current : "") + 1;
    char *path = (char *)malloc(length);
    if (path) {
        snprintf(path, length, "%s;%s", TOOLCHAIN_BIN, current ? current : "");
        SetEnvironmentVariableA("PATH", path);
        free(path);
    }
    free(current);
    return runner;
}

void lesson_runner_destroy(LessonRunner *runner) {
    if (!runner) return;
    lesson_runner_stop(runner);
    if (runner->worker) {
        WaitForSingleObject(runner->worker, INFINITE);
        CloseHandle(runner->worker);
    }
    DeleteCriticalSection(&runner->lock);
    lesson_free_events(runner->events_head);
    free(runner->repo_root);
    free(runner);
}

int lesson_runner_start(LessonRunner *runner, RunRequest *request, char *error, size_t error_size) {
    if (InterlockedCompareExchange(&runner->running, 1, 0) != 0) {
        snprintf(error, error_size, "A program is already running. Stop it first.");
        lesson_free_request(request);
        free(request);
        return 1;
    }
    /* The previous run has finished, so its thread can be waited for before a new one starts. */
    if (runner->worker) {
        WaitForSingleObject(runner->worker, INFINITE);
        CloseHandle(runner->worker);
        runner->worker = NULL;
    }

    /* Leading NAME=value items set environment variables for this run only. They are removed from the arguments. */
    WorkerContext *context = (WorkerContext *)calloc(1, sizeof *context);
    if (!context) {
        InterlockedExchange(&runner->running, 0);
        lesson_free_request(request);
        free(request);
        snprintf(error, error_size, "Out of memory.");
        return 1;
    }
    size_t split = 0;
    while (split < request->arg_count && is_assignment(request->args[split])) split++;
    context->env_count = split;
    context->env_names = (char **)calloc(split ? split : 1, sizeof(char *));
    context->env_values = (char **)calloc(split ? split : 1, sizeof(char *));
    for (size_t i = 0; i < split; i++) {
        char *arg = request->args[i];
        char *equals = strchr(arg, '=');
        *equals = '\0';
        context->env_names[i] = dup_text(arg);
        context->env_values[i] = dup_text(equals + 1);
        free(arg);
    }
    memmove(request->args, request->args + split, (request->arg_count - split) * sizeof(char *));
    request->arg_count -= split;

    InterlockedExchange(&runner->cancelled, 0);
    context->runner = runner;
    context->request = request;
    runner->worker = CreateThread(NULL, 0, worker_main, context, 0, NULL);
    if (!runner->worker) {
        InterlockedExchange(&runner->running, 0);
        snprintf(error, error_size, "Could not start the run.");
        return 1;
    }
    return 0;
}

void lesson_runner_stop(LessonRunner *runner) {
    InterlockedExchange(&runner->cancelled, 1);
    EnterCriticalSection(&runner->lock);
    if (runner->job) TerminateJobObject(runner->job, 1);
    LeaveCriticalSection(&runner->lock);
}

int lesson_runner_send_input(LessonRunner *runner, const char *text, char *error, size_t error_size) {
    EnterCriticalSection(&runner->lock);
    if (!runner->input) {
        LeaveCriticalSection(&runner->lock);
        snprintf(error, error_size, "No program is running.");
        return 1;
    }
    DWORD written = 0;
    int ok = WriteFile(runner->input, text, (DWORD)strlen(text), &written, NULL);
    LeaveCriticalSection(&runner->lock);
    if (!ok) {
        snprintf(error, error_size, "The program has stopped reading input.");
        return 1;
    }
    return 0;
}

LessonEvent *lesson_runner_take_events(LessonRunner *runner) {
    EnterCriticalSection(&runner->lock);
    LessonEvent *head = runner->events_head;
    runner->events_head = NULL;
    runner->events_tail = NULL;
    LeaveCriticalSection(&runner->lock);
    return head;
}

void lesson_free_events(LessonEvent *events) {
    while (events) {
        LessonEvent *next = events->next;
        free(events->name);
        cJSON_Delete(events->payload);
        free(events);
        events = next;
    }
}

void lesson_free_request(RunRequest *request) {
    free(request->step);
    free(request->source);
    for (size_t i = 0; i < request->arg_count; i++) free(request->args[i]);
    free(request->args);
    for (size_t i = 0; i < request->option_count; i++) free(request->option_names[i]);
    free(request->option_names);
    free(request->option_values);
    memset(request, 0, sizeof *request);
}
