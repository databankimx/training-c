#include <stdio.h>

#include "hash_table.h"

int main(void) {
    const char *words[] = {"apple", "pear", "apple", "fig", "pear", "apple"};
    size_t word_count = sizeof words / sizeof words[0];

    HashTable counts;
    if (hash_table_init(&counts, 16) != 0) {
        printf("Out of memory.\n");
        return 1;
    }

    for (size_t i = 0; i < word_count; i++) {
        if (hash_table_increment(&counts, words[i]) != 0) {
            printf("Out of memory.\n");
            hash_table_free(&counts);
            return 1;
        }
    }

    printf("Distinct words: %zu\n", counts.size);

    /* Lookups are printed one at a time, since the table has no fixed order to loop over. */
    const char *queries[] = {"apple", "pear", "fig"};
    for (size_t i = 0; i < 3; i++) {
        int value = 0;
        if (hash_table_get(&counts, queries[i], &value) == 0) {
            printf("%s: %d\n", queries[i], value);
        }
    }

    int missing = 0;
    if (hash_table_get(&counts, "kiwi", &missing) != 0) {
        printf("kiwi is not in the map\n");
    }

    hash_table_free(&counts);

    /* Try: change the bucket count from 16 to 1, and predict whether the output changes before you press Run. */
    return 0;
}
