#include <stdio.h>

/* Limits value to the range from low to high, inclusive. */
static int clamp(int value, int low, int high) {
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}

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

    check(clamp(5, 0, 10) == 5, "inside the range stays the same", &failures);
    check(clamp(-3, 0, 10) == 0, "below the range becomes the low end", &failures);
    check(clamp(42, 0, 10) == 10, "above the range becomes the high end", &failures);
    check(clamp(0, 0, 10) == 0, "the low end stays the same", &failures);
    check(clamp(10, 0, 10) == 10, "the high end stays the same", &failures);

    printf("Failures: %d\n", failures);

    /* CTest reads this exit code: zero passes, and one fails. */
    return failures == 0 ? 0 : 1;
}
