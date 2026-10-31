#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static int compare_names(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
}

int main(void) {
    /* The array keeps the names in the order they were given, like a vector. */
    const char *names[] = {"Ada", "Grace", "Alan"};
    size_t name_count = sizeof names / sizeof names[0];

    /* The table answers lookups from each name to its length. */
    HashTable lengths;
    if (hash_table_init(&lengths, 16) != 0) {
        printf("Out of memory.\n");
        return 1;
    }
    for (size_t i = 0; i < name_count; i++) {
        hash_table_set(&lengths, names[i], (int)strlen(names[i]));
    }

    printf("Names: %zu\n", name_count);

    /* A hash table has no order, so the names are sorted here before printing, as a std::map would sort them. */
    const char *sorted[3];
    memcpy(sorted, names, sizeof sorted);
    qsort(sorted, name_count, sizeof sorted[0], compare_names);

    for (size_t i = 0; i < name_count; i++) {
        int length = 0;
        hash_table_get(&lengths, sorted[i], &length);
        printf("%s: %d\n", sorted[i], length);
    }

    hash_table_free(&lengths);

    /* Try: add "Ada" a second time to names, and predict the lengths table size, lengths.size, before you press Run. */
    return 0;
}
