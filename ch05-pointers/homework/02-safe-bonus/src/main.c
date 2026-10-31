#include <stdio.h>

int main(void) {
    int points = 50;
    int *score = &points;
    int *missing = NULL;

    if (score != NULL) {
        *score += 10;
    }
    printf("Points: %d\n", points);

    if (missing != NULL) {
        *missing += 5;
    } else {
        printf("No score to update.\n");
    }
    printf("Points: %d\n", points);

    return 0;
}
