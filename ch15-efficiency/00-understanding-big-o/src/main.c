#include <stdio.h>

/* Each function counts the steps its loop takes, so the growth shows up as numbers. */

static long linear_steps(long n) {
    long steps = 0;
    for (long i = 0; i < n; i++) {
        steps++;
    }
    return steps;
}

static long quadratic_steps(long n) {
    long steps = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            steps++;
        }
    }
    return steps;
}

static long halving_steps(long n) {
    long steps = 0;
    long range = n;
    while (range > 1) {
        range /= 2;
        steps++;
    }
    return steps;
}

int main(void) {
    long sizes[] = {10, 100, 1000};
    for (size_t i = 0; i < 3; i++) {
        printf("n = %ld: linear %ld, quadratic %ld, halving %ld\n",
               sizes[i], linear_steps(sizes[i]), quadratic_steps(sizes[i]), halving_steps(sizes[i]));
    }

    // Try: change the first size from 10 to 10000, and predict the quadratic count before you press Run.
    return 0;
}
