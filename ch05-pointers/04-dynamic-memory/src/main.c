#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Ask the heap for room for three ints. The memory lives until we free it. */
    int *numbers = malloc(3 * sizeof *numbers);
    if (numbers == NULL) {
        printf("Out of memory.\n");
        return 1;
    }
    numbers[0] = 10;
    numbers[1] = 20;
    numbers[2] = 30;
    printf("%d %d %d\n", numbers[0], numbers[1], numbers[2]);

    /* Grow the block to five ints. realloc may move it, so use its result, and keep the old pointer until it succeeds. */
    int *grown = realloc(numbers, 5 * sizeof *grown);
    if (grown == NULL) {
        free(numbers);
        return 1;
    }
    numbers = grown;
    numbers[3] = 40;
    numbers[4] = 50;
    printf("%d %d\n", numbers[3], numbers[4]);

    /* calloc fills the block with zeros. */
    int *zeros = calloc(2, sizeof *zeros);
    if (zeros == NULL) {
        free(numbers);
        return 1;
    }
    printf("%d %d\n", zeros[0], zeros[1]);

    //free(zeros);
    free(numbers);
    numbers = NULL;

    /* Try: delete the line numbers = NULL;, add a second free(numbers); after the first, and predict the result before you press Run. */
    return 0;
}
