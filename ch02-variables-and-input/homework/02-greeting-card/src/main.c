#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char name[64];
    char line[32];

    printf("What is your name? ");
    fflush(stdout);
    if (fgets(name, sizeof name, stdin) == NULL) {
        return 1;
    }
    name[strcspn(name, "\n")] = '\0';

    printf("How old are you? ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    const int age = (int)strtol(line, NULL, 10);

    printf("Hello, %s.\n", name);
    printf("Next year you will be %d.\n", age + 1);
    return 0;
}
