#include <stdio.h>
#include <stdlib.h>

double rectangle_area(double width, double height) {
    return width * height;
}

double circle_area(double radius) {
    const double pi = 3.14159;
    return pi * radius * radius;
}

int main(void) {
    char line[64];

    printf("Enter a width: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    double width = strtod(line, NULL);

    printf("Enter a height: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    double height = strtod(line, NULL);

    printf("Enter a radius: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    double radius = strtod(line, NULL);

    printf("Rectangle area: %.2f\n", rectangle_area(width, height));
    printf("Circle area: %.2f\n", circle_area(radius));
    return 0;
}
