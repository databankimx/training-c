#include <stdio.h>
#include <string.h>

typedef struct {
    char brand[32];
    char model[32];
    int year;
} Car;

Car make_car(const char *brand, const char *model, int year) {
    Car car;
    /* UNSAFE PATH: strcpy does not check sizes. brand and model must be at most 31 characters. */
    strcpy(car.brand, brand);
    strcpy(car.model, model);
    car.year = year;
    return car;
}

void describe(Car car) {
    printf("%s %s %d\n", car.brand, car.model, car.year);
}

void make_older(Car *car) {
    car->year -= 10;
}

int main(void) {
    Car mine = make_car("BMW", "X5", 1999);
    describe(mine);
    make_older(&mine);
    describe(mine);

    Car cars[2] = {make_car("Ford", "Mustang", 1969), make_car("Fiat", "500", 2010)};
    for (size_t i = 0; i < 2; i++) {
        describe(cars[i]);
    }

    // Try: change make_older to take a Car by value, and predict the second line of output before you press Run.
    return 0;
}
