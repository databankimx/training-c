#include <stdio.h>

#include "int_vector.h"

int main(void) {
    IntVector scores;
    int_vector_init(&scores);
    int_vector_push(&scores, 72);
    int_vector_push(&scores, 88);
    int_vector_push(&scores, 95);
    int_vector_push(&scores, 60);

    printf("Count: %zu\n", scores.size);

    int highest = 0;
    int lowest = 0;
    int total = 0;
    for (size_t i = 0; i < scores.size; i++) {
        int score = 0;
        int_vector_at(&scores, i, &score);
        if (i == 0 || score > highest) {
            highest = score;
        }
        if (i == 0 || score < lowest) {
            lowest = score;
        }
        total += score;
    }

    printf("Highest: %d\n", highest);
    printf("Lowest: %d\n", lowest);
    printf("Average: %.2f\n", (double)total / (double)scores.size);

    int_vector_free(&scores);
    return 0;
}
