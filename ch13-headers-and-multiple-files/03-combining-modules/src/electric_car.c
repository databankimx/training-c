#include "electric_car.h"

#include <string.h>

void electric_car_init(ElectricCar *electric, const char *make, const char *model, int year, int charge) {
    /* UNSAFE PATH: strcpy does not check sizes. make and model must be at most 31 characters. */
    strcpy(electric->base.make, make);
    strcpy(electric->base.model, model);
    electric->base.year = year;

    battery_init(&electric->battery, 100, 0);
    if (charge > 0) {
        battery_recharge(&electric->battery, charge);
    }
}

void electric_car_charge(ElectricCar *electric, int amount) {
    battery_recharge(&electric->battery, amount);
}

void electric_car_show_charge(const ElectricCar *electric) {
    battery_print(&electric->battery);
}
