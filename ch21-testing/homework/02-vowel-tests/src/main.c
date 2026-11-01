#include <stdio.h>
#include <string.h>

/* Counts the lowercase vowels a, e, i, o, and u in a word. */
static int count_vowels(const char *word) {
    int count = 0;
    for (const char *p = word; *p != '\0'; p++) {
        if (strchr("aeiou", *p) != NULL && *p != '\0') {
            count++;
        }
    }
    return count;
}

static void check(int passed, const char *name, int *failures) {
    if (passed) {
        printf("PASS %s\n", name);
    } else {
        printf("FAIL %s\n", name);
        (*failures)++;
    }
}

int main(void) {
    int failures = 0;

    check(count_vowels("hello") == 2, "hello has 2 vowels", &failures);
    check(count_vowels("") == 0, "an empty word has no vowels", &failures);
    check(count_vowels("rhythm") == 0, "rhythm has no vowels", &failures);
    check(count_vowels("education") == 5, "education has 5 vowels", &failures);

    printf("Failures: %d\n", failures);
    return failures == 0 ? 0 : 1;
}
