/* runner.h: builds and runs a lesson step, and collects its output.
 *
 * The C++ runner's runner.hpp describes the same class. A run happens on a worker thread: it copies the step into the
 * work folder, configures and builds it with CMake, then runs the program (or its tests with CTest) with its output on
 * pipes. The worker never touches the page. It queues events, and the window's thread sends them to the page, so the
 * page is only ever used from the window's thread.
 */

#ifndef LESSON_RUNNER_H
#define LESSON_RUNNER_H

#include <windows.h>

#include <stddef.h>

#include "cJSON.h"

/* The message the window receives when events are queued. */
#define LESSON_RUNNER_EVENTS_MESSAGE (WM_APP + 1)

/* One run, as the page asked for it. Every string is owned by the request. */
typedef struct {
    char *step;               /* the step folder, absolute */
    char *source;             /* the edited main.c, or NULL to run the step as it is */
    int backtrace;            /* build with debug information and stack-trace support */
    int test;                 /* run the step's tests with CTest, instead of the program */
    char **args;              /* the arguments for the program */
    size_t arg_count;
    char **option_names;      /* the step's option checkboxes: each name and whether it is on */
    int *option_values;
    size_t option_count;
} RunRequest;

/* A queued event: its name and its payload. The list is detached by runner_take_events. */
typedef struct LessonEvent {
    char *name;
    cJSON *payload;
    struct LessonEvent *next;
} LessonEvent;

typedef struct LessonRunner LessonRunner;

/* Creates the runner. Its build tools are found first on PATH, from the MSYS2 UCRT64 folder. */
LessonRunner *lesson_runner_create(HWND window, const char *repo_root);

/* Stops any run, waits for it, and frees the runner. */
void lesson_runner_destroy(LessonRunner *runner);

/* Starts a run on a worker thread. The runner takes ownership of the request. Returns 0 on success, or 1 with a
 * message in error if a run is already going. */
int lesson_runner_start(LessonRunner *runner, RunRequest *request, char *error, size_t error_size);

/* Asks the running program to stop, which ends its whole process tree. */
void lesson_runner_stop(LessonRunner *runner);

/* Writes text to the running program's input. Returns 0 on success, or 1 with a message in error if nothing is running. */
int lesson_runner_send_input(LessonRunner *runner, const char *text, char *error, size_t error_size);

/* Takes every queued event, oldest first. The caller frees the list with lesson_free_events. */
LessonEvent *lesson_runner_take_events(LessonRunner *runner);

void lesson_free_events(LessonEvent *events);

/* Frees a request and everything it owns. */
void lesson_free_request(RunRequest *request);

#endif /* LESSON_RUNNER_H */
