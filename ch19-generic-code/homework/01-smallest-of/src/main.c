#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Returns a pointer to the smallest element, or NULL when count is 0. The comparison decides the order. */
static const void *smallest_of(const void *base, size_t count, size_t size,
                               int (*compare)(const void *, const void *)) {
    if (count == 0) {
        return NULL;
    }
    const unsigned char *bytes = base;
    const void *smallest = bytes;
    for (size_t i = 1; i < count; i++) {
        const void *element = bytes + i * size;
        if (compare(element, smallest) < 0) {
            smallest = element;
        }
    }
    return smallest;
}

static int compare_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static int compare_string(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

int main(void) {
    int numbers[] = {5, 2, 9};
    const int *smallest_number = smallest_of(numbers, 3, sizeof numbers[0], compare_int);
    printf("Smallest number: %d\n", *smallest_number);

    const char *words[] = {"pear", "apple", "fig"};
    const char *const *smallest_word = smallest_of(words, 3, sizeof words[0], compare_string);
    printf("Smallest word: %s\n", *smallest_word);

    /* The extension's empty case: smallest_of returns NULL, so the caller must check before it reads the result. */
    const void *none = smallest_of(numbers, 0, sizeof numbers[0], compare_int);
    printf("Empty array: %s\n", none == NULL ? "no smallest value" : "has a value");
    return 0;
}
