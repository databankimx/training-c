#include <stdio.h>
#include <string.h>

typedef struct {
    char brand[32];
} Vehicle;

typedef struct {
    Vehicle base;
    char model[32];
} Car;

typedef struct {
    Car base;
    int top_speed;
} SportsCar;

void vehicle_honk(const Vehicle *vehicle) {
    (void)vehicle;
    printf("Toot, toot!\n");
}

int main(void) {
    Car my_car;
    strcpy(my_car.base.brand, "Ford");
    strcpy(my_car.model, "Mustang");

    vehicle_honk(&my_car.base);
    printf("%s %s\n", my_car.base.brand, my_car.model);

    SportsCar fast;
    strcpy(fast.base.base.brand, "Ford");
    strcpy(fast.base.model, "Mustang");
    fast.top_speed = 180;

    vehicle_honk(&fast.base.base);
    printf("%s %s %d\n", fast.base.base.brand, fast.base.model, fast.top_speed);

    // Try: add a function vehicle_describe that prints "A vehicle.", call it on &fast.base.base, and predict the output before you press Run.
    return 0;
}
