#include <stdio.h>

/* A macro is expanded by the preprocessor, so it works for any type that supports > and the conditional operator.
   Every use of a and b in the expansion is a separate evaluation, which matters when they have side effects. */
#define LARGER_OF(a, b) ((a) > (b) ? (a) : (b))

/* The same job as a function. Each argument is evaluated once, and the types are checked by the compiler. */
static int larger_int(int a, int b) {
    return a > b ? a : b;
}

static int calls = 0;

/* Each call has a side effect: it counts itself, and returns a new value. */
static int next_value(void) {
    calls++;
    return calls * 10;
}

int main(void) {
    printf("LARGER_OF(3, 7) = %d\n", LARGER_OF(3, 7));
    printf("LARGER_OF(2.5, 1.5) = %g\n", LARGER_OF(2.5, 1.5));
    printf("larger_int(3, 7) = %d\n", larger_int(3, 7));

    /* next_value() returns 10 on its first call, which is more than 5, so the macro uses its first argument.
       The expansion names that argument twice, so the call runs twice and the result is the second value, 20. */
    calls = 0;
    int macro_result = LARGER_OF(next_value(), 5);
    printf("LARGER_OF(next_value(), 5) = %d after %d calls\n", macro_result, calls);

    calls = 0;
    int function_result = larger_int(next_value(), 5);
    printf("larger_int(next_value(), 5) = %d after %d calls\n", function_result, calls);

    // Try: replace LARGER_OF(next_value(), 5) with LARGER_OF(next_value(), 50), and predict the call count before you press Run.
    return 0;
}
