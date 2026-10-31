#include <stdio.h>

void swap_nums(int *x, int *y) {
    int z = *x;
    *x = *y;
    *y = z;
}

int main(void) {
    int first = 10;
    int second = 20;
    printf("%d %d\n", first, second);

    swap_nums(&first, &second);
    printf("%d %d\n", first, second);

    // Try: write swap_copies(int x, int y) with the same body but no pointers, and predict what main prints.
    return 0;
}
