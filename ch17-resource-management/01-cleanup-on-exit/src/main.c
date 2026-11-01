#include <stdio.h>
#include <stdlib.h>

/* Allocates two blocks and does some work with them. fail_at picks a route out of the function:
   0 means success, 1 fails after the first allocation, and 2 fails after the second.
   Every route leaves through the cleanup labels, so each block is released exactly once. */
static int run_task(int fail_at, int *released) {
    int result = -1;
    char *first = NULL;
    char *second = NULL;

    first = malloc(16);
    if (first == NULL) {
        goto done;
    }
    if (fail_at == 1) {
        goto cleanup_first;
    }

    second = malloc(32);
    if (second == NULL) {
        goto cleanup_first;
    }
    if (fail_at == 2) {
        goto cleanup_second;
    }

    result = 0;

cleanup_second:
    free(second);
    (*released)++;
cleanup_first:
    free(first);
    (*released)++;
done:
    return result;
}

int main(void) {
    for (int fail_at = 0; fail_at <= 2; fail_at++) {
        int released = 0;
        int result = run_task(fail_at, &released);
        printf("fail_at %d: result %d, blocks released %d\n", fail_at, result, released);
    }

    // Try: move the free(first) line above the cleanup_second label, and predict what happens on the fail_at 2 route before you press Run.
    return 0;
}
