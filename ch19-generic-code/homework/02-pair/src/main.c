#include <stdio.h>

/* C has no class templates. Each combination of types gets its own structure, written out by hand.
   This is what the compiler would generate from a template. */

typedef struct {
    int first;
    const char *second;
} IntStringPair;

typedef struct {
    const char *first;
    double second;
} StringDoublePair;

static IntStringPair make_int_string_pair(int first, const char *second) {
    IntStringPair pair = {first, second};
    return pair;
}

static StringDoublePair make_string_double_pair(const char *first, double second) {
    StringDoublePair pair = {first, second};
    return pair;
}

static void print_int_string_pair(const IntStringPair *pair) {
    printf("Pair: %d %s\n", pair->first, pair->second);
}

static void print_string_double_pair(const StringDoublePair *pair) {
    printf("Pair: %s %g\n", pair->first, pair->second);
}

int main(void) {
    IntStringPair numbers = make_int_string_pair(3, "three");
    print_int_string_pair(&numbers);

    StringDoublePair constant = make_string_double_pair("pi", 3.14);
    print_string_double_pair(&constant);

    return 0;
}
