#include <stdio.h>

int main(void) {
    int numbers[3] = {10, 20, 30};
    int *first = numbers;

    printf("%d\n", *first);
    printf("%d\n", first[1]);
    printf("%d\n", *(first + 2));

    printf("Array size: %zu bytes\n", sizeof numbers);
    printf("Pointer size: %zu bytes\n", sizeof first);
    printf("Elements counted from the array: %zu\n", sizeof numbers / sizeof numbers[0]);

    // Try: set first = &numbers[2], and predict *first before you press Run.
    return 0;
}
