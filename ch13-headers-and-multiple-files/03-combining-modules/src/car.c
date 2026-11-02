#include "car.h"

#include <stdio.h>

void car_display(const Car *car) {
    printf("Make: %s\n", car->make);
    printf("Model: %s\n", car->model);
    printf("Year: %d\n", car->year);
}
