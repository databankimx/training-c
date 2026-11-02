#include <stdio.h>

int main(void) {
    int number = 10;
    printf("%d\n", number);

    number = 15;
    printf("%d\n", number);

    float small = 5.75f;
    double large = 19.99;
    printf("float: %g\n", small);
    printf("double: %g\n", large);

    double scientific = 35e3;
    float scientific_f = 35e3f;
    double big = 12E4;
    printf("%g %g\n", scientific, big);
    printf("%g\n", scientific_f);

    char letter = 'a';
    char code = 97;
    printf("%c %c %d\n", letter, code, 'a' + 1);

    int x = 5, y = 6, z = 50;
    printf("%d %d %d\n", x, y, z);

    int first, second, third;
    first = second = third = 50;
    printf("%d %d %d\n", first, second, third);

    const double pi = 3.14159;
    printf("%.5f\n", pi);

    // Try: change pi to 3.0, and predict the last line before you press Run.
    return 0;
}
