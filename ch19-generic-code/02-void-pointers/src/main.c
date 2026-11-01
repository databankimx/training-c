#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Swaps two elements of any type. The size is the number of bytes in one element, so the function never needs the type. */
static void swap_elements(void *a, void *b, size_t size) {
    unsigned char *first = a;
    unsigned char *second = b;
    for (size_t i = 0; i < size; i++) {
        unsigned char temp = first[i];
        first[i] = second[i];
        second[i] = temp;
    }
}

/* Returns the index of the first element equal to target, or count when none is. The caller supplies the comparison,
   which returns 0 when two elements are equal. */
static size_t index_of(const void *base, size_t count, size_t size, const void *target,
                       int (*compare)(const void *, const void *)) {
    const unsigned char *bytes = base;
    for (size_t i = 0; i < count; i++) {
        if (compare(bytes + i * size, target) == 0) {
            return i;
        }
    }
    return count;
}

static int compare_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

/* The elements of the string array are pointers, so the comparison reads a pointer first, then compares the text. */
static int compare_string(const void *a, const void *b) {
    const char *x = *(const char *const *)a;
    const char *y = *(const char *const *)b;
    return strcmp(x, y);
}

int main(void) {
    double first = 1.5;
    double second = 2.5;
    swap_elements(&first, &second, sizeof first);
    printf("Swapped doubles: %g %g\n", first, second);

    int values[] = {4, 9, 2};
    size_t count = sizeof values / sizeof values[0];
    int wanted = 9;
    size_t position = index_of(values, count, sizeof values[0], &wanted, compare_int);
    printf("Found %d at index %zu\n", wanted, position);

    const char *names[] = {"ann", "bob", "cy"};
    size_t name_count = sizeof names / sizeof names[0];
    const char *target = "bob";
    size_t name_position = index_of(names, name_count, sizeof names[0], &target, compare_string);
    printf("Found %s at index %zu\n", target, name_position);

    int missing = 7;
    size_t missing_position = index_of(values, count, sizeof values[0], &missing, compare_int);
    if (missing_position == count) {
        printf("Not found: %d\n", missing);
    }

    // Try: change compare_int so it compares the first byte only, and predict whether 9 is still found in values.
    return 0;
}
