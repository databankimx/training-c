#include <stdio.h>
#include <string.h>

/* Counts the pairs (i, j) with i before j and values[i] greater than values[j]. */
static long count_inversions(const int values[], size_t n) {
    long inversions = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (values[i] > values[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}

/* Runs insertion sort on a copy of the array and returns its move count. The caller's array is not changed. */
static long insertion_moves(const int values[], size_t n) {
    int copy[16];
    /* UNSAFE PATH: copy has room for 16 values. A longer list would write past the end of copy, so this
       function must only be called with n of 16 or fewer. */
    memcpy(copy, values, n * sizeof copy[0]);
    long moves = 0;
    for (size_t i = 1; i < n; i++) {
        size_t j = i;
        while (j > 0 && copy[j - 1] > copy[j]) {
            int temp = copy[j - 1];
            copy[j - 1] = copy[j];
            copy[j] = temp;
            moves++;
            j--;
        }
    }
    return moves;
}

int main(void) {
    int list[] = {5, 1, 4, 2, 3};
    size_t n = sizeof list / sizeof list[0];

    long inversions = count_inversions(list, n);
    long moves = insertion_moves(list, n);
    printf("Inversions: %ld\n", inversions);
    printf("Insertion sort moves: %ld\n", moves);
    printf("Match: %s\n", inversions == moves ? "yes" : "no");

    int ordered[] = {1, 2, 3, 4, 5};
    printf("Ordered list: %ld inversions, %ld moves\n", count_inversions(ordered, 5), insertion_moves(ordered, 5));
    return 0;
}
