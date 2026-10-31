#include <stdio.h>

typedef struct {
    double width;
    double height;
} Rectangle;

double area(Rectangle r) {
    return r.width * r.height;
}

void scale(Rectangle *r, double factor) {
    r->width *= factor;
    r->height *= factor;
}

int main(void) {
    Rectangle r = {3.0, 2.0};
    printf("Area: %.2f\n", area(r));

    scale(&r, 2.0);
    printf("Area: %.2f\n", area(r));
    return 0;
}
