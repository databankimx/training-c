#include <stdio.h>

int main(void) {
    printf("Counting up:\n");
    for (int i = 0; i < 5; ++i) {
        printf("%d\n", i + 1);
    }

    printf("Counting by twos:\n");
    for (int i = 0; i < 10; i += 2) {
        printf("%d\n", i + 2);
    }

    printf("Counting down:\n");
    for (int i = 5; i > 0; i--) {
        printf("%d\n", i);
    }

    printf("Nested loops:\n");
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%d, %d\n", i, j);
        }
    }

    // Try: change i += 2 to i += 3, and predict the numbers before you press Run.
    return 0;
}
