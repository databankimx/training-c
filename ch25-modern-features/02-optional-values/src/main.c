#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

/* A result that may be missing. found says whether index holds an answer, so the caller can't read an empty result by mistake. */
typedef struct {
    bool found;
    size_t index;
} MaybeIndex;

/* Returns the position of the first match, with found set, or with found cleared when there is no match. */
static MaybeIndex find_index(const int values[], size_t count, int target) {
    for (size_t i = 0; i < count; i++) {
        if (values[i] == target) {
            MaybeIndex result = {true, i};
            return result;
        }
    }
    MaybeIndex result = {false, 0};
    return result;
}

/* The C form of value_or: the index when one is present, and the fallback otherwise. */
static long index_or(MaybeIndex maybe, long fallback) {
    return maybe.found ? (long)maybe.index : fallback;
}

int main(void) {
    int values[] = {4, 8, 5};
    size_t count = sizeof values / sizeof values[0];

    MaybeIndex found = find_index(values, count, 8);
    if (found.found) {
        printf("Found at %zu\n", found.index);
    }

    MaybeIndex missing = find_index(values, count, 99);
    if (!missing.found) {
        printf("Not found\n");
    }
    printf("%ld\n", index_or(missing, -1));

    // Try: call find_index for 4, and print index_or of that result with a fallback of -1. Predict the output before you press Run.
    return 0;
}
