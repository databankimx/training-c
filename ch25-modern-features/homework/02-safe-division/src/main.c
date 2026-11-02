#include <stdbool.h>
#include <stdio.h>

/* A quotient that may be missing. found is false when the divisor was zero, so there is no answer. */
typedef struct {
    bool found;
    int quotient;
} MaybeQuotient;

static MaybeQuotient safe_divide(int a, int b) {
    MaybeQuotient result = {false, 0};
    if (b != 0) {
        result.found = true;
        result.quotient = a / b;
    }
    return result;
}

static void print_division(int a, int b) {
    MaybeQuotient result = safe_divide(a, b);
    if (result.found) {
        printf("%d / %d = %d\n", a, b, result.quotient);
    } else {
        printf("%d / %d = no answer\n", a, b);
    }
}

int main(void) {
    print_division(10, 2);
    print_division(1, 0);
    print_division(9, 3);
    return 0;
}
