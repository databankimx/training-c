#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[64];

    printf("Enter an operator (+, -, *, /): ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    char op = line[0];

    printf("Enter the first number: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    double first = strtod(line, NULL);

    printf("Enter the second number: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    double second = strtod(line, NULL);

    switch (op) {
        case '+':
            printf("%g\n", first + second);
            break;
        case '-':
            printf("%g\n", first - second);
            break;
        case '*':
            printf("%g\n", first * second);
            break;
        case '/':
            if (second == 0) {
                printf("Cannot divide by zero.\n");
            } else {
                printf("%g\n", first / second);
            }
            break;
        default:
            printf("Unknown operator.\n");
            break;
    }
    return 0;
}
