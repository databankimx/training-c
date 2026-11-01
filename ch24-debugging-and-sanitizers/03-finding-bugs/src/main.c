#include <stdio.h>

/* Adds the whole numbers from 1 up to n. This version has an off-by-one error: the loop stops before n. */
static int sum_to(int n) {
    int total = 0;
    for (int i = 1; i < n; i++) {
        total += i;
    }
    return total;
}

int main(void) {
    printf("Sum of 1 to 10: %d\n", sum_to(10));

    // Try: change the loop condition in sum_to so that it includes n, and predict the output before you press Run.
    return 0;
}
