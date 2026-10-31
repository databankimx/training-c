#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int scores[3];
    char line[32];

    printf("Score 1: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    scores[0] = (int)strtol(line, NULL, 10);

    printf("Score 2: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    scores[1] = (int)strtol(line, NULL, 10);

    printf("Score 3: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    scores[2] = (int)strtol(line, NULL, 10);

    int highest = scores[0];
    if (scores[1] > highest) {
        highest = scores[1];
    }
    if (scores[2] > highest) {
        highest = scores[2];
    }

    printf("The highest score is %d\n", highest);
    return 0;
}
