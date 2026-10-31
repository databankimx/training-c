/* router-test: sends commands to the router from the console, and prints each reply and event.
 *
 *   router-test <repository root>
 *
 * Each input line is a command name, then its arguments as JSON. For example:
 *   read_commands {"path": "C:\\Development\\training\\training-cpp\\ch01-getting-started\\01-hello-world"}
 *   run_step {"path": "C:\\Development\\training\\training-cpp\\ch01-getting-started\\01-hello-world"}
 *
 * Replies print as "reply <command> <json>", errors as "error <command> <message>", and events as "event <name>
 * <json>". After the last line, the tool waits a few seconds so a run can finish and its output can print.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "cJSON.h"
#include "router.h"
#include "runner.h"

static void print_json(const char *label, const char *name, const cJSON *value) {
    char *text = cJSON_PrintUnformatted(value);
    printf("%s %s %s\n", label, name, text ? text : "?");
    free(text);
}

/* Router events are printed as they happen. */
static void print_event(void *context, const char *name, cJSON *payload) {
    (void)context;
    print_json("event", name, payload);
    cJSON_Delete(payload);
}

/* Run events are queued by the runner, so they are printed here. */
static void drain(LessonRunner *runner) {
    LessonEvent *events = lesson_runner_take_events(runner);
    for (LessonEvent *event = events; event; event = event->next) {
        print_json("event", event->name, event->payload);
    }
    lesson_free_events(events);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: router-test <repository root>\n");
        return 2;
    }
    LessonRunner *runner = lesson_runner_create(NULL, argv[1]);
    LessonRouter *router = lesson_router_create(argv[1], runner, print_event, NULL);
    if (!runner || !router) {
        fprintf(stderr, "could not create the runner or the router\n");
        return 1;
    }

    char line[8192];
    while (fgets(line, sizeof line, stdin)) {
        size_t length = strlen(line);
        while (length > 0 && (line[length - 1] == '\n' || line[length - 1] == '\r')) line[--length] = '\0';
        if (length == 0) continue;

        /* The command name ends at the first space. The rest is its JSON arguments, or nothing. */
        char *json_text = strchr(line, ' ');
        if (json_text) *json_text++ = '\0';
        cJSON *args = cJSON_Parse(json_text ? json_text : "{}");
        if (!args) {
            printf("error %s the arguments are not valid JSON\n", line);
            continue;
        }

        char error[512] = "";
        cJSON *reply = lesson_router_handle(router, line, args, error, sizeof error);
        if (reply) {
            print_json("reply", line, reply);
            cJSON_Delete(reply);
        } else {
            printf("error %s %s\n", line, error);
        }
        cJSON_Delete(args);
        drain(runner);
    }

    /* Let a run that is still going finish, and print its output. */
    for (int i = 0; i < 50; i++) {
        Sleep(100);
        drain(runner);
    }

    lesson_router_destroy(router);
    lesson_runner_destroy(runner);
    return 0;
}
