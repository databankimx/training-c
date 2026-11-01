#include <assert.h>
#include <stdio.h>

/* Divides a by b. The caller must never pass zero, so the assertion states that promise. */
static int divide(int a, int b) {
    assert(b != 0);
    return a / b;
}

int main(void) {
    int half = divide(10, 2);
    int third = divide(9, 3);
    if (half == 5 && third == 3) {
        printf("All assertions passed\n");
    }

    // Try: add divide(1, 0); before the final message, and predict what the program prints and its exit code before you press Run.
    return 0;
}
