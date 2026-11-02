#include "battery.h"

#include <stdio.h>

void battery_init(Battery *battery, int capacity, int charge) {
    battery->capacity = capacity;
    battery->charge = charge;
}

void battery_recharge(Battery *battery, int amount) {
    if (amount == 0) {
        battery->charge = battery->capacity;
    } else {
        battery->charge += amount;
    }
    if (battery->charge > battery->capacity) {
        battery->charge = battery->capacity;
    }
}

void battery_print(const Battery *battery) {
    printf("Charge: %d\n", battery->charge);
    printf("Capacity: %d\n", battery->capacity);
}
