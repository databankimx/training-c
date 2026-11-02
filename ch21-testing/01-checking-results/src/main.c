#include <stdio.h>

static int add(int a, int b) {
    return a + b;
}

/* Prints one line for the check, and counts a failure when it doesn't pass. */
static void check(int passed, const char *name, int *failures) {
    if (passed) {
        printf("PASS %s\n", name);
    } else {
        printf("FAIL %s\n", name);
        (*failures)++;
    }
}

int main(void) {
    int failures = 0;

    check(add(2, 3) == 5, "add 2 and 3", &failures);
    check(add(-4, 4) == 0, "add -4 and 4", &failures);
    check(add(0, 0) == 0, "add 0 and 0", &failures);

    /* This check is wrong on purpose: add(2, 3) is 5, not 6. A failing test can mean the code or the test is wrong. */
    check(add(2, 3) == 6, "add 2 and 3 expects 6", &failures);

    printf("Failures: %d\n", failures);
    return failures == 0 ? 0 : 1;
}
