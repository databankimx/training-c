#include <stdio.h>

#include "car.h"
#include "electric_car.h"

int main(void) {
    Car first = {"Ford", "Escort", 1986};
    car_display(&first);
    printf("\n");

    Car second = {"Nissan", "Leaf", 2015};
    car_display(&second);
    printf("\n");

    ElectricCar tesla;
    electric_car_init(&tesla, "Tesla", "Model 3", 2020, 25);
    electric_car_show_charge(&tesla);
    printf("\n");

    electric_car_charge(&tesla, 25);
    electric_car_show_charge(&tesla);
    printf("\n");

    electric_car_charge(&tesla, 0);
    electric_car_show_charge(&tesla);
    printf("\n");

    // Try: call electric_car_charge(&tesla, 200) and predict the charge shown before you press Run.
    return 0;
}
