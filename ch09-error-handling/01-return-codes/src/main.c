#include <stdio.h>

#define ACCESS_OK 0
#define ACCESS_TOO_YOUNG 1

int check_access(int age) {
    if (age < 18) {
        return ACCESS_TOO_YOUNG;
    }
    printf("Access granted - you are old enough.\n");
    return ACCESS_OK;
}

int main(void) {
    int status = check_access(25);
    if (status != ACCESS_OK) {
        printf("Unexpected failure.\n");
    }

    int age = 15;
    status = check_access(age);
    if (status == ACCESS_TOO_YOUNG) {
        printf("Access denied - you must be at least 18 years old.\n");
        printf("Age is: %d\n", age);
    }

    // Try: delete the if around the second check_access call, and predict what the program prints.
    return 0;
}
