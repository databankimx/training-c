#include <stdio.h>

int main(void) {
    int partial[5] = {7, 8};
    printf("%d %d %d %d\n", partial[0], partial[1], partial[2], partial[4]);

    int speeds[] = {60, 75, 80, 90, 95};
    size_t count = sizeof speeds / sizeof speeds[0];
    printf("Speeds: %zu\n", count);
    printf("Last: %d\n", speeds[count - 1]);

    int squares[3];
    squares[0] = 1;
    squares[1] = 4;
    squares[2] = 9;
    printf("%d\n", squares[2]);

    // Try: change partial to {7, 8, 9, 10, 11}, and predict the first line before you press Run.
    return 0;
}
