#include <stdbool.h>
#include <stdio.h>

/* A leap year is divisible by 4, except a century year, which must also be divisible by 400. */
static bool is_leap_year(int year) {
    if (year % 400 == 0) {
        return true;
    }
    if (year % 100 == 0) {
        return false;
    }
    return year % 4 == 0;
}

static void check(int passed, const char *name, int *failures) {
    if (passed) {
        printf("PASS %s\n", name);
    } else {
        printf("FAIL %s\n", name);
        (*failures)++;
    }
}

int main(void) {
    int failures = 0;

    check(is_leap_year(2024), "2024 is a leap year", &failures);
    check(!is_leap_year(1900), "1900 is not a leap year", &failures);
    check(is_leap_year(2000), "2000 is a leap year", &failures);
    check(!is_leap_year(2023), "2023 is not a leap year", &failures);

    printf("Failures: %d\n", failures);
    return failures == 0 ? 0 : 1;
}
