#include <stdio.h>

#include "temperature.h"

int main(void) {
    printf("%.2f C is %.2f F\n", 0.0, celsius_to_fahrenheit(0.0));
    printf("%.2f C is %.2f F\n", 100.0, celsius_to_fahrenheit(100.0));
    printf("%.2f C is %.2f F\n", -40.0, celsius_to_fahrenheit(-40.0));
    printf("%.2f F is %.2f C\n", 212.0, fahrenheit_to_celsius(212.0));
    printf("%.2f F is %.2f C\n", 32.0, fahrenheit_to_celsius(32.0));
    return 0;
}
