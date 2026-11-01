#include <stdio.h>

/* Returns the index of the first value not less than target, or count when every value is smaller. The list must be sorted. */
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

int main(void) {
    int values[] = {1, 3, 3, 3, 5, 8};
    size_t count = sizeof values / sizeof values[0];

    size_t at3 = lower_bound(values, count, 3);
    size_t at4 = lower_bound(values, count, 4);
    size_t at9 = lower_bound(values, count, 9);
    printf("lower_bound(3): %zu\n", at3);
    printf("lower_bound(4): %zu\n", at4);
    printf("lower_bound(9): %zu\n", at9);

    /* Every answer is the position where the target would go to keep the list in order. */
    int matches = at3 == 1 && at4 == 4 && at9 == 6;
    printf("Matches the expected positions: %s\n", matches ? "yes" : "no");
    return 0;
}
