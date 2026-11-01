#include <stdio.h>
#include <stdlib.h>

/* A comparison that puts the largest values first. It returns negative when a should come before b. */
static int compare_descending(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y > x) - (y < x);
}

/* A comparison that puts the smallest values first. */
static int compare_ascending(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static void print_values(const char *label, const int values[], size_t count) {
    printf("%s:", label);
    for (size_t i = 0; i < count; i++) {
        printf(" %d", values[i]);
    }
    printf("\n");
}

int main(void) {
    int values[] = {3, 1, 4, 1, 5, 9, 2, 6};
    size_t count = sizeof values / sizeof values[0];

    /* The rule is passed as a function pointer, the C form of the lambda passed to std::sort. */
    qsort(values, count, sizeof values[0], compare_descending);
    print_values("Descending", values, count);

    int again[] = {3, 1, 4, 1, 5, 9, 2, 6};
    qsort(again, count, sizeof again[0], compare_ascending);
    print_values("Ascending", again, count);

    // Try: pass compare_ascending to qsort in the first call instead, and predict the order before you press Run.
    return 0;
}
