#include <stdio.h>
#include <string.h>

typedef struct {
    char brand[32];
    char model[32];
    int year;
} Car;

int main(void) {
    Car my_car1;
    strcpy(my_car1.brand, "BMW");
    strcpy(my_car1.model, "X5");
    my_car1.year = 1999;

    Car my_car2;
    strcpy(my_car2.brand, "Ford");
    strcpy(my_car2.model, "Mustang");
    my_car2.year = 1969;

    printf("%s %s %d\n", my_car1.brand, my_car1.model, my_car1.year);
    printf("%s %s %d\n", my_car2.brand, my_car2.model, my_car2.year);

    // Try: add a member char color[32]; and print it without setting it, then predict the output before you press Run.
    return 0;
}
