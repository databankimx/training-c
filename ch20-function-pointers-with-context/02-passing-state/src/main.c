#include <stdio.h>

/* A context that holds a copy of the factor, made when the context is created. Later changes to the original don't reach it. */
typedef struct {
    int factor;
} ScaleContext;

/* A context that refers to the original total, so each call changes the caller's variable. */
typedef struct {
    int *total;
} AccumulatorContext;

static ScaleContext make_scale_context(int factor) {
    ScaleContext context = {factor};
    return context;
}

static int scale_by_copy(const ScaleContext *context, int x) {
    return x * context->factor;
}

static void add_to(AccumulatorContext *context, int x) {
    *context->total += x;
}

int main(void) {
    int factor = 3;
    ScaleContext scale = make_scale_context(factor);
    factor = 10;
    printf("Scaled by copy: %d\n", scale_by_copy(&scale, 5));

    int total = 0;
    AccumulatorContext accumulator = {&total};
    add_to(&accumulator, 4);
    add_to(&accumulator, 6);
    printf("Total by reference: %d\n", total);

    // Try: change make_scale_context to store a pointer to factor instead of a copy, and predict the scaled value before you press Run.
    return 0;
}
