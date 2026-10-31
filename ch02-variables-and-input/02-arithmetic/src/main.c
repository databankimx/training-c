#include <stdio.h>

int main(void) {
    int a = 7;
    int b = 2;

    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);
    printf("a %% b = %d\n", a % b);
    printf("a / b as double = %.2f\n", (double)a / b);

    // Try: change a to 9 and b to 4, and predict every line before you press Run.
    return 0;
}
