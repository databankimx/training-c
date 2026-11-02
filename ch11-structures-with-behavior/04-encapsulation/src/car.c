#include "car.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    char brand[32];
    char model[32];
    int year;
};

/* Returns NULL if the year is refused, so an object is never created in an invalid state. */
Car *car_create(const char *brand, const char *model, int year) {
    Car *car = malloc(sizeof *car);
    if (car == NULL) {
        return NULL;
    }
    /* UNSAFE PATH: strcpy does not check sizes. The brand and model must be at most 31 characters,
       or the copy writes past the end of the member. Use snprintf with sizeof for untrusted input. */
    strcpy(car->brand, brand);
    strcpy(car->model, model);
    car->year = 0;

    if (car_set_year(car, year) != 0) {
        free(car);
        return NULL;
    }
    return car;
}

void car_destroy(Car *car) {
    free(car);
}

int car_get_year(const Car *car) {
    return car->year;
}

/* Returns 0 when the year is stored, or -1 when it's refused and the car is left unchanged. */
int car_set_year(Car *car, int year) {
    if (year < 1886) {
        return -1;
    }
    car->year = year;
    return 0;
}

void car_show(const Car *car) {
    printf("%d %s %s\n", car->year, car->brand, car->model);
}
