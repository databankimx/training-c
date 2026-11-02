#include <stdio.h>

/* C has no map, so the words are kept in an array in alphabetical order. The order is set by hand, as the lesson explains. */
typedef struct {
    const char *word;
    int count;
} WordCount;

int main(void) {
    WordCount counts[] = {
        {"apple", 3},
        {"fig", 2},
        {"pear", 5},
    };
    size_t count = sizeof counts / sizeof counts[0];

    for (size_t i = 0; i < count; i++) {
        const WordCount *entry = &counts[i];
        printf("%s %d\n", entry->word, entry->count);
    }

    int total = 0;
    for (size_t i = 0; i < count; i++) {
        total += counts[i].count;
    }
    printf("Total: %d\n", total);
    return 0;
}
