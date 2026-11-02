#include <stdio.h>

/* Counts the pairs (i, j) with i < j among n positions, by checking each pair with nested loops. */
static long count_pairs(long n) {
    long pairs = 0;
    for (long i = 0; i < n; i++) {
        for (long j = i + 1; j < n; j++) {
            pairs++;
        }
    }
    return pairs;
}

/* The same count from a formula: n times (n - 1), divided by 2. */
static long pair_formula(long n) {
    return n * (n - 1) / 2;
}

int main(void) {
    long sizes[] = {4, 10, 100};
    for (size_t i = 0; i < 3; i++) {
        printf("n = %ld: pairs %ld, formula %ld\n",
               sizes[i], count_pairs(sizes[i]), pair_formula(sizes[i]));
    }
    return 0;
}
