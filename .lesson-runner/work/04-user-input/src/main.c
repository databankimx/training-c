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
    int age = (int)strtol(line, NULL, 10);

    printf("Hello, %s. In ten years you will be %d.\n", name, age + 10);

    // Try: enter a name, then type ten as the age, and predict the last line before you press Run.
    return 0;
}
