#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[32];

    printf("Enter a number: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    int number = (int)strtol(line, NULL, 10);

    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", number, i, number * i);
    }
    return 0;
}
