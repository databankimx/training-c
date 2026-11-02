#include <stdio.h>

typedef struct Shape Shape;

struct Shape {
    double (*area)(const Shape *self);
};

typedef struct {
    Shape base;
    double width;
    double height;
} Rectangle;

typedef struct {
    Shape base;
    double radius;
} Circle;

double shape_area_default(const Shape *self) {
    (void)self;
    return 0.0;
}

double rectangle_area(const Shape *self) {
    const Rectangle *r = (const Rectangle *)self;
    return r->width * r->height;
}

double circle_area(const Shape *self) {
    const Circle *c = (const Circle *)self;
    return 3.14159 * c->radius * c->radius;
}

Rectangle make_rectangle(double width, double height) {
    Rectangle r = {{rectangle_area}, width, height};
    return r;
}

Circle make_circle(double radius) {
    Circle c = {{circle_area}, radius};
    return c;
}

void print_area(const Shape *shape) {
    printf("Area: %.2f\n", shape->area(shape));
}

int main(void) {
    Rectangle rect = make_rectangle(3.0, 2.0);
    print_area(&rect.base);

    Circle circle = make_circle(1.0);
    print_area(&circle.base);

    Shape plain = {shape_area_default};
    print_area(&plain);

    return 0;
}
