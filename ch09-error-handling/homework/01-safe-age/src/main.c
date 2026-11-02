#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define AGE_OK 0
#define AGE_NOT_A_NUMBER 1
#define AGE_OUT_OF_RANGE 2
#define AGE_END_OF_INPUT 3

int read_age(int *age) {
    char line[64];
    if (fgets(line, sizeof line, stdin) == NULL) {
        return AGE_END_OF_INPUT;
    }

    char *end = line;
    long value = strtol(line, &end, 10);
    if (end == line || (*end != '\n' && *end != '\0')) {
        return AGE_NOT_A_NUMBER;
    }
    if (value < 0 || value > 120) {
        return AGE_OUT_OF_RANGE;
    }

    *age = (int)value;
    return AGE_OK;
}

int main(void) {
    while (true) {
        printf("Enter your age (0-120): ");
        fflush(stdout);

        int age = 0;
        int status = read_age(&age);
        if (status == AGE_OK) {
            printf("Age accepted: %d\n", age);
            break;
        }
        if (status == AGE_END_OF_INPUT) {
            printf("No more input.\n");
            return 1;
        }
        if (status == AGE_NOT_A_NUMBER) {
            printf("not a number\n");
        } else {
            printf("age must be from 0 to 120\n");
        }
    }
    return 0;
}
