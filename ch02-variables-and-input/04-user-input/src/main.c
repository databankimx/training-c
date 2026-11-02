#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char text[128];
    char line[32];

    printf("Enter some text: ");
    fflush(stdout);
    if (fgets(text, sizeof text, stdin) == NULL) {
        return 1;
    }
    text[strcspn(text, "\n")] = '\0';
    printf("You entered: %s\n", text);

    printf("Enter a number: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    int x = (int)strtol(line, NULL, 10);
    printf("You entered: %d\n", x);

    printf("Enter another number: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    int y = (int)strtol(line, NULL, 10);
    printf("You entered: %d\n", y);

    printf("%d + %d = %d\n", x, y, x + y);

    // Try: at the second prompt, type hello instead of a number, and predict the sum before you press Run.
    return 0;
}
