#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Each word keeps its original position, so equal lengths can be ordered by it. qsort is not stable,
   so the tie-break is what makes the result the same as a stable sort would give. */
typedef struct {
    const char *word;
    size_t original;
} Entry;

static int compare_by_length(const void *a, const void *b) {
    const Entry *x = a;
    const Entry *y = b;
    size_t lx = strlen(x->word);
    size_t ly = strlen(y->word);
    if (lx != ly) {
        return lx < ly ? -1 : 1;
    }
    return x->original < y->original ? -1 : (x->original > y->original ? 1 : 0);
}

int main(void) {
    const char *words[] = {"pear", "fig", "banana", "kiwi"};
    size_t count = sizeof words / sizeof words[0];

    Entry entries[4];
    for (size_t i = 0; i < count; i++) {
        entries[i].word = words[i];
        entries[i].original = i;
    }

    qsort(entries, count, sizeof entries[0], compare_by_length);

    printf("By length:");
    for (size_t i = 0; i < count; i++) {
        printf(" %s", entries[i].word);
    }
    printf("\n");
    return 0;
}
