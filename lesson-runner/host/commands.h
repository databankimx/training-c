/* commands.h: the page's file commands, such as reading a lesson or opening a run's output.
 *
 * Each function follows the C++ runner's commands.cpp. A function that returns text owns the result; free it with
 * free. A function that fails returns 0 and writes the reason into error.
 */

#ifndef LESSON_COMMANDS_H
#define LESSON_COMMANDS_H

#include <stddef.h>

#include "cJSON.h"

/* The lesson text (lesson.md) of a step, or an empty string if it has none. Owned by the caller. */
char *lesson_read_lesson(const char *step);

/* The text of lesson.md or solution.md in a step, or an empty string. Other file names are refused. */
char *lesson_read_step_file(const char *step, const char *file);

/* The commands in a step's commands.txt, as a JSON array of strings. Blank lines are skipped. */
cJSON *lesson_read_commands(const char *step);

/* The C source files under a step, as a JSON array of paths relative to the step, with main.c first. Files in tests
 * are listed with a tests/ prefix. */
cJSON *lesson_list_source_files(const char *step);

/* The text of one source file, named as lesson_list_source_files names it. Returns 1 and the text in out, or 0 with
 * a message in error. */
int lesson_read_source(const char *step, const char *file, char **out, char *error, size_t error_size);

/* Opens a file with its default application. The file must be inside the run folder. */
int lesson_open_file(const char *path, const char *work_folder, char *error, size_t error_size);

/* Opens a web or mail link in the default browser or mail program. Other kinds of link are refused. */
int lesson_open_external(const char *url, char *error, size_t error_size);

#endif /* LESSON_COMMANDS_H */
