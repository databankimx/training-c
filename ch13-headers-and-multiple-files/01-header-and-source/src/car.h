#ifndef CAR_H
#define CAR_H

typedef struct {
    char make[32];
    char model[32];
    int year;
} Car;

void car_display(const Car *car);

#endif /* CAR_H */
