#include <stdio.h>
#include <string.h>

typedef struct {
    char brand[32];
    char model[32];
    int year;
} Car;

void car_print(const Car *car) {
    printf("%s %s %d\n", car->brand, car->model, car->year);
}

int main(void) {
    Car car1;
    strcpy(car1.brand, "BMW");
    strcpy(car1.model, "X5");
    car1.year = 1999;

    Car car2;
    strcpy(car2.brand, "Ford");
    strcpy(car2.model, "Mustang");
    car2.year = 1969;

    car_print(&car1);
    car_print(&car2);

    // Try: set car1.year to 2000 directly from main, and predict the first line before you press Run.
    return 0;
}
