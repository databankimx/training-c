#include <stdio.h>

int main(void) {
    double celsius = 100.0;
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("%.1f C is %.1f F\n", celsius, fahrenheit);

    celsius = 25.0;
    fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("%.1f C is %.1f F\n", celsius, fahrenheit);

    celsius = 0.0;
    fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("%.1f C is %.1f F\n", celsius, fahrenheit);

    return 0;
}
