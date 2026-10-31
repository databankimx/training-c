#ifndef BATTERY_H
#define BATTERY_H

typedef struct {
    int charge;
    int capacity;
} Battery;

void battery_init(Battery *battery, int capacity, int charge);

/* An amount of zero fills the battery. Any other amount adds to the charge, up to the capacity. */
void battery_recharge(Battery *battery, int amount);

void battery_print(const Battery *battery);

#endif /* BATTERY_H */
