#include <stdio.h>

/* The context refers to both totals, so the visiting function updates the caller's variables. */
typedef struct {
    int *even_count;
    int *even_sum;
} Totals;

/* Calls visit once for each value in the array, passing the context along, as for_each does with a lambda. */
static void for_each_value(const int values[], size_t count, void (*visit)(void *, int), void *context) {
    for (size_t i = 0; i < count; i++) {
        visit(context, values[i]);
    }
}

static void count_and_sum_evens(void *context, int value) {
    Totals *totals = context;
    if (value % 2 == 0) {
        *totals->even_count += 1;
        *totals->even_sum += value;
    }
}

int main(void) {
    int values[10];
    for (int i = 0; i < 10; i++) {
        values[i] = i + 1;
    }

    int even_count = 0;
    int even_sum = 0;
    Totals totals = {&even_count, &even_sum};

    for_each_value(values, 10, count_and_sum_evens, &totals);

    printf("Even count: %d\n", even_count);
    printf("Sum of evens: %d\n", even_sum);
    return 0;
}
