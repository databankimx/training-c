#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[32];

    printf("Enter a starting number: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    int start = (int)strtol(line, NULL, 10);

    for (int i = start; i > 0; i--) {
        printf("%d\n", i);
    }
    printf("Liftoff!\n");
    return 0;
}
