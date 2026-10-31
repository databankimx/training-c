/* discovery.h: finds the chapters, sections, steps, and homework in the training repository.
 *
 * The rules match the C++ runner's discovery.cpp. The differences are the ones C requires: text is held in plain
 * char arrays, folders are read with the Windows file API, and JSON is built with cJSON. A step's tests are found by
 * a CTest add_test in its CMakeLists.txt, since C has no test-case macro the runner can read.
 *
 * Every string in these structures is owned by the structure. Free the whole tree with lesson_free_chapters.
 */

#ifndef LESSON_DISCOVERY_H
#define LESSON_DISCOVERY_H

#include <stddef.h>

#include "cJSON.h"

typedef struct {
    char *name;
    char *description;
    int default_on; /* 1 when the option defaults to ON */
} LessonOption;

typedef struct {
    char *name;
    char *title;
    char *path;
    int has_code;       /* the step has a CMakeLists.txt */
    int has_tests;      /* the step's CMakeLists.txt declares a CTest test */
    int has_main;       /* a source file under src or tests has a main function */
    int has_visualizer; /* the step has a visualize.html */
    LessonOption *options;
    size_t option_count;
} LessonStep;

typedef struct {
    char *name;
    char *title;
    char *path;
    LessonStep *steps;
    size_t step_count;
} LessonSection;

typedef struct {
    char *name;
    char *title;
    char *path;
    LessonStep *steps;
    size_t step_count;
    LessonStep *homework;
    size_t homework_count;
    char *homework_path;
    char *homework_title; /* "Homework" unless the homework folder has a title.txt */
    LessonSection *sections;
    size_t section_count;
} LessonChapter;

typedef struct {
    LessonChapter *chapters;
    size_t count;
} LessonChapters;

/* Walks up from start until it finds the folder that holds lesson-runner. Returns the start folder if none does. The
 * result is written to out, which must hold at least MAX_PATH bytes. */
void lesson_find_repo_root(const char *start, char *out, size_t out_size);

/* Every chapter folder in the repository, in chapter order. Free with lesson_free_chapters. */
LessonChapters lesson_discover(const char *root);

/* The chapters grouped by the parts named in parts.json. Chapters that no part names go under "Other". Returns a
 * JSON array of { title, chapters } objects. The caller frees it with cJSON_Delete. */
cJSON *lesson_list_parts(const char *root);

/* The folder where runs are built and run, inside the repository. Written to out. */
void lesson_work_root(const char *repo_root, char *out, size_t out_size);

/* Reads the option(...) lines of a CMake file. Commented lines are skipped. Free with lesson_free_options. */
void lesson_read_options(const char *cmake_file, LessonOption **options, size_t *count);

/* The JSON shape the page expects for one chapter, section, or step. The caller frees the result. */
cJSON *lesson_chapter_to_json(const LessonChapter *chapter);

void lesson_free_chapters(LessonChapters *chapters);

#endif /* LESSON_DISCOVERY_H */
