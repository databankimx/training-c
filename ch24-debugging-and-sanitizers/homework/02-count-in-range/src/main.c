#include <stdio.h>

/* Counts the values that are at least low and at most high. Both ends are included. */
static int count_in_range(const int values[], size_t count, int low, int high) {
    int matches = 0;
    for (size_t i = 0; i < count; i++) {
        if (values[i] >= low && values[i] <= high) {
            matches++;
        }
    }
    return matches;
}

int main(void) {
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof values / sizeof values[0];

    printf("Count between 2 and 4: %d\n", count_in_range(values, count, 2, 4));
    printf("Count between 1 and 5: %d\n", count_in_range(values, count, 1, 5));
    return 0;
}
