#include <stdio.h>
#include <string.h>

typedef struct {
    char brand[32];
    char model[32];
    int year;
} Car;

void car_init(Car *car, const char *brand, const char *model, int year) {
    strcpy(car->brand, brand);
    strcpy(car->model, model);
    car->year = year;
}

void car_show(const Car *car) {
    printf("%d %s %s\n", car->year, car->brand, car->model);
}

int main(void) {
    Car my_car1;
    car_init(&my_car1, "Ford", "Mustang", 1969);
    car_show(&my_car1);

    Car my_car2;
    car_init(&my_car2, "Dodge", "Challenger", 2014);
    car_show(&my_car2);

    // Try: add a third car with car_init(&my_car3, "Fiat"); and predict whether the build succeeds before you press Run.
    return 0;
}
