#include <stdio.h>

int add_five(int x) {
    return 5 + x;
}

int add_ints(int x, int y) {
    return x + y;
}

double add_doubles(double x, double y) {
    return x + y;
}

int main(void) {
    int res = add_five(3);
    printf("%d\n", res);

    int whole = add_ints(8, 5);
    double decimal = add_doubles(4.3, 6.26);
    printf("Int: %d\n", whole);
    printf("Double: %.2f\n", decimal);

    // Try: call add_ints(8, 5.0), and predict the value before you press Run.
    return 0;
}
