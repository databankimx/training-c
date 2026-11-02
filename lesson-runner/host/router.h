/* router.h: the protocol between the page and the runner. The page sends a command and its arguments, and the router
 * answers with a reply or an error, and sends events (such as run output) back through a callback.
 *
 * The commands and their argument names match the C++ runner's router.cpp, so the page works with either runner.
 */

#ifndef LESSON_ROUTER_H
#define LESSON_ROUTER_H

#include <stddef.h>

#include "cJSON.h"
#include "runner.h"

/* Receives every event. The sink takes ownership of the payload, and frees it when done. */
typedef void (*LessonEventSink)(void *context, const char *name, cJSON *payload);

/* Receives the window actions the page asks for: "open" for a pop-out lesson window, and "dock" to bring it back. */
typedef void (*LessonWindowAction)(void *context, const char *action);

typedef struct LessonRouter LessonRouter;

/* Creates a router for a repository. The runner is used for run_step, send_input, and stop_run. The router does not
 * own the runner or the sink's context. */
LessonRouter *lesson_router_create(const char *repo_root, LessonRunner *runner, LessonEventSink events,
                                   void *events_context);

void lesson_router_destroy(LessonRouter *router);

void lesson_router_set_window_action(LessonRouter *router, LessonWindowAction action, void *context);

/* Handles one command. Returns the reply, which the caller frees with cJSON_Delete. On failure it returns NULL and
 * writes the reason into error. */
cJSON *lesson_router_handle(LessonRouter *router, const char *command, const cJSON *args, char *error,
                            size_t error_size);

#endif /* LESSON_ROUTER_H */
