/* commands.c: see commands.h. The rules follow the C++ runner's commands.cpp. */

#include "commands.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shellapi.h>

#define PATH_BYTES 1024

/* Reads a whole file as text, owned by the caller. Returns an empty string if the file can't be read. */
static char *read_text(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) return _strdup("");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (size < 0) {
        fclose(file);
        return _strdup("");
    }
    char *text = (char *)malloc((size_t)size + 1);
    if (!text) {
        fclose(file);
        return _strdup("");
    }
    size_t read = fread(text, 1, (size_t)size, file);
    text[read] = '\0';
    fclose(file);
    return text;
}

static char *join_path(const char *folder, const char *name) {
    char path[PATH_BYTES];
    snprintf(path, sizeof path, "%s\\%s", folder, name);
    return _strdup(path);
}

/* Source files are C files and their headers, matched without regard to case. */
static int is_source_file(const char *name) {
    const char *dot = strrchr(name, '.');
    if (!dot) return 0;
    return _stricmp(dot, ".c") == 0 || _stricmp(dot, ".h") == 0;
}

/* Adds every source file under a folder, recursively, as a path relative to root with / separators. */
static void collect_sources(const char *root, const char *dir, const char *prefix, cJSON *out) {
    char pattern[PATH_BYTES];
    snprintf(pattern, sizeof pattern, "%s\\*", dir);
    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA(pattern, &data);
    if (find == INVALID_HANDLE_VALUE) return;
    do {
        if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) continue;
        char *full = join_path(dir, data.cFileName);
        if (!full) continue;
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            collect_sources(root, full, prefix, out);
        } else if (is_source_file(data.cFileName)) {
            /* The relative name: the part of full after root, with / separators, prefixed as the caller asks. */
            const char *relative = full + strlen(root);
            if (*relative == '\\') relative++;
            char name[PATH_BYTES];
            snprintf(name, sizeof name, "%s%s", prefix, relative);
            for (char *p = name; *p; p++) {
                if (*p == '\\') *p = '/';
            }
            cJSON_AddItemToArray(out, cJSON_CreateString(name));
        }
        free(full);
    } while (FindNextFileA(find, &data));
    FindClose(find);
}

char *lesson_read_lesson(const char *step) {
    char *path = join_path(step, "lesson.md");
    char *text = path ? read_text(path) : _strdup("");
    free(path);
    return text;
}

char *lesson_read_step_file(const char *step, const char *file) {
    if (strcmp(file, "lesson.md") != 0 && strcmp(file, "solution.md") != 0) return _strdup("");
    char *path = join_path(step, file);
    char *text = path ? read_text(path) : _strdup("");
    free(path);
    return text;
}

cJSON *lesson_read_commands(const char *step) {
    cJSON *commands = cJSON_CreateArray();
    char *path = join_path(step, "commands.txt");
    char *text = path ? read_text(path) : _strdup("");
    free(path);

    char *line = text;
    while (*line) {
        char *end = strchr(line, '\n');
        size_t length = end ? (size_t)(end - line) : strlen(line);
        /* Trim spaces, tabs, and carriage returns, which Windows line endings leave behind. */
        size_t first = 0;
        while (first < length && (line[first] == ' ' || line[first] == '\t' || line[first] == '\r')) first++;
        size_t last = length;
        while (last > first && (line[last - 1] == ' ' || line[last - 1] == '\t' || line[last - 1] == '\r')) last--;
        if (last > first) {
            char *command = (char *)malloc(last - first + 1);
            if (command) {
                memcpy(command, line + first, last - first);
                command[last - first] = '\0';
                cJSON_AddItemToArray(commands, cJSON_CreateString(command));
                free(command);
            }
        }
        if (!end) break;
        line = end + 1;
    }
    free(text);
    return commands;
}

cJSON *lesson_list_source_files(const char *step) {
    cJSON *files = cJSON_CreateArray();
    char *src = join_path(step, "src");
    char *tests = join_path(step, "tests");
    if (src) collect_sources(src, src, "", files);
    if (tests) collect_sources(tests, tests, "tests/", files);
    free(src);
    free(tests);

    /* main.c comes first, then the rest in alphabetical order. */
    int count = cJSON_GetArraySize(files);
    char **names = (char **)calloc(count ? count : 1, sizeof(char *));
    for (int i = 0; i < count; i++) names[i] = _strdup(cJSON_GetArrayItem(files, i)->valuestring);
    cJSON_Delete(files);

    /* A simple insertion sort, with main.c forced to the front. */
    for (int i = 1; i < count; i++) {
        char *current = names[i];
        int j = i;
        while (j > 0) {
            int current_is_main = strcmp(current, "main.c") == 0;
            int previous_is_main = strcmp(names[j - 1], "main.c") == 0;
            int before = (current_is_main && !previous_is_main) ||
                         (current_is_main == previous_is_main && strcmp(current, names[j - 1]) < 0);
            if (!before) break;
            names[j] = names[j - 1];
            j--;
        }
        names[j] = current;
    }

    cJSON *sorted = cJSON_CreateArray();
    for (int i = 0; i < count; i++) {
        cJSON_AddItemToArray(sorted, cJSON_CreateString(names[i]));
        free(names[i]);
    }
    free(names);
    return sorted;
}

int lesson_read_source(const char *step, const char *file, char **out, char *error, size_t error_size) {
    /* Refuse anything that could leave the step's folder, and anything that isn't a source file. */
    int escapes = strstr(file, "..") != NULL || file[0] == '/' || file[0] == '\\';
    if (escapes || !is_source_file(file)) {
        snprintf(error, error_size, "Not a source file: %s", file);
        return 0;
    }

    char full[PATH_BYTES];
    if (strncmp(file, "tests/", 6) == 0) {
        snprintf(full, sizeof full, "%s\\tests\\%s", step, file + 6);
    } else {
        snprintf(full, sizeof full, "%s\\src\\%s", step, file);
    }
    FILE *probe = fopen(full, "rb");
    if (!probe) {
        snprintf(error, error_size, "Could not read %s", full);
        return 0;
    }
    fclose(probe);
    *out = read_text(full);
    return 1;
}

int lesson_open_file(const char *path, const char *work_folder, char *error, size_t error_size) {
    /* Only files the run created may be opened. */
    if (strncmp(path, work_folder, strlen(work_folder)) != 0) {
        snprintf(error, error_size, "Not opening a file outside the run folder: %s", path);
        return 0;
    }
    HINSTANCE result = ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);
    /* ShellExecute returns a value above 32 on success. */
    if ((INT_PTR)result <= 32) {
        snprintf(error, error_size, "Could not open %s", path);
        return 0;
    }
    return 1;
}

int lesson_open_external(const char *url, char *error, size_t error_size) {
    int allowed = strncmp(url, "https://", 8) == 0 || strncmp(url, "http://", 7) == 0 ||
                  strncmp(url, "mailto:", 7) == 0;
    if (!allowed) {
        snprintf(error, error_size, "Not opening %s", url);
        return 0;
    }
    HINSTANCE result = ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    if ((INT_PTR)result <= 32) {
        snprintf(error, error_size, "Could not open %s", url);
        return 0;
    }
    return 1;
}
