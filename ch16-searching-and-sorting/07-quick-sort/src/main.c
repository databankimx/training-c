#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Writes one trace frame. Places marked in done are final, and are shown in green. */
static void emit_frame(FILE *file, int *first, const int values[], size_t n, const size_t compare[], size_t compare_count,
                       const unsigned char done[], const char *message) {
    if (!*first) {
        fprintf(file, ",\n");
    }
    *first = 0;
    fprintf(file, "{\"array\": [");
    for (size_t k = 0; k < n; k++) {
        fprintf(file, "%s%d", k == 0 ? "" : ", ", values[k]);
    }
    fprintf(file, "], \"compare\": [");
    for (size_t k = 0; k < compare_count; k++) {
        fprintf(file, "%s%zu", k == 0 ? "" : ", ", compare[k]);
    }
    fprintf(file, "], \"sorted\": [");
    int printed = 0;
    for (size_t k = 0; k < n; k++) {
        if (done[k]) {
            fprintf(file, "%s%zu", printed ? ", " : "", k);
            printed = 1;
        }
    }
    fprintf(file, "], \"message\": \"%s\"}", message);
}

/* Partitions values[lo, hi) around its last value, the pivot. Returns the pivot's final index. */
static size_t partition(int values[], size_t n, size_t lo, size_t hi, long *comparisons, long *swaps,
                        unsigned char done[], FILE *trace, int *first) {
    size_t pivot_index = hi - 1;
    int pivot = values[pivot_index];
    size_t next = lo;
    char message[160];

    for (size_t j = lo; j + 1 < hi; j++) {
        (*comparisons)++;
        size_t compare[2] = {j, pivot_index};
        if (trace) {
            snprintf(message, sizeof message, "Compare %d with the pivot %d.", values[j], pivot);
            emit_frame(trace, first, values, n, compare, 2, done, message);
        }
        if (values[j] < pivot) {
            if (next != j) {
                int temp = values[next];
                values[next] = values[j];
                values[j] = temp;
                (*swaps)++;
                if (trace) {
                    size_t swap_pair[2] = {next, j};
                    emit_frame(trace, first, values, n, swap_pair, 2, done, "Smaller than the pivot, so swap it to the boundary.");
                }
            }
            next++;
        }
    }

    if (next != pivot_index) {
        int temp = values[next];
        values[next] = values[pivot_index];
        values[pivot_index] = temp;
        (*swaps)++;
        if (trace) {
            size_t swap_pair[2] = {next, pivot_index};
            emit_frame(trace, first, values, n, swap_pair, 2, done, "Move the pivot into its final place.");
        }
    }
    done[next] = 1;
    return next;
}

/* Sorts values[lo, hi) by partitioning around a pivot, then sorting each side. */
static void quick_sort_range(int values[], size_t n, size_t lo, size_t hi, long *comparisons, long *swaps,
                             unsigned char done[], FILE *trace, int *first) {
    if (hi - lo <= 1) {
        if (hi - lo == 1) {
            done[lo] = 1;
        }
        return;
    }
    size_t pivot_index = partition(values, n, lo, hi, comparisons, swaps, done, trace, first);
    quick_sort_range(values, n, lo, pivot_index, comparisons, swaps, done, trace, first);
    quick_sort_range(values, n, pivot_index + 1, hi, comparisons, swaps, done, trace, first);
}

/* Sorts the whole array, and returns 0, or -1 when memory runs out. */
static int quick_sort(int values[], size_t n, long *comparisons, long *swaps, FILE *trace) {
    unsigned char *done = calloc(n, sizeof *done);
    if (done == NULL) {
        return -1;
    }
    int first = 1;
    quick_sort_range(values, n, 0, n, comparisons, swaps, done, trace, &first);
    free(done);
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

    /* The trace uses its own copy, so the sort shown on screen starts from the scrambled order. */
    int scrambled[20];
    memcpy(scrambled, small, sizeof small);

    long comparisons = 0;
    long swaps = 0;
    quick_sort(small, small_count, &comparisons, &swaps, NULL);
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
    quick_sort(big, big_count, &comparisons, &swaps, NULL);
    printf("Timing list: %zu values, from -1000 to 1000\n", big_count);
    printf("First three after sorting: %d %d %d\n", big[0], big[1], big[2]);
    printf("Last three after sorting: %d %d %d\n", big[big_count - 3], big[big_count - 2], big[big_count - 1]);
    printf("Comparisons: %ld, swaps: %ld\n", comparisons, swaps);
    printf("Sorted correctly: %s\n", is_sorted(big, big_count) ? "yes" : "no");
    free(big);

    FILE *trace = fopen("trace.js", "w");
    if (trace == NULL) {
        printf("Could not write trace.js for the visualizer.\n");
    } else {
        fprintf(trace, "window.trace = {\"title\": \"Quick sort\", \"frames\": [\n");
        int *copy = malloc(small_count * sizeof *copy);
        unsigned char *done = calloc(small_count, sizeof *done);
        if (copy != NULL && done != NULL) {
            memcpy(copy, scrambled, sizeof scrambled);
            long trace_comparisons = 0;
            long trace_swaps = 0;
            int first = 1;
            quick_sort_range(copy, small_count, 0, small_count, &trace_comparisons, &trace_swaps, done, trace, &first);
            for (size_t k = 0; k < small_count; k++) {
                done[k] = 1;
            }
            emit_frame(trace, &first, copy, small_count, NULL, 0, done, "The array is sorted.");
        }
        free(copy);
        free(done);
        fprintf(trace, "\n]};\n");
        fclose(trace);
    }

    // Try: change the visualized list to 1 through 20 in order, and predict the comparison count before you press Run.
    return 0;
}
