#include <assert.h>
#include <stdio.h>

/* Returns the average of count values. The caller must never pass an empty array, so the assertion states that promise. */
static double average(const int values[], size_t count) {
    assert(count > 0);
    long long total = 0;
    for (size_t i = 0; i < count; i++) {
        total += values[i];
    }
    return (double)total / (double)count;
}

int main(void) {
    int values[] = {2, 4, 6, 8};
    size_t count = sizeof values / sizeof values[0];
    printf("Average: %.2f\n", average(values, count));
    return 0;
}
