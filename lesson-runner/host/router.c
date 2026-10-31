/* router.c: see router.h. The commands follow the C++ runner's router.cpp. */

#include "router.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "discovery.h"

#define PATH_MAX_BYTES 1024

struct LessonRouter {
    char *repo_root;
    LessonRunner *runner;
    LessonEventSink events;
    void *events_context;
    LessonWindowAction window_action;
    void *window_context;
    char *lesson_title;
    char *lesson_text;
    int light;
};

static char *dup_text(const char *text) {
    size_t length = strlen(text);
    char *copy = (char *)malloc(length + 1);
    if (copy) memcpy(copy, text, length + 1);
    return copy;
}

/* A string argument, or NULL when it is missing or isn't a string. */
static const char *string_arg(const cJSON *args, const char *name) {
    const cJSON *item = args ? cJSON_GetObjectItemCaseSensitive(args, name) : NULL;
    return cJSON_IsString(item) ? item->valuestring : NULL;
}

static int bool_arg(const cJSON *args, const char *name, int fallback) {
    const cJSON *item = args ? cJSON_GetObjectItemCaseSensitive(args, name) : NULL;
    if (!item || !cJSON_IsBool(item)) return fallback;
    return cJSON_IsTrue(item);
}

static void emit(LessonRouter *router, const char *name, cJSON *payload) {
    router->events(router->events_context, name, payload);
}

static void set_error(char *error, size_t error_size, const char *message) {
    snprintf(error, error_size, "%s", message);
}

LessonRouter *lesson_router_create(const char *repo_root, LessonRunner *runner, LessonEventSink events,
                                   void *events_context) {
    LessonRouter *router = (LessonRouter *)calloc(1, sizeof *router);
    if (!router) return NULL;
    router->repo_root = dup_text(repo_root);
    router->runner = runner;
    router->events = events;
    router->events_context = events_context;
    router->lesson_title = dup_text("");
    router->lesson_text = dup_text("");
    return router;
}

void lesson_router_destroy(LessonRouter *router) {
    if (!router) return;
    free(router->repo_root);
    free(router->lesson_title);
    free(router->lesson_text);
    free(router);
}

void lesson_router_set_window_action(LessonRouter *router, LessonWindowAction action, void *context) {
    router->window_action = action;
    router->window_context = context;
}

/* The lesson-listing commands, which read the repository. */
static cJSON *list_chapters(const char *root) {
    LessonChapters chapters = lesson_discover(root);
    cJSON *array = cJSON_CreateArray();
    for (size_t i = 0; i < chapters.count; i++) {
        cJSON_AddItemToArray(array, lesson_chapter_to_json(&chapters.chapters[i]));
    }
    lesson_free_chapters(&chapters);
    return array;
}

static cJSON *run_step(LessonRouter *router, const cJSON *args, char *error, size_t error_size) {
    const char *path = string_arg(args, "path");
    if (!path) {
        set_error(error, error_size, "Missing argument: path");
        return NULL;
    }

    RunRequest *request = (RunRequest *)calloc(1, sizeof *request);
    if (!request) {
        set_error(error, error_size, "Out of memory.");
        return NULL;
    }
    request->step = dup_text(path);
    const char *source = string_arg(args, "source");
    request->source = source ? dup_text(source) : NULL;
    request->backtrace = bool_arg(args, "backtrace", 0);
    request->test = bool_arg(args, "test", 0);

    /* The page's option checkboxes: an object of name to true or false. */
    const cJSON *options = cJSON_GetObjectItemCaseSensitive(args, "options");
    if (cJSON_IsObject(options)) {
        size_t count = 0;
        for (const cJSON *option = options->child; option; option = option->next) count++;
        request->option_names = (char **)calloc(count ? count : 1, sizeof(char *));
        request->option_values = (int *)calloc(count ? count : 1, sizeof(int));
        for (const cJSON *option = options->child; option; option = option->next) {
            if (!cJSON_IsBool(option)) {
                lesson_free_request(request);
                free(request);
                set_error(error, error_size, "Each option must be true or false.");
                return NULL;
            }
            request->option_names[request->option_count] = dup_text(option->string);
            request->option_values[request->option_count] = cJSON_IsTrue(option);
            request->option_count++;
        }
    }

    /* The arguments for the program, as an array of strings. */
    const cJSON *arguments = cJSON_GetObjectItemCaseSensitive(args, "args");
    if (cJSON_IsArray(arguments)) {
        int count = cJSON_GetArraySize(arguments);
        request->args = (char **)calloc(count ? count : 1, sizeof(char *));
        for (int i = 0; i < count; i++) {
            const cJSON *arg = cJSON_GetArrayItem(arguments, i);
            if (!cJSON_IsString(arg)) {
                lesson_free_request(request);
                free(request);
                set_error(error, error_size, "Each argument must be text.");
                return NULL;
            }
            request->args[request->arg_count++] = dup_text(arg->valuestring);
        }
    }

    /* lesson_runner_start takes ownership of the request, even when it fails. */
    if (lesson_runner_start(router->runner, request, error, error_size) != 0) return NULL;
    return cJSON_CreateNull();
}

cJSON *lesson_router_handle(LessonRouter *router, const char *command, const cJSON *args, char *error,
                            size_t error_size) {
    /* Lesson and step reading. */
    if (strcmp(command, "list_parts") == 0) {
        return lesson_list_parts(router->repo_root);
    }
    if (strcmp(command, "list_chapters") == 0) {
        return list_chapters(router->repo_root);
    }
    if (strcmp(command, "read_lesson") == 0 || strcmp(command, "read_step_file") == 0 ||
        strcmp(command, "read_commands") == 0 || strcmp(command, "list_source_files") == 0 ||
        strcmp(command, "read_source") == 0) {
        const char *path = string_arg(args, "path");
        if (!path) {
            set_error(error, error_size, "Missing argument: path");
            return NULL;
        }
        if (strcmp(command, "read_lesson") == 0) {
            char *text = lesson_read_lesson(path);
            cJSON *reply = cJSON_CreateString(text);
            free(text);
            return reply;
        }
        if (strcmp(command, "read_commands") == 0) return lesson_read_commands(path);
        if (strcmp(command, "list_source_files") == 0) return lesson_list_source_files(path);

        const char *file = string_arg(args, "file");
        if (!file) {
            set_error(error, error_size, "Missing argument: file");
            return NULL;
        }
        if (strcmp(command, "read_step_file") == 0) {
            char *text = lesson_read_step_file(path, file);
            cJSON *reply = cJSON_CreateString(text);
            free(text);
            return reply;
        }
        char *text = NULL;
        if (!lesson_read_source(path, file, &text, error, error_size)) return NULL;
        cJSON *reply = cJSON_CreateString(text);
        free(text);
        return reply;
    }

    /* The lesson on screen, which the pop-out window reads. */
    if (strcmp(command, "set_lesson") == 0) {
        const char *title = string_arg(args, "title");
        const char *text = string_arg(args, "text");
        if (!title || !text) {
            set_error(error, error_size, "Missing argument: title or text");
            return NULL;
        }
        free(router->lesson_title);
        free(router->lesson_text);
        router->lesson_title = dup_text(title);
        router->lesson_text = dup_text(text);
        cJSON *payload = cJSON_CreateObject();
        cJSON_AddStringToObject(payload, "title", title);
        cJSON_AddStringToObject(payload, "text", text);
        emit(router, "lesson-updated", payload);
        return cJSON_CreateNull();
    }
    if (strcmp(command, "get_lesson") == 0) {
        cJSON *reply = cJSON_CreateObject();
        cJSON_AddStringToObject(reply, "title", router->lesson_title);
        cJSON_AddStringToObject(reply, "text", router->lesson_text);
        return reply;
    }

    /* Theme, shared by every window. */
    if (strcmp(command, "set_theme") == 0) {
        router->light = bool_arg(args, "light", 0);
        emit(router, "theme-changed", cJSON_CreateBool(router->light));
        return cJSON_CreateNull();
    }
    if (strcmp(command, "get_theme") == 0) {
        return cJSON_CreateBool(router->light);
    }

    /* Links: #goto/ jumps are sent to the page, and web and mail links open in the browser. */
    if (strcmp(command, "navigate_to") == 0) {
        const char *name = string_arg(args, "name");
        if (!name) {
            set_error(error, error_size, "Missing argument: name");
            return NULL;
        }
        emit(router, "goto", cJSON_CreateString(name));
        return cJSON_CreateNull();
    }
    if (strcmp(command, "open_visualizer") == 0) {
        /* The visualizer is copied into the run's work folder on each run, so it is opened from there. */
        const char *path = string_arg(args, "path");
        if (!path) {
            set_error(error, error_size, "Missing argument: path");
            return NULL;
        }
        char work[PATH_MAX_BYTES];
        lesson_work_root(router->repo_root, work, sizeof work);
        const char *step_name = strrchr(path, '\\');
        step_name = step_name ? step_name + 1 : path;
        char page[PATH_MAX_BYTES * 2];
        snprintf(page, sizeof page, "%s\\%s\\visualize.html", work, step_name);
        if (GetFileAttributesA(page) == INVALID_FILE_ATTRIBUTES) {
            set_error(error, error_size, "Run this step once, so its trace is written, then press Visualize.");
            return NULL;
        }
        if (!lesson_open_file(page, work, error, error_size)) return NULL;
        return cJSON_CreateNull();
    }
    if (strcmp(command, "open_file") == 0) {
        const char *path = string_arg(args, "path");
        if (!path) {
            set_error(error, error_size, "Missing argument: path");
            return NULL;
        }
        char work[PATH_MAX_BYTES];
        lesson_work_root(router->repo_root, work, sizeof work);
        if (!lesson_open_file(path, work, error, error_size)) return NULL;
        return cJSON_CreateNull();
    }
    if (strcmp(command, "open_external") == 0) {
        const char *url = string_arg(args, "url");
        if (!url) {
            set_error(error, error_size, "Missing argument: url");
            return NULL;
        }
        if (!lesson_open_external(url, error, error_size)) return NULL;
        return cJSON_CreateNull();
    }

    /* Window actions. */
    if (strcmp(command, "open_lesson_window") == 0 || strcmp(command, "dock_lesson") == 0) {
        if (router->window_action) {
            router->window_action(router->window_context,
                                  strcmp(command, "open_lesson_window") == 0 ? "open" : "dock");
        }
        return cJSON_CreateNull();
    }

    /* Runs. */
    if (strcmp(command, "run_step") == 0) return run_step(router, args, error, error_size);
    if (strcmp(command, "send_input") == 0) {
        const char *text = string_arg(args, "text");
        if (!text) {
            set_error(error, error_size, "Missing argument: text");
            return NULL;
        }
        if (lesson_runner_send_input(router->runner, text, error, error_size) != 0) return NULL;
        return cJSON_CreateNull();
    }
    if (strcmp(command, "stop_run") == 0) {
        lesson_runner_stop(router->runner);
        return cJSON_CreateNull();
    }

    snprintf(error, error_size, "Unknown command: %s", command);
    return NULL;
}
