#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static int compare_words(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

int main(void) {
    const char *words[] = {"red", "blue", "red", "green", "blue", "red"};
    size_t word_count = sizeof words / sizeof words[0];

    HashTable counts;
    if (hash_table_init(&counts, 16) != 0) {
        printf("Out of memory.\n");
        return 1;
    }

    /* Keep one copy of each distinct word, so the table's order doesn't matter when printing. */
    const char *distinct[6];
    size_t distinct_count = 0;
    for (size_t i = 0; i < word_count; i++) {
        int seen = 0;
        if (hash_table_get(&counts, words[i], &seen) != 0) {
            distinct[distinct_count++] = words[i];
        }
        hash_table_increment(&counts, words[i]);
    }

    qsort(distinct, distinct_count, sizeof distinct[0], compare_words);

    const char *best_word = NULL;
    int best_count = 0;
    for (size_t i = 0; i < distinct_count; i++) {
        int count = 0;
        hash_table_get(&counts, distinct[i], &count);
        printf("%s: %d\n", distinct[i], count);
        if (count > best_count) {
            best_count = count;
            best_word = distinct[i];
        }
    }

    printf("Most common: %s\n", best_word);

    hash_table_free(&counts);
    return 0;
}
