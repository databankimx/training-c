#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Sorts values in place. comparisons and swaps count the work done. */
static void selection_sort(int values[], size_t n, long *comparisons, long *swaps) {
    for (size_t i = 0; i + 1 < n; i++) {
        size_t smallest = i;
        for (size_t j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (values[j] < values[smallest]) {
                smallest = j;
            }
        }
        if (smallest != i) {
            int temp = values[i];
            values[i] = values[smallest];
            values[smallest] = temp;
            (*swaps)++;
        }
    }
}

static void write_values(FILE *file, const int values[], size_t count) {
    fprintf(file, "[");
    for (size_t k = 0; k < count; k++) {
        fprintf(file, "%s%d", k == 0 ? "" : ", ", values[k]);
    }
    fprintf(file, "]");
}

static void write_indexes(FILE *file, const size_t indexes[], size_t count) {
    fprintf(file, "[");
    for (size_t k = 0; k < count; k++) {
        fprintf(file, "%s%zu", k == 0 ? "" : ", ", indexes[k]);
    }
    fprintf(file, "]");
}

/* Writes trace.js for the visualizer. Places before i are final, and are marked "sorted". */
static int write_selection_trace(const char *path, const int source[], size_t n) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return -1;
    }
    int *values = malloc(n * sizeof *values);
    if (values == NULL) {
        fclose(file);
        return -1;
    }
    memcpy(values, source, n * sizeof *values);

    fprintf(file, "window.trace = {\"title\": \"Selection sort\", \"frames\": [\n");
    int first = 1;
    for (size_t i = 0; i + 1 < n; i++) {
        size_t smallest = i;
        size_t placed[32];
        size_t placed_count = 0;
        for (size_t k = 0; k < i && placed_count < 32; k++) {
            placed[placed_count++] = k;
        }

        for (size_t j = i + 1; j < n; j++) {
            size_t compare[2] = {smallest, j};
            if (!first) {
                fprintf(file, ",\n");
            }
            first = 0;
            fprintf(file, "{\"array\": ");
            write_values(file, values, n);
            fprintf(file, ", \"compare\": ");
            write_indexes(file, compare, 2);
            fprintf(file, ", \"sorted\": ");
            write_indexes(file, placed, placed_count);
            if (values[j] < values[smallest]) {
                fprintf(file, ", \"message\": \"%d is less than %d, so %d is the new smallest.\"}", values[j], values[smallest], values[j]);
                smallest = j;
            } else {
                fprintf(file, ", \"message\": \"%d is not less than %d, so the smallest is still %d.\"}", values[j], values[smallest], values[smallest]);
            }
        }

        if (smallest != i) {
            size_t swap_pair[2] = {i, smallest};
            int temp = values[i];
            values[i] = values[smallest];
            values[smallest] = temp;

            fprintf(file, ",\n{\"array\": ");
            write_values(file, values, n);
            fprintf(file, ", \"swap\": ");
            write_indexes(file, swap_pair, 2);
            fprintf(file, ", \"sorted\": ");
            write_indexes(file, placed, placed_count);
            fprintf(file, ", \"message\": \"Move the smallest value into place at index %zu.\"}", i);
        }
    }

    if (!first) {
        fprintf(file, ",\n");
    }
    fprintf(file, "{\"array\": ");
    write_values(file, values, n);
    fprintf(file, ", \"sorted\": [");
    for (size_t k = 0; k < n; k++) {
        fprintf(file, "%s%zu", k == 0 ? "" : ", ", k);
    }
    fprintf(file, "], \"message\": \"The array is sorted.\"}");
    fprintf(file, "\n]};\n");
    free(values);
    fclose(file);
    return 0;
}

static int is_sorted(const int values[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (values[i - 1] > values[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    /* The visualized list holds 1 through 20 once each, in a scrambled order. */
    int small[] = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
    size_t small_count = sizeof small / sizeof small[0];
    printf("Visualized list: %zu values\n", small_count);

    /* The trace needs the list as it was before sorting, so keep a copy. */
    int scrambled[20];
    memcpy(scrambled, small, sizeof small);

    long comparisons = 0;
    long swaps = 0;
    selection_sort(small, small_count, &comparisons, &swaps);
    printf("Sorted:");
    for (size_t i = 0; i < small_count; i++) {
        printf(" %d", small[i]);
    }
    printf("\n");
    printf("Comparisons: %ld, swaps: %ld\n", comparisons, swaps);

    /* The timing list holds every whole number from -1000 to 1000, in a fixed shuffled order. */
    size_t big_count = 2001;
    int *big = malloc(big_count * sizeof *big);
    if (big == NULL) {
        printf("Out of memory.\n");
        return 1;
    }
    for (size_t i = 0; i < big_count; i++) {
        big[i] = (int)i - 1000;
    }
    unsigned int seed = 12345;
    for (size_t i = big_count - 1; i > 0; i--) {
        seed = seed * 1103515245u + 12345u;
        size_t j = (seed >> 16) % (i + 1);
        int swap = big[i];
        big[i] = big[j];
        big[j] = swap;
    }

    comparisons = 0;
    swaps = 0;
    selection_sort(big, big_count, &comparisons, &swaps);
    printf("Timing list: %zu values, from -1000 to 1000\n", big_count);
    printf("First three after sorting: %d %d %d\n", big[0], big[1], big[2]);
    printf("Last three after sorting: %d %d %d\n", big[big_count - 3], big[big_count - 2], big[big_count - 1]);
    printf("Comparisons: %ld, swaps: %ld\n", comparisons, swaps);
    printf("Sorted correctly: %s\n", is_sorted(big, big_count) ? "yes" : "no");
    free(big);

    if (write_selection_trace("trace.js", scrambled, small_count) != 0) {
        printf("Could not write trace.js for the visualizer.\n");
    }

    // Try: change the visualized list to 1 through 20 in order, and predict the swap count before you press Run.
    return 0;
}
