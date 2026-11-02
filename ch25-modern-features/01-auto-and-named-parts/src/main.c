#include <stdio.h>

/* A record with named parts. C has no structured bindings, so each part is read by its name. */
typedef struct {
    const char *name;
    int score;
} Score;

int main(void) {
    /* The scores are kept in name order, since C has no map that sorts them for us. */
    Score scores[] = {
        {"Ada", 91},
        {"Grace", 88},
    };
    size_t count = sizeof scores / sizeof scores[0];

    /* With C23, auto takes the type from the initializer, the same as in C++. */
    for (size_t i = 0; i < count; i++) {
        const Score *entry = &scores[i];
        printf("%s: %d\n", entry->name, entry->score);
    }

    auto total = 3;
    auto average = 4.5;
    printf("%d %g\n", total, average);

    // Try: add {"Linus", 95} to the end of scores, and predict the line order before you press Run. The array keeps the order it was written in.
    return 0;
}
