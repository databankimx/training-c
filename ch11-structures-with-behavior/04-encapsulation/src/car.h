#ifndef CAR_H
#define CAR_H

/* The structure is declared here but defined only in car.c, so code outside car.c can't read its fields. */
typedef struct Car Car;

Car *car_create(const char *brand, const char *model, int year);
void car_destroy(Car *car);

int car_get_year(const Car *car);
int car_set_year(Car *car, int year);

void car_show(const Car *car);

#endif /* CAR_H */
