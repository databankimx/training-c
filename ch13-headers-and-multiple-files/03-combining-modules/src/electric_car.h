#ifndef ELECTRIC_CAR_H
#define ELECTRIC_CAR_H

#include "battery.h"
#include "car.h"

typedef struct {
    Car base;
    Battery battery;
} ElectricCar;

void electric_car_init(ElectricCar *electric, const char *make, const char *model, int year, int charge);
void electric_car_charge(ElectricCar *electric, int amount);
void electric_car_show_charge(const ElectricCar *electric);

#endif /* ELECTRIC_CAR_H */
