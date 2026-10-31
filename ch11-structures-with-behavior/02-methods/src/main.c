#include <stdio.h>
#include <string.h>

typedef struct {
    char brand[32];
    char model[32];
    int year;
} Car;

void car_name(const Car *car, char *out, size_t size) {
    snprintf(out, size, "%s %s", car->brand, car->model);
}

void car_full_name(const Car *car, char *out, size_t size) {
    snprintf(out, size, "%d %s %s", car->year, car->brand, car->model);
}

int main(void) {
    Car my_car;
    strcpy(my_car.brand, "Ford");
    strcpy(my_car.model, "Mustang");
    my_car.year = 1969;

    char text[80];
    car_name(&my_car, text, sizeof text);
    printf("%s\n", text);

    car_full_name(&my_car, text, sizeof text);
    printf("%s\n", text);

    // Try: add car->year = 2000; inside car_name, and predict whether the build succeeds before you press Run.
    return 0;
}
