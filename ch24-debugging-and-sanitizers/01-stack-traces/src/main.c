#include <stdio.h>

/* Records the name of the function it's written in, as the call starts. The output reads as the chain of calls. */
#define TRACE() printf("  in %s\n", __func__)

static int inner(int value) {
    TRACE();
    if (value < 0) {
        /* The failure is reported here, with the calls that led to it already printed above. */
        printf("inner failed: value %d is negative\n", value);
        return -1;
    }
    return value * 2;
}

static int middle(int value) {
    TRACE();
    return inner(value);
}

int main(void) {
    TRACE();
    int result = middle(-5);
    printf("main got %d\n", result);

    // Try: change middle(-5) to middle(5), and predict how many lines the trace prints before you press Run.
    return 0;
}
