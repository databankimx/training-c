/* discovery.c: see discovery.h. The rules follow the C++ runner's discovery.cpp. */

#include "discovery.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define EXTRA_CHAPTER_NUMBER 1000u
#define MAX_PATH_BYTES 1024

/* ---- Small string helpers -------------------------------------------------------------------- */

static char *xstrdup(const char *text) {
    size_t length = strlen(text);
    char *copy = (char *)malloc(length + 1);
    if (copy) memcpy(copy, text, length + 1);
    return copy;
}

static char *xstrndup(const char *text, size_t length) {
    char *copy = (char *)malloc(length + 1);
    if (copy) {
        memcpy(copy, text, length);
        copy[length] = '\0';
    }
    return copy;
}

/* Joins a folder and a name with a backslash. The result is owned by the caller. */
static char *path_join(const char *folder, const char *name) {
    size_t folder_length = strlen(folder);
    size_t name_length = strlen(name);
    char *joined = (char *)malloc(folder_length + name_length + 2);
    if (!joined) return NULL;
    memcpy(joined, folder, folder_length);
    joined[folder_length] = '\\';
    memcpy(joined + folder_length + 1, name, name_length + 1);
    return joined;
}

static int starts_with(const char *text, const char *prefix) {
    return strncmp(text, prefix, strlen(prefix)) == 0;
}

static int ends_with(const char *text, const char *suffix) {
    size_t text_length = strlen(text);
    size_t suffix_length = strlen(suffix);
    return text_length >= suffix_length && _stricmp(text + text_length - suffix_length, suffix) == 0;
}

static int contains(const char *text, const char *needle) {
    return strstr(text, needle) != NULL;
}

/* A lowercase copy, owned by the caller. */
static char *lowercase_copy(const char *text) {
    char *copy = xstrdup(text);
    if (!copy) return NULL;
    for (char *p = copy; *p; p++) *p = (char)tolower((unsigned char)*p);
    return copy;
}

/* An uppercase copy, owned by the caller. */
static char *uppercase_copy(const char *text) {
    char *copy = xstrdup(text);
    if (!copy) return NULL;
    for (char *p = copy; *p; p++) *p = (char)toupper((unsigned char)*p);
    return copy;
}

/* Words are the pieces of a name between hyphens. Empty pieces are dropped. Free with free_words. */
typedef struct {
    char **items;
    size_t count;
} Words;

static void words_push(Words *words, char *item) {
    char **grown = (char **)realloc(words->items, (words->count + 1) * sizeof(char *));
    if (!grown) {
        free(item);
        return;
    }
    words->items = grown;
    words->items[words->count++] = item;
}

static Words split_words(const char *text) {
    Words words = {NULL, 0};
    const char *start = text;
    for (const char *p = text;; p++) {
        if (*p == '-' || *p == '\0') {
            if (p > start) words_push(&words, xstrndup(start, (size_t)(p - start)));
            if (*p == '\0') break;
            start = p + 1;
        }
    }
    return words;
}

static void free_words(Words *words) {
    for (size_t i = 0; i < words->count; i++) free(words->items[i]);
    free(words->items);
    words->items = NULL;
    words->count = 0;
}

/* The words joined by a separator, owned by the caller. */
static char *join_words(const Words *words, const char *separator) {
    size_t total = 1;
    for (size_t i = 0; i < words->count; i++) total += strlen(words->items[i]) + strlen(separator);
    char *result = (char *)malloc(total);
    if (!result) return NULL;
    result[0] = '\0';
    for (size_t i = 0; i < words->count; i++) {
        if (i > 0) strcat(result, separator);
        strcat(result, words->items[i]);
    }
    return result;
}

/* Capitalizes the first letter of a word, and leaves the rest alone. */
static char *capitalize_copy(const char *word) {
    char *copy = xstrdup(word);
    if (copy && copy[0]) copy[0] = (char)toupper((unsigned char)copy[0]);
    return copy;
}

/* ---- Title words: the lists that fix spelling ------------------------------------------------- */

/* Words that are always written in capitals in titles. Matching ignores case. */
static const char *kAllCapsWords[] = {
    "api", "c", "cli", "ffi", "html", "http", "io", "json", "oo", "oop", "sql", "ui", "url", "xml",
};

/* Words with a fixed spelling that isn't simply all capitals. */
static const char *kSpecialWordsFrom[] = {"cpp", "cmake", "raii", "stl", "rust"};
static const char *kSpecialWordsTo[] = {"C++", "CMake", "RAII", "STL", "Rust"};

/* Phrases that appear inside a folder name and become a spaced title. The replacement has no hyphen. */
static const char *kInlinePhrasesFrom[] = {"big-o"};
static const char *kInlinePhrasesTo[] = {"Big O"};

/* The fixed spelling or all-caps form of a word, owned by the caller, or NULL if it isn't on a list. */
static char *special_word(const char *word) {
    char *key = lowercase_copy(word);
    char *result = NULL;
    if (!key) return NULL;
    for (size_t i = 0; i < sizeof kSpecialWordsFrom / sizeof kSpecialWordsFrom[0]; i++) {
        if (strcmp(key, kSpecialWordsFrom[i]) == 0) {
            result = xstrdup(kSpecialWordsTo[i]);
            break;
        }
    }
    if (!result) {
        for (size_t i = 0; i < sizeof kAllCapsWords / sizeof kAllCapsWords[0]; i++) {
            if (strcmp(key, kAllCapsWords[i]) == 0) {
                result = uppercase_copy(word);
                break;
            }
        }
    }
    free(key);
    return result;
}

/* Replaces each inline phrase that appears as whole words, so its hyphens don't split it apart. Owned by the caller. */
static char *protect_phrases(const char *text) {
    char *current = xstrdup(text);
    for (size_t i = 0; i < sizeof kInlinePhrasesFrom / sizeof kInlinePhrasesFrom[0]; i++) {
        const char *from = kInlinePhrasesFrom[i];
        const char *to = kInlinePhrasesTo[i];
        size_t from_length = strlen(from);
        size_t to_length = strlen(to);
        char *lower = lowercase_copy(current);
        size_t at = 0;
        while (at < strlen(current)) {
            const char *found_text = strstr(lower + at, from);
            if (!found_text) break;
            size_t found = (size_t)(found_text - lower);
            size_t end = found + from_length;
            int starts_word = found == 0 || current[found - 1] == '-';
            int ends_word = current[end] == '\0' || current[end] == '-';
            if (starts_word && ends_word) {
                size_t length = strlen(current);
                char *replaced = (char *)malloc(length - from_length + to_length + 1);
                if (!replaced) break;
                memcpy(replaced, current, found);
                memcpy(replaced + found, to, to_length);
                memcpy(replaced + found + to_length, current + end, length - end + 1);
                free(current);
                free(lower);
                current = replaced;
                lower = lowercase_copy(current);
                at = found + to_length;
            } else {
                at = found + 1;
            }
        }
        free(lower);
    }
    return current;
}

/* A step title such as "Hello world", from a folder name such as 02-hello-world. */
static char *step_title(const char *name) {
    const char *rest = name;
    while (isdigit((unsigned char)*rest)) rest++;
    while (*rest == '-') rest++;

    char *lower = lowercase_copy(rest);
    int is_re_exporting = lower && strcmp(lower, "re-exporting") == 0;
    free(lower);
    if (is_re_exporting) return xstrdup("Re-exporting");

    char *protected_text = protect_phrases(rest);
    Words pieces = split_words(protected_text);
    free(protected_text);

    Words titled = {NULL, 0};
    for (size_t i = 0; i < pieces.count; i++) {
        char *special = special_word(pieces.items[i]);
        if (special) {
            words_push(&titled, special);
        } else if (titled.count > 0) {
            words_push(&titled, xstrdup(pieces.items[i]));
        } else {
            words_push(&titled, capitalize_copy(pieces.items[i]));
        }
    }
    char *result = join_words(&titled, " ");
    free_words(&titled);
    free_words(&pieces);
    return result ? result : xstrdup("");
}

/* A chapter title such as "Ch07 · Packages", from a folder name such as ch07-packages. Extra chapters have no number. */
static char *chapter_title(const char *name, unsigned number) {
    const char *rest = name;
    if (starts_with(rest, "ch")) rest += 2;
    while (isdigit((unsigned char)*rest)) rest++;
    while (*rest == '-') rest++;

    Words pieces = split_words(rest);
    Words titled = {NULL, 0};
    for (size_t i = 0; i < pieces.count; i++) {
        char *special = special_word(pieces.items[i]);
        words_push(&titled, special ? special : capitalize_copy(pieces.items[i]));
    }
    char *joined = join_words(&titled, " ");
    free_words(&titled);
    free_words(&pieces);
    if (!joined) return xstrdup("");

    if (number >= EXTRA_CHAPTER_NUMBER) return joined;

    /* "Ch07 \xC2\xB7 ..." uses a middle dot, U+00B7, encoded as UTF-8. */
    size_t length = strlen(joined) + 16;
    char *title = (char *)malloc(length);
    if (title) snprintf(title, length, "Ch%02u \xC2\xB7 %s", number, joined);
    free(joined);
    return title ? title : xstrdup("");
}

/* ---- Folder names ------------------------------------------------------------------------------ */

/* Reads the digits that follow a prefix, such as 07 in ch07-packages. Returns 0 if there are none. */
static int read_number_after(const char *name, const char *prefix, unsigned *value) {
    if (!starts_with(name, prefix)) return 0;
    const char *digits = name + strlen(prefix);
    if (!isdigit((unsigned char)*digits)) return 0;
    unsigned result = 0;
    while (isdigit((unsigned char)*digits)) {
        result = result * 10u + (unsigned)(*digits - '0');
        digits++;
    }
    *value = result;
    return 1;
}

static int chapter_number(const char *name, unsigned *number) {
    if (read_number_after(name, "ch", number)) return 1;
    if (starts_with(name, "final-")) {
        *number = EXTRA_CHAPTER_NUMBER;
        return 1;
    }
    return 0;
}

/* Sections are folders named sNN-..., such as s01-what-is-ownership. */
static int section_number(const char *name, unsigned *number) {
    return read_number_after(name, "s", number);
}

/* ---- File system ------------------------------------------------------------------------------- */

static int is_directory(const char *path) {
    DWORD attributes = GetFileAttributesA(path);
    return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

static int is_regular_file(const char *path) {
    DWORD attributes = GetFileAttributesA(path);
    return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

/* Reads a whole file as text, owned by the caller. Returns an empty string if the file can't be read. */
static char *read_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) return xstrdup("");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (size < 0) {
        fclose(file);
        return xstrdup("");
    }
    char *text = (char *)malloc((size_t)size + 1);
    if (!text) {
        fclose(file);
        return xstrdup("");
    }
    size_t read = fread(text, 1, (size_t)size, file);
    text[read] = '\0';
    fclose(file);
    return text;
}

/* The names of the entries in a folder, sorted, without "." and "..". Free with free_words. */
static Words list_folder(const char *folder) {
    Words names = {NULL, 0};
    char pattern[MAX_PATH_BYTES];
    snprintf(pattern, sizeof pattern, "%s\\*", folder);
    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA(pattern, &data);
    if (find == INVALID_HANDLE_VALUE) return names;
    do {
        if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) continue;
        words_push(&names, xstrdup(data.cFileName));
    } while (FindNextFileA(find, &data));
    FindClose(find);
    return names;
}

static int compare_names(const void *a, const void *b) {
    return strcmp(*(char *const *)a, *(char *const *)b);
}

static void sort_names(Words *names) {
    if (names->count > 1) qsort(names->items, names->count, sizeof(char *), compare_names);
}

/* ---- Source files and CMake ------------------------------------------------------------------- */

/* Scans the sources under a folder (recursively) for a piece of text. Returns 1 if it's found. */
static int folder_has_text(const char *folder, const char *needle) {
    Words names = list_folder(folder);
    int found = 0;
    for (size_t i = 0; i < names.count && !found; i++) {
        char *path = path_join(folder, names.items[i]);
        if (!path) break;
        if (is_directory(path)) {
            found = folder_has_text(path, needle);
        } else if (ends_with(names.items[i], ".c") || ends_with(names.items[i], ".h")) {
            char *text = read_file(path);
            found = contains(text, needle);
            free(text);
        }
        free(path);
    }
    free_words(&names);
    return found;
}

static int step_has_main(const char *step) {
    int found = 0;
    static const char *folders[] = {"src", "tests"};
    for (size_t i = 0; i < sizeof folders / sizeof folders[0] && !found; i++) {
        char *folder = path_join(step, folders[i]);
        if (folder && is_directory(folder)) found = folder_has_text(folder, "int main(");
        free(folder);
    }
    return found;
}

/* A step writes a trace for the visualizer when its source mentions trace.js. */
static int step_writes_trace(const char *step) {
    char *src = path_join(step, "src");
    int found = src && is_directory(src) && folder_has_text(src, "trace.js");
    free(src);
    return found;
}

/* Whether a step's CMakeLists.txt declares a CTest test. C has no test-case macro, so this is how tests are found. */
static int cmake_declares_tests(const char *step) {
    char *path = path_join(step, "CMakeLists.txt");
    char *text = path ? read_file(path) : xstrdup("");
    int found = contains(text, "add_test(");
    free(text);
    free(path);
    return found;
}

/* The label above a chapter's homework: its title.txt first line, or "Homework". Owned by the caller. */
static char *homework_title(const char *homework) {
    char *path = path_join(homework, "title.txt");
    if (!path) return xstrdup("Homework");
    FILE *file = fopen(path, "r");
    free(path);
    if (!file) return xstrdup("Homework");
    char line[512];
    char *result = NULL;
    if (fgets(line, sizeof line, file)) {
        size_t length = strlen(line);
        while (length > 0 && isspace((unsigned char)line[length - 1])) line[--length] = '\0';
        if (length > 0) result = xstrdup(line);
    }
    fclose(file);
    return result ? result : xstrdup("Homework");
}

/* Reads the option(...) lines of a CMake file. The C++ rules: name ends at a space, tab, or quote, the description is
 * in quotes, and the default is the word after the description. */
void lesson_read_options(const char *cmake_file, LessonOption **options, size_t *count) {
    *options = NULL;
    *count = 0;
    char *text = read_file(cmake_file);
    char *line = text;
    while (*line) {
        char *end = strchr(line, '\n');
        size_t length = end ? (size_t)(end - line) : strlen(line);
        char *copy = xstrndup(line, length);
        if (copy) {
            char *start = copy;
            while (*start == ' ' || *start == '\t') start++;
            if (starts_with(start, "option(")) {
                char *name_end = start + 7;
                while (*name_end && *name_end != ' ' && *name_end != '\t' && *name_end != '"') name_end++;
                char *quote_open = strchr(name_end, '"');
                char *quote_close = quote_open ? strchr(quote_open + 1, '"') : NULL;
                if (name_end > start + 7 && quote_close) {
                    char *close = strchr(quote_close, ')');
                    char *value = xstrndup(quote_close + 1,
                                           close ? (size_t)(close - quote_close - 1) : strlen(quote_close + 1));
                    char *value_start = value;
                    while (*value_start == ' ' || *value_start == '\t') value_start++;
                    char *value_end = value_start + strlen(value_start);
                    while (value_end > value_start && (value_end[-1] == ' ' || value_end[-1] == '\t')) value_end--;
                    *value_end = '\0';

                    LessonOption *grown = (LessonOption *)realloc(*options, (*count + 1) * sizeof(LessonOption));
                    if (grown) {
                        *options = grown;
                        LessonOption *option = &(*options)[(*count)++];
                        option->name = xstrndup(start + 7, (size_t)(name_end - (start + 7)));
                        option->description = xstrndup(quote_open + 1, (size_t)(quote_close - quote_open - 1));
                        option->default_on = strcmp(value_start, "ON") == 0;
                    }
                    free(value);
                }
            }
            free(copy);
        }
        if (!end) break;
        line = end + 1;
    }
    free(text);
}

/* ---- Steps and sections ------------------------------------------------------------------------ */

static int compare_steps(const void *a, const void *b) {
    return strcmp(((const LessonStep *)a)->name, ((const LessonStep *)b)->name);
}

/* The steps in a folder: each sub-folder with a lesson.md or a CMakeLists.txt, except sections and homework. */
static LessonStep *steps_in(const char *folder, size_t *count) {
    LessonStep *steps = NULL;
    *count = 0;
    if (!is_directory(folder)) return NULL;

    Words names = list_folder(folder);
    sort_names(&names);
    for (size_t i = 0; i < names.count; i++) {
        char *path = path_join(folder, names.items[i]);
        if (!path) continue;
        unsigned section;
        char *lesson = path_join(path, "lesson.md");
        char *cmake = path_join(path, "CMakeLists.txt");
        int is_step = is_directory(path) && lesson && cmake &&
                      (is_regular_file(lesson) || is_regular_file(cmake)) && !section_number(names.items[i], &section) &&
                      strcmp(names.items[i], "homework") != 0;
        if (is_step) {
            LessonStep *grown = (LessonStep *)realloc(steps, (*count + 1) * sizeof(LessonStep));
            if (grown) {
                steps = grown;
                LessonStep *step = &steps[(*count)++];
                memset(step, 0, sizeof *step);
                step->name = xstrdup(names.items[i]);
                step->title = step_title(names.items[i]);
                step->path = xstrdup(path);
                step->has_code = is_regular_file(cmake);
                step->has_tests = cmake_declares_tests(path);
                step->has_main = step_has_main(path);
                char *visualizer = path_join(path, "visualize.html");
                step->has_visualizer = (visualizer && is_regular_file(visualizer)) || step_writes_trace(path);
                free(visualizer);
                lesson_read_options(cmake, &step->options, &step->option_count);
            }
        }
        free(lesson);
        free(cmake);
        free(path);
    }
    free_words(&names);
    if (*count > 1) qsort(steps, *count, sizeof(LessonStep), compare_steps);
    return steps;
}

/* Sub-chapters: folders named sNN-... inside a chapter, shown as "4.1 What is ownership". */
static LessonSection *sections_in(const char *chapter, unsigned chapter_no, size_t *count) {
    typedef struct {
        unsigned number;
        LessonSection section;
    } Numbered;

    Numbered *found = NULL;
    size_t found_count = 0;
    *count = 0;
    Words names = list_folder(chapter);
    sort_names(&names);
    for (size_t i = 0; i < names.count; i++) {
        unsigned number;
        char *path = path_join(chapter, names.items[i]);
        if (path && is_directory(path) && section_number(names.items[i], &number)) {
            Numbered *grown = (Numbered *)realloc(found, (found_count + 1) * sizeof(Numbered));
            if (grown) {
                found = grown;
                Numbered *entry = &found[found_count++];
                entry->number = number;
                entry->section.name = xstrdup(names.items[i]);
                entry->section.path = xstrdup(path);
                const char *after_s = names.items[i] + 1;
                char *step_name = xstrdup(after_s);
                char *base = step_title(step_name);
                free(step_name);
                size_t length = strlen(base) + 32;
                entry->section.title = (char *)malloc(length);
                if (entry->section.title) snprintf(entry->section.title, length, "%u.%u %s", chapter_no, number, base);
                free(base);
                entry->section.steps = steps_in(path, &entry->section.step_count);
            }
        }
        free(path);
    }
    free_words(&names);

    /* Sort by section number, keeping the folder order for equal numbers. */
    for (size_t i = 1; i < found_count; i++) {
        Numbered current = found[i];
        size_t j = i;
        while (j > 0 && found[j - 1].number > current.number) {
            found[j] = found[j - 1];
            j--;
        }
        found[j] = current;
    }

    LessonSection *sections = (LessonSection *)malloc((found_count ? found_count : 1) * sizeof(LessonSection));
    for (size_t i = 0; i < found_count; i++) sections[i] = found[i].section;
    free(found);
    *count = found_count;
    return sections;
}

/* ---- Chapters ---------------------------------------------------------------------------------- */

typedef struct {
    unsigned number;
    LessonChapter chapter;
} NumberedChapter;

LessonChapters lesson_discover(const char *root) {
    LessonChapters result = {NULL, 0};
    if (!is_directory(root)) return result;

    NumberedChapter *found = NULL;
    size_t found_count = 0;
    Words names = list_folder(root);
    sort_names(&names);
    for (size_t i = 0; i < names.count; i++) {
        unsigned number;
        if (!chapter_number(names.items[i], &number)) continue;
        char *path = path_join(root, names.items[i]);
        if (!path || !is_directory(path)) {
            free(path);
            continue;
        }
        NumberedChapter *grown = (NumberedChapter *)realloc(found, (found_count + 1) * sizeof(NumberedChapter));
        if (grown) {
            found = grown;
            NumberedChapter *entry = &found[found_count++];
            memset(entry, 0, sizeof *entry);
            entry->number = number;
            LessonChapter *chapter = &entry->chapter;
            chapter->name = xstrdup(names.items[i]);
            chapter->title = chapter_title(names.items[i], number);
            chapter->path = xstrdup(path);
            chapter->steps = steps_in(path, &chapter->step_count);
            char *homework = path_join(path, "homework");
            chapter->homework = steps_in(homework, &chapter->homework_count);
            chapter->homework_path = xstrdup(homework);
            chapter->homework_title = homework_title(homework);
            chapter->sections = sections_in(path, number, &chapter->section_count);
            free(homework);
        }
        free(path);
    }
    free_words(&names);

    /* Sort by chapter number, then name. Folder order is already by name, so a stable insertion sort is enough. */
    for (size_t i = 1; i < found_count; i++) {
        NumberedChapter current = found[i];
        size_t j = i;
        while (j > 0 && found[j - 1].number > current.number) {
            found[j] = found[j - 1];
            j--;
        }
        found[j] = current;
    }

    result.chapters = (LessonChapter *)malloc((found_count ? found_count : 1) * sizeof(LessonChapter));
    for (size_t i = 0; i < found_count; i++) result.chapters[i] = found[i].chapter;
    result.count = found_count;
    free(found);
    return result;
}

/* ---- JSON -------------------------------------------------------------------------------------- */

static cJSON *step_to_json(const LessonStep *step) {
    cJSON *object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "name", step->name);
    cJSON_AddStringToObject(object, "title", step->title);
    cJSON_AddStringToObject(object, "path", step->path);
    cJSON_AddBoolToObject(object, "has_code", step->has_code);
    cJSON_AddBoolToObject(object, "has_tests", step->has_tests);
    cJSON_AddBoolToObject(object, "has_main", step->has_main);
    cJSON_AddBoolToObject(object, "has_visualizer", step->has_visualizer);
    cJSON *options = cJSON_AddArrayToObject(object, "options");
    for (size_t i = 0; i < step->option_count; i++) {
        cJSON *option = cJSON_CreateObject();
        cJSON_AddStringToObject(option, "name", step->options[i].name);
        cJSON_AddStringToObject(option, "description", step->options[i].description);
        cJSON_AddBoolToObject(option, "default", step->options[i].default_on);
        cJSON_AddItemToArray(options, option);
    }
    return object;
}

static cJSON *steps_to_json(const LessonStep *steps, size_t count) {
    cJSON *array = cJSON_CreateArray();
    for (size_t i = 0; i < count; i++) cJSON_AddItemToArray(array, step_to_json(&steps[i]));
    return array;
}

static cJSON *section_to_json(const LessonSection *section) {
    cJSON *object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "name", section->name);
    cJSON_AddStringToObject(object, "title", section->title);
    cJSON_AddStringToObject(object, "path", section->path);
    cJSON_AddItemToObject(object, "steps", steps_to_json(section->steps, section->step_count));
    return object;
}

cJSON *lesson_chapter_to_json(const LessonChapter *chapter) {
    cJSON *object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "name", chapter->name);
    cJSON_AddStringToObject(object, "title", chapter->title);
    cJSON_AddStringToObject(object, "path", chapter->path);
    cJSON_AddItemToObject(object, "steps", steps_to_json(chapter->steps, chapter->step_count));
    cJSON_AddItemToObject(object, "homework", steps_to_json(chapter->homework, chapter->homework_count));
    cJSON_AddStringToObject(object, "homework_path", chapter->homework_path);
    cJSON_AddStringToObject(object, "homework_title", chapter->homework_title);
    cJSON *sections = cJSON_AddArrayToObject(object, "sections");
    for (size_t i = 0; i < chapter->section_count; i++) cJSON_AddItemToArray(sections, section_to_json(&chapter->sections[i]));
    return object;
}

/* The parts in parts.json, grouped as the C++ runner does. Chapters that no part names go under "Other". */
cJSON *lesson_list_parts(const char *root) {
    LessonChapters chapters = lesson_discover(root);
    int *used = (int *)calloc(chapters.count ? chapters.count : 1, sizeof(int));

    char *config_path = path_join(root, "parts.json");
    char *config_text = config_path ? read_file(config_path) : xstrdup("");
    cJSON *config = cJSON_Parse(config_text);
    free(config_text);
    free(config_path);

    cJSON *parts = cJSON_CreateArray();
    const cJSON *config_parts = config ? cJSON_GetObjectItemCaseSensitive(config, "parts") : NULL;
    if (cJSON_IsArray(config_parts)) {
        const cJSON *part;
        cJSON_ArrayForEach(part, config_parts) {
            const cJSON *title = cJSON_GetObjectItemCaseSensitive(part, "title");
            const cJSON *names = cJSON_GetObjectItemCaseSensitive(part, "chapters");
            cJSON *group = cJSON_CreateObject();
            cJSON_AddStringToObject(group, "title", cJSON_IsString(title) ? title->valuestring : "");
            cJSON *group_chapters = cJSON_AddArrayToObject(group, "chapters");
            const cJSON *name;
            cJSON_ArrayForEach(name, names) {
                if (!cJSON_IsString(name)) continue;
                for (size_t i = 0; i < chapters.count; i++) {
                    if (!used[i] && strcmp(chapters.chapters[i].name, name->valuestring) == 0) {
                        used[i] = 1;
                        cJSON_AddItemToArray(group_chapters, lesson_chapter_to_json(&chapters.chapters[i]));
                        break;
                    }
                }
            }
            if (cJSON_GetArraySize(group_chapters) > 0) {
                cJSON_AddItemToArray(parts, group);
            } else {
                cJSON_Delete(group);
            }
        }
    }

    cJSON *other = cJSON_CreateArray();
    for (size_t i = 0; i < chapters.count; i++) {
        if (!used[i]) cJSON_AddItemToArray(other, lesson_chapter_to_json(&chapters.chapters[i]));
    }
    if (cJSON_GetArraySize(other) > 0) {
        cJSON *group = cJSON_CreateObject();
        cJSON_AddStringToObject(group, "title", "Other");
        cJSON_AddItemToObject(group, "chapters", other);
        cJSON_AddItemToArray(parts, group);
    } else {
        cJSON_Delete(other);
    }

    cJSON_Delete(config);
    free(used);
    lesson_free_chapters(&chapters);
    return parts;
}

/* ---- Repository root and work folder ----------------------------------------------------------- */

void lesson_find_repo_root(const char *start, char *out, size_t out_size) {
    char folder[MAX_PATH_BYTES];
    GetFullPathNameA(start, (DWORD)sizeof folder, folder, NULL);
    for (;;) {
        char candidate[MAX_PATH_BYTES + 32];
        snprintf(candidate, sizeof candidate, "%s\\lesson-runner", folder);
        if (is_directory(candidate)) {
            snprintf(out, out_size, "%s", folder);
            return;
        }
        char *slash = strrchr(folder, '\\');
        if (!slash || slash == folder || (slash == folder + 2 && folder[1] == ':')) break;
        *slash = '\0';
    }
    snprintf(out, out_size, "%s", start);
}

void lesson_work_root(const char *repo_root, char *out, size_t out_size) {
    snprintf(out, out_size, "%s\\.lesson-runner\\work", repo_root);
}

/* ---- Freeing ----------------------------------------------------------------------------------- */

static void free_steps(LessonStep *steps, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(steps[i].name);
        free(steps[i].title);
        free(steps[i].path);
        for (size_t j = 0; j < steps[i].option_count; j++) {
            free(steps[i].options[j].name);
            free(steps[i].options[j].description);
        }
        free(steps[i].options);
    }
    free(steps);
}

void lesson_free_chapters(LessonChapters *chapters) {
    for (size_t i = 0; i < chapters->count; i++) {
        LessonChapter *chapter = &chapters->chapters[i];
        free(chapter->name);
        free(chapter->title);
        free(chapter->path);
        free(chapter->homework_path);
        free(chapter->homework_title);
        free_steps(chapter->steps, chapter->step_count);
        free_steps(chapter->homework, chapter->homework_count);
        for (size_t j = 0; j < chapter->section_count; j++) {
            LessonSection *section = &chapter->sections[j];
            free(section->name);
            free(section->title);
            free(section->path);
            free_steps(section->steps, section->step_count);
        }
        free(chapter->sections);
    }
    free(chapters->chapters);
    chapters->chapters = NULL;
    chapters->count = 0;
}
