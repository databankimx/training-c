#include <math.h>
#include <stdio.h>

int main(void) {
    int a = 7;
    int b = 2;

    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);
    printf("a / b = %d\n", a / b);
    printf("a %% b = %d\n", a % b);

    double c = 7.0;
    printf("c / b = %.1f\n", c / b);
    printf("a / 2.0 = %.1f\n", a / 2.0);

    double average = (double)a / b;
    printf("average to two places = %.2f\n", average);

    printf("2 + 3 * 4 = %d\n", 2 + 3 * 4);
    printf("(2 + 3) * 4 = %d\n", (2 + 3) * 4);
    printf("10 - 4 - 3 = %d\n", 10 - 4 - 3);

    int count = 0;
    count++;
    count += 5;
    printf("count = %d\n", count);

    int x = 5;
    int before = x++;
    int after = ++x;
    printf("before = %d, after = %d, x = %d\n", before, after, x);

    int total = 10;
    total -= 3;
    total *= 2;
    total /= 4;
    total %= 4;
    printf("total = %d\n", total);

    printf("max(a, b) = %d\n", (a > b) ? a : b);
    printf("min(a, b) = %d\n", (a < b) ? a : b);
    printf("sqrt(16) = %.2f\n", sqrt(16.0));
    printf("round(2.6) = %.2f\n", round(2.6));
    printf("pow(2, 10) = %.2f\n", pow(2.0, 10));

    // Try: change b to 4, and predict a / b and a % b before you press Run.
    return 0;
}
