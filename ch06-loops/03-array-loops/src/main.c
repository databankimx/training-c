#include <stdio.h>

int main(void) {
    int scores[] = {10, 20, 30, 40, 50};
    size_t count = sizeof scores / sizeof scores[0];

    printf("Scores:\n");
    for (size_t i = 0; i < count; i++) {
        printf("%d\n", scores[i]);
    }

    char colors[3][8] = {"red", "green", "blue"};
    size_t color_count = sizeof colors / sizeof colors[0];

    printf("Colors:\n");
    for (size_t i = 0; i < color_count; i++) {
        printf("%s\n", colors[i]);
    }

    // Try: add 60 to the end of scores, and predict the output before you press Run.
    return 0;
}
