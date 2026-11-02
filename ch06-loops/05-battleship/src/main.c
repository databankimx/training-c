#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int ships[4][4] = {
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    };
    int hits = 0;
    int turns = 0;
    char line[64];

    printf("Battleship: find the four ships. Type q to quit.\n");
    while (hits < 4) {
        printf("Row (0-3): ");
        fflush(stdout);
        if (fgets(line, sizeof line, stdin) == NULL) {
            break;
        }
        if (line[0] == 'q' || line[0] == 'Q') {
            break;
        }
        char *row_end = line;
        long row = strtol(line, &row_end, 10);
        if (row_end == line) {
            printf("Please type a number.\n\n");
            continue;
        }

        printf("Column (0-3): ");
        fflush(stdout);
        if (fgets(line, sizeof line, stdin) == NULL) {
            break;
        }
        if (line[0] == 'q' || line[0] == 'Q') {
            break;
        }
        char *column_end = line;
        long column = strtol(line, &column_end, 10);
        if (column_end == line) {
            printf("Please type a number.\n\n");
            continue;
        }

        if (row < 0 || row > 3 || column < 0 || column > 3) {
            printf("Please choose numbers from 0 to 3.\n\n");
            continue;
        }

        turns++;
        if (ships[row][column] == 1) {
            ships[row][column] = 0;
            hits++;
            printf("Hit! %d left.\n\n", 4 - hits);
        } else {
            printf("Miss\n\n");
        }
    }

    printf("Game over after %d turns, with %d ships left.\n", turns, 4 - hits);

    // Try: change hits < 4 to hits < 3, and predict how the game ends before you press Run.
    return 0;
}
