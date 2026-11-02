#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    char line[32];

    printf("Enter a day number (1-7): ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    int number = (int)strtol(line, NULL, 10);

    if (number < 1 || number > 7) {
        printf("That isn't a valid day number.\n");
    } else {
        int index = number - 1;
        printf("Day %d is %s\n", number, days[index]);
    }
    return 0;
}
