#include <stdio.h>

#define MEMO_SIZE 64

/* Returns 0 when n is valid, or -1 when it's negative. Checked once, before any recursion starts. */
static int check_n(int n) {
    if (n < 0) {
        return -1;
    }
    return 0;
}

/* The naive version follows the definition exactly. Every call makes its own calls, so the same values are rebuilt again and again. */
static long long fib_naive_helper(int n, long long *calls) {
    (*calls)++;
    if (n < 2) {
        return n;
    }
    return fib_naive_helper(n - 1, calls) + fib_naive_helper(n - 2, calls);
}

/* The memoized version stores each value the first time it's worked out. -1 means "not yet computed". */
static long long fib_memo_helper(int n, long long memo[], long long *calls) {
    (*calls)++;
    if (n < 2) {
        return n;
    }
    if (memo[n] >= 0) {
        return memo[n];
    }
    long long result = fib_memo_helper(n - 1, memo, calls) + fib_memo_helper(n - 2, memo, calls);
    memo[n] = result;
    return result;
}

/* The loop keeps the last two values, and moves forward once for each step. */
static long long fib_loop(int n) {
    long long previous = 0;
    long long current = 1;
    if (n == 0) {
        return 0;
    }
    for (int i = 1; i < n; i++) {
        long long next = previous + current;
        previous = current;
        current = next;
    }
    return current;
}

int main(void) {
    int sizes[] = {10, 20, 30};
    for (size_t i = 0; i < 3; i++) {
        int n = sizes[i];
        long long naive_calls = 0;
        long long memo_calls = 0;
        long long memo[MEMO_SIZE];
        for (int k = 0; k < MEMO_SIZE; k++) {
            memo[k] = -1;
        }

        long long naive_value = fib_naive_helper(n, &naive_calls);
        long long memo_value = fib_memo_helper(n, memo, &memo_calls);
        long long loop_value = fib_loop(n);

        printf("n = %d: value %lld, naive calls %lld, memoized calls %lld", n, naive_value, naive_calls, memo_calls);
        if (naive_value != memo_value || memo_value != loop_value) {
            printf(" (MISMATCH)");
        }
        printf("\n");
    }

    int refused = -1;
    if (check_n(refused) != 0) {
        printf("n = %d refused: n must not be negative\n", refused);
    }

    /* Try: change the naive call for n = 10 so it doesn't call fib_naive_helper(n - 2, calls), and predict the naive count before you press Run. */
    return 0;
}
