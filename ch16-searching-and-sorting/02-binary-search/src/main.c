#include <stdio.h>

/* Returns the index of target in a sorted array, or -1. comparisons counts each middle value checked. */
static long binary_search(const int values[], size_t count, int target, long *comparisons) {
    long low = 0;
    long high = (long)count - 1;
    while (low <= high) {
        long middle = (low + high) / 2;
        (*comparisons)++;
        if (values[middle] == target) {
            return middle;
        }
        if (values[middle] < target) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return -1;
}

static void describe(long index, long comparisons) {
    if (index < 0) {
        printf("NOT FOUND after %ld comparisons\n", comparisons);
    } else {
        printf("index %ld after %ld comparisons\n", index, comparisons);
    }
}

static void write_values(FILE *file, const int values[], size_t count) {
    fprintf(file, "[");
    for (size_t k = 0; k < count; k++) {
        fprintf(file, "%s%d", k == 0 ? "" : ", ", values[k]);
    }
    fprintf(file, "]");
}

/* Writes trace.js for the visualizer. Values outside the range still being searched are marked "sorted", which the page fades. */
static int write_binary_trace(const char *path, const int values[], size_t count, int target) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return -1;
    }

    fprintf(file, "window.trace = {\"title\": \"Binary search\", \"target\": %d, \"frames\": [\n", target);
    long low = 0;
    long high = (long)count - 1;
    long comparisons = 0;
    int first = 1;
    while (low <= high) {
        long middle = (low + high) / 2;
        comparisons++;

        if (!first) {
            fprintf(file, ",\n");
        }
        first = 0;

        fprintf(file, "{\"array\": ");
        write_values(file, values, count);
        fprintf(file, ", \"sorted\": [");
        int printed = 0;
        for (size_t i = 0; i < count; i++) {
            if ((long)i < low || (long)i > high) {
                fprintf(file, "%s%zu", printed ? ", " : "", i);
                printed = 1;
            }
        }
        fprintf(file, "], \"compare\": [%ld], ", middle);

        if (values[middle] == target) {
            fprintf(file, "\"found\": %ld, \"message\": \"Index %ld holds %d, which is the target.\"}", middle, middle, values[middle]);
            break;
        }
        if (values[middle] < target) {
            fprintf(file, "\"found\": -1, \"message\": \"Index %ld holds %d, which is less than %d, so the target is in the upper half.\"}", middle, values[middle], target);
            low = middle + 1;
        } else {
            fprintf(file, "\"found\": -1, \"message\": \"Index %ld holds %d, which is more than %d, so the target is in the lower half.\"}", middle, values[middle], target);
            high = middle - 1;
        }
    }
    fprintf(file, "\n]};\n");
    fclose(file);
    return 0;
}

int main(void) {
    /* The short list is sorted, so each value sits at the index that matches it. */
    int small[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    size_t small_count = sizeof small / sizeof small[0];
    printf("Sorted list: %zu values\n", small_count);

    long comparisons = 0;
    long index = binary_search(small, small_count, 7, &comparisons);
    printf("Searching for 7: ");
    describe(index, comparisons);
    if (write_binary_trace("trace.js", small, small_count, 7) != 0) {
        printf("Could not write trace.js for the visualizer.\n");
    }

    /* The long list holds every whole number from 0 to 1000, in order. */
    int large[1001];
    for (int i = 0; i <= 1000; i++) {
        large[i] = i;
    }

    printf("Sorted list: 1001 values\n");
    comparisons = 0;
    index = binary_search(large, 1001, 737, &comparisons);
    printf("  for 737: ");
    if (index < 0) {
        printf("NOT FOUND after %ld comparisons\n", comparisons);
    } else {
        printf("index %ld after %ld comparisons (linear search: %ld)\n", index, comparisons, index + 1);
    }

    comparisons = 0;
    index = binary_search(large, 1001, 5000, &comparisons);
    printf("  for 5000: ");
    describe(index, comparisons);

    // Try: search the short list for 12, and predict the output and comparison count before you press Run.
    return 0;
}
