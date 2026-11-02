#include <stdio.h>

/* Each function counts the operations its loops perform for n items. */

long linear_operations(long n) {
    long count = 0;
    for (long i = 0; i < n; i++) {
        count++;
    }
    return count;
}

long quadratic_operations(long n) {
    long count = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            count++;
        }
    }
    return count;
}

int main(void) {
    long sizes[] = {10, 100, 1000};
    for (size_t i = 0; i < 3; i++) {
        printf("n = %ld: linear %ld, quadratic %ld\n",
               sizes[i], linear_operations(sizes[i]), quadratic_operations(sizes[i]));
    }

    // Try: change the first size from 10 to 10000, and predict the quadratic count before you press Run.
    return 0;
}
