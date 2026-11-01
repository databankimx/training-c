#include <stdio.h>
#include <stdlib.h>

/* A comparison function for qsort and bsearch. It returns negative, zero, or positive, as the first value is less, equal, or greater. */
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

/* The standard C library has no lower_bound, so this one is written out. It returns the index of the first value not less than target. */
static size_t lower_bound(const int values[], size_t count, int target) {
    size_t low = 0;
    size_t high = count;
    while (low < high) {
        size_t middle = low + (high - low) / 2;
        if (values[middle] < target) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }
    return low;
}

static int is_sorted(const int values[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (values[i - 1] > values[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int small[] = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
    size_t small_count = sizeof small / sizeof small[0];

    qsort(small, small_count, sizeof small[0], compare_ints);
    printf("Short list: %zu values\n", small_count);
    printf("Sorted:");
    for (size_t i = 0; i < small_count; i++) {
        printf(" %d", small[i]);
    }
    printf("\n");

    /* bsearch returns a pointer to a match, or NULL. Subtracting the start gives the index. */
    int key = 12;
    int *found = bsearch(&key, small, small_count, sizeof small[0], compare_ints);
    size_t position = lower_bound(small, small_count, key);
    printf("Search for 12: %s at index %ld\n", found ? "present" : "absent", found ? (long)(found - small) : -1L);
    printf("lower_bound for 12: index %zu\n", position);

    /* The timing list holds every whole number from -1000 to 1000, in a fixed shuffled order. */
    size_t big_count = 2001;
    int *big = malloc(big_count * sizeof *big);
    if (big == NULL) {
        printf("Out of memory.\n");
        return 1;
    }
    for (size_t i = 0; i < big_count; i++) {
        big[i] = (int)i - 1000;
    }
    unsigned int seed = 12345;
    for (size_t i = big_count - 1; i > 0; i--) {
        seed = seed * 1103515245u + 12345u;
        size_t j = (seed >> 16) % (i + 1);
        int swap = big[i];
        big[i] = big[j];
        big[j] = swap;
    }

    qsort(big, big_count, sizeof big[0], compare_ints);
    printf("Timing list: %zu values\n", big_count);
    printf("Sorted correctly: %s\n", is_sorted(big, big_count) ? "yes" : "no");

    int target737 = 737;
    int target5000 = 5000;
    printf("Search for 737: %s\n", bsearch(&target737, big, big_count, sizeof big[0], compare_ints) ? "present" : "absent");
    printf("Search for 5000: %s\n", bsearch(&target5000, big, big_count, sizeof big[0], compare_ints) ? "present" : "absent");
    free(big);

    // Try: change key to 21, and predict the bsearch and lower_bound results before you press Run.
    return 0;
}
