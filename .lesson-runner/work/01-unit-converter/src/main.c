#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[64];

    printf("Enter a temperature in Celsius: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }

    double celsius = strtod(line, NULL);
    const double fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    printf("%g C is %g F\n", celsius, fahrenheit);
    return 0;
}
