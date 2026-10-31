#include <stdio.h>

#include "int_vector.h"

int main(void) {
    IntVector scores;
    int_vector_init(&scores);
    int_vector_push(&scores, 72);
    int_vector_push(&scores, 88);
    int_vector_push(&scores, 95);

    printf("Count: %zu\n", scores.size);

    int first = 0;
    int last = 0;
    int_vector_at(&scores, 0, &first);
    int_vector_at(&scores, scores.size - 1, &last);
    printf("First: %d\n", first);
    printf("Last: %d\n", last);

    int total = 0;
    for (size_t i = 0; i < scores.size; i++) {
        int value = 0;
        int_vector_at(&scores, i, &value);
        total += value;
    }
    printf("Total: %d\n", total);
    printf("Average: %d\n", total / (int)scores.size);

    int_vector_push(&scores, 60);
    printf("After adding: %zu\n", scores.size);

    int checked = 0;
    if (int_vector_at(&scores, 10, &checked) != 0) {
        printf("Index 10 is out of range.\n");
    }
    int_vector_free(&scores);

    IntVector stack;
    int_vector_init(&stack);
    int_vector_push(&stack, 1);
    int_vector_push(&stack, 2);
    int_vector_push(&stack, 3);

    int_vector_at(&stack, 0, &first);
    int_vector_at(&stack, stack.size - 1, &last);
    printf("Front: %d, back: %d\n", first, last);

    int_vector_pop(&stack);
    int_vector_at(&stack, stack.size - 1, &last);
    printf("After pop_back: size %zu, back %d\n", stack.size, last);

    int_vector_insert(&stack, 1, 99);
    int_vector_erase(&stack, 0);
    printf("Elements:");
    for (size_t i = 0; i < stack.size; i++) {
        int value = 0;
        int_vector_at(&stack, i, &value);
        printf(" %d", value);
    }
    printf("\n");
    int_vector_free(&stack);

    // Try: change the check to int_vector_at(&scores, 3, ...) and predict whether the message prints before you press Run.
    return 0;
}
