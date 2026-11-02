#include <stdio.h>

void print_numbers(int numbers[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        printf("%d\n", numbers[i]);
    }
}

int main(void) {
    int my_numbers[5] = {10, 20, 30, 40, 50};

    print_numbers(my_numbers, 5);
    printf("First three:\n");
    print_numbers(my_numbers, 3);

    // Try: add numbers[0] = 99; at the top of print_numbers, and predict the first line of output before you press Run.
    return 0;
}
