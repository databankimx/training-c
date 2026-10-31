#include <stdio.h>

int main(void) {
    char letters[2][4] = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'}
    };
    printf("%c\n", letters[1][2]);
    printf("%c\n", letters[0][3]);

    int grid[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    printf("Center: %d\n", grid[1][1]);
    printf("Sum of the first row: %d\n", grid[0][0] + grid[0][1] + grid[0][2]);

    grid[2][0] = 0;
    printf("Bottom-left: %d\n", grid[2][0]);

    // Try: change the index to grid[1][2], and predict the value before you press Run.
    return 0;
}
