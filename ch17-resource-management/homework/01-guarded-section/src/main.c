#include <stdio.h>

/* A guard records the name of a section, and its leave function undoes the enter. */
typedef struct {
    const char *name;
} Guard;

static void guard_enter(Guard *guard, const char *name) {
    guard->name = name;
    printf("Enter %s\n", guard->name);
}

static void guard_leave(const Guard *guard) {
    printf("Leave %s\n", guard->name);
}

/* Returns 0 on success, or -1 when the work fails. The guard is left on every route, before the caller sees the result. */
static int process(int fail) {
    Guard section;
    guard_enter(&section, "section");
    int result = -1;

    printf("Working\n");
    if (fail) {
        goto leave;
    }
    printf("Finished working\n");
    result = 0;

leave:
    guard_leave(&section);
    return result;
}

int main(void) {
    int status = process(0);
    status = process(1);
    if (status != 0) {
        printf("Caught: work failed\n");
    }
    printf("End\n");

    // Try: add a second guard named "inner" inside process, and predict the order of the two Leave lines when fail is 1, before you press Run.
    return 0;
}
