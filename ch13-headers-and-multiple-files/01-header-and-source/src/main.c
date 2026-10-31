#include <stdio.h>

#include "car.h"

int main(void) {
    Car first = {"Ford", "Escort", 1986};
    car_display(&first);
    printf("\n");

    Car second = {"Nissan", "Leaf", 2015};
    car_display(&second);
    printf("\n");

    // Try: remove the #include "car.h" line, and predict the build error before you press Run.
    return 0;
}
