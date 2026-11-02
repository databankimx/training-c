#include <stdio.h>

/* Returns the index of the first match, or -1 if no element matches. comparisons counts every element looked at. */
static long linear_search(const int values[], size_t count, int target, long *comparisons) {
    for (size_t i = 0; i < count; i++) {
        (*comparisons)++;
        if (values[i] == target) {
            return (long)i;
        }
    }
    return -1;
}

/* Turns the index into a word, so -1 never prints as a position. */
static void describe(long index, long comparisons) {
    if (index < 0) {
        printf("NOT FOUND after %ld comparisons\n", comparisons);
    } else {
        printf("index %ld after %ld comparisons\n", index, comparisons);
    }
}

/* Writes trace.js for the visualizer: one frame per comparison, in the shape visualize.html reads. */
static int write_linear_trace(const char *path, const int values[], size_t count, int target) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return -1;
    }

    fprintf(file, "window.trace = {\"title\": \"Linear search\", \"target\": %d, \"frames\": [\n", target);
    int found_at = -1;
    for (size_t i = 0; i < count; i++) {
        if (values[i] == target) {
            found_at = (int)i;
            break;
        }
    }

    size_t last = found_at >= 0 ? (size_t)found_at : count - 1;
    for (size_t step = 0; step <= last; step++) {
        fprintf(file, "{\"array\": [");
        for (size_t k = 0; k < count; k++) {
            fprintf(file, "%s%d", k == 0 ? "" : ", ", values[k]);
        }
        fprintf(file, "], \"compare\": [%zu], \"found\": %d, \"message\": \"", step,
                (found_at >= 0 && (int)step == found_at) ? found_at : -1);
        if (found_at >= 0 && step == (size_t)found_at) {
            fprintf(file, "Found %d at index %zu.", target, step);
        } else {
            fprintf(file, "Index %zu holds %d, which is not %d.", step, values[step], target);
        }
        fprintf(file, "\"}%s\n", (found_at >= 0 && step == last) ? "" : ",");
    }
    if (found_at < 0) {
        fprintf(file, "{\"array\": [");
        for (size_t k = 0; k < count; k++) {
            fprintf(file, "%s%d", k == 0 ? "" : ", ", values[k]);
        }
        fprintf(file, "], \"compare\": [], \"found\": -1, \"message\": \"%d is not in the list, after checking every value.\"}\n", target);
    }

    fprintf(file, "]};\n");
    fclose(file);
    return 0;
}

int main(void) {
    /* The short list is in no particular order, so every value and its position is visible. */
    int small[] = {4, 7, 10, 0, 2, 8, 9, 3, 5, 6, 1, 11};
    size_t small_count = sizeof small / sizeof small[0];
    printf("Data: %zu values\n", small_count);

    long comparisons = 0;
    long index = linear_search(small, small_count, 3, &comparisons);
    printf("Searching for 3: ");
    describe(index, comparisons);
    if (write_linear_trace("trace.js", small, small_count, 3) != 0) {
        printf("Could not write trace.js for the visualizer.\n");
    }

    /* The long list holds every whole number from 0 to 1000 once each, in a shuffled order. */
    int large[1001];
    for (int i = 0; i <= 1000; i++) {
        large[i] = i;
    }
    /* A fixed-seed shuffle: the same order on every run. */
    unsigned int seed = 12345;
    for (int i = 1000; i > 0; i--) {
        seed = seed * 1103515245u + 12345u;
        int j = (int)((seed >> 16) % (unsigned int)(i + 1));
        int swap = large[i];
        large[i] = large[j];
        large[j] = swap;
    }

    printf("Searching 1,001 values\n");
    comparisons = 0;
    index = linear_search(large, 1001, 737, &comparisons);
    printf("  for 737: ");
    describe(index, comparisons);

    comparisons = 0;
    index = linear_search(large, 1001, 5000, &comparisons);
    printf("  for 5000: ");
    describe(index, comparisons);

    // Try: search the short list for 12, and predict the output and comparison count before you press Run.
    return 0;
}
