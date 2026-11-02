#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[32];

    printf("Enter a year: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    int year = (int)strtol(line, NULL, 10);

    bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    if (leap) {
        printf("%d is a leap year.\n", year);
    } else {
        printf("%d is not a leap year.\n", year);
    }
    return 0;
}
