#include <stdio.h>

#include "car.h"

int main(void) {
    Car *my_car = car_create("Ford", "Mustang", 1969);
    if (my_car == NULL) {
        printf("Could not create the car.\n");
        return 1;
    }
    car_show(my_car);

    car_set_year(my_car, 2014);
    car_show(my_car);

    if (car_set_year(my_car, 1700) != 0) {
        printf("year is before cars existed\n");
    }
    car_show(my_car);

    car_destroy(my_car);

    // Try: add my_car->year = 1700; and predict whether the build succeeds before you press Run.
    return 0;
}
