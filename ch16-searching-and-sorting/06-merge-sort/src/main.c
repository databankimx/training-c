#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Writes one trace frame. compare lists the indexes being checked, and the sorted range is shown in green. */
static void emit_frame(FILE *file, int *first, const int values[], size_t n, const size_t compare[], size_t compare_count,
                       size_t sorted_lo, size_t sorted_hi, const char *message) {
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
    for (size_t k = sorted_lo; k < sorted_hi; k++) {
        fprintf(file, "%s%zu", k == sorted_lo ? "" : ", ", k);
    }
    fprintf(file, "], \"message\": \"%s\"}", message);
}

/* Merges the sorted runs values[lo, mid) and values[mid, hi). comparisons counts each pair of front values checked. */
static void merge_runs(int values[], int temp[], size_t n, size_t lo, size_t mid, size_t hi,
                       long *comparisons, FILE *trace, int *first) {
    size_t left = lo;
    size_t right = mid;
    size_t out = lo;
    char message[160];

    while (left < mid && right < hi) {
        (*comparisons)++;
        size_t compare[2] = {left, right};
        if (trace) {
            snprintf(message, sizeof message, "Compare %d and %d: take the smaller one.", values[left], values[right]);
            emit_frame(trace, first, values, n, compare, 2, 0, 0, message);
        }
        if (values[left] <= values[right]) {
            temp[out++] = values[left++];
        } else {
            temp[out++] = values[right++];
        }
    }
    while (left < mid) {
        temp[out++] = values[left++];
    }
    while (right < hi) {
        temp[out++] = values[right++];
    }
    for (size_t k = lo; k < hi; k++) {
        values[k] = temp[k];
    }

    if (trace) {
        snprintf(message, sizeof message, "The run from index %zu to %zu is merged and in order.", lo, hi - 1);
        emit_frame(trace, first, values, n, NULL, 0, lo, hi, message);
    }
}

/* Sorts values[lo, hi) by splitting it, sorting each half, and merging. Calls itself on each half. */
static void merge_sort_range(int values[], int temp[], size_t n, size_t lo, size_t hi,
                             long *comparisons, FILE *trace, int *first) {
    if (hi - lo <= 1) {
        return;
    }
    size_t mid = lo + (hi - lo) / 2;
    if (trace) {
        char message[160];
        snprintf(message, sizeof message, "Split indexes %zu to %zu into two halves.", lo, hi - 1);
        emit_frame(trace, first, values, n, NULL, 0, 0, 0, message);
    }
    merge_sort_range(values, temp, n, lo, mid, comparisons, trace, first);
    merge_sort_range(values, temp, n, mid, hi, comparisons, trace, first);
    merge_runs(values, temp, n, lo, mid, hi, comparisons, trace, first);
}

/* Sorts the whole array. The temporary array is the extra space the Big O section counts. */
static int merge_sort(int values[], size_t n, long *comparisons, FILE *trace) {
    int *temp = malloc(n * sizeof *temp);
    if (temp == NULL) {
        return -1;
    }
    int first = 1;
    merge_sort_range(values, temp, n, 0, n, comparisons, trace, &first);
    free(temp);
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
    merge_sort(small, small_count, &comparisons, NULL);
    printf("Sorted:");
    for (size_t i = 0; i < small_count; i++) {
        printf(" %d", small[i]);
    }
    printf("\n");
    printf("Comparisons: %ld\n", comparisons);

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
    merge_sort(big, big_count, &comparisons, NULL);
    printf("Timing list: %zu values, from -1000 to 1000\n", big_count);
    printf("First three after sorting: %d %d %d\n", big[0], big[1], big[2]);
    printf("Last three after sorting: %d %d %d\n", big[big_count - 3], big[big_count - 2], big[big_count - 1]);
    printf("Comparisons: %ld\n", comparisons);
    printf("Sorted correctly: %s\n", is_sorted(big, big_count) ? "yes" : "no");
    free(big);

    FILE *trace = fopen("trace.js", "w");
    if (trace == NULL) {
        printf("Could not write trace.js for the visualizer.\n");
    } else {
        fprintf(trace, "window.trace = {\"title\": \"Merge sort\", \"frames\": [\n");
        int first = 1;
        long trace_comparisons = 0;
        int *copy = malloc(small_count * sizeof *copy);
        if (copy != NULL) {
            memcpy(copy, scrambled, sizeof scrambled);
            int *temp = malloc(small_count * sizeof *temp);
            if (temp != NULL) {
                merge_sort_range(copy, temp, small_count, 0, small_count, &trace_comparisons, trace, &first);
                emit_frame(trace, &first, copy, small_count, NULL, 0, 0, small_count, "The array is sorted.");
                free(temp);
            }
            free(copy);
        }
        fprintf(trace, "\n]};\n");
        fclose(trace);
    }

    // Try: change the visualized list to 1 through 20 in order, and predict the comparison count before you press Run.
    return 0;
}
