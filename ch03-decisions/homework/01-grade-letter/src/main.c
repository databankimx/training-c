#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[32];

    printf("Enter a score (0-100): ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    int score = (int)strtol(line, NULL, 10);

    char letter;
    if (score >= 90) {
        letter = 'A';
    } else if (score >= 80) {
        letter = 'B';
    } else if (score >= 70) {
        letter = 'C';
    } else if (score >= 60) {
        letter = 'D';
    } else {
        letter = 'F';
    }

    printf("Your grade is %c\n", letter);
    return 0;
}
