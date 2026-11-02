#include <stdio.h>

#define MEMO_SIZE 64

/* Returns 0 when n is valid, or -1 when it's negative. */
static int check_n(int n) {
    if (n < 0) {
        return -1;
    }
    return 0;
}

static long long ways_naive_helper(int n, long long *calls) {
    (*calls)++;
    if (n < 2) {
        return 1;
    }
    return ways_naive_helper(n - 1, calls) + ways_naive_helper(n - 2, calls);
}

static long long ways_memo_helper(int n, long long memo[], long long *calls) {
    (*calls)++;
    if (n < 2) {
        return 1;
    }
    if (memo[n] >= 0) {
        return memo[n];
    }
    long long result = ways_memo_helper(n - 1, memo, calls) + ways_memo_helper(n - 2, memo, calls);
    memo[n] = result;
    return result;
}

int main(void) {
    int sizes[] = {5, 10};
    for (size_t i = 0; i < 2; i++) {
        int n = sizes[i];
        long long naive_calls = 0;
        long long memo_calls = 0;
        long long memo[MEMO_SIZE];
        for (int k = 0; k < MEMO_SIZE; k++) {
            memo[k] = -1;
        }

        long long naive_value = ways_naive_helper(n, &naive_calls);
        long long memo_value = ways_memo_helper(n, memo, &memo_calls);
        printf("n = %d: ways %lld, naive calls %lld, memoized calls %lld", n, naive_value, naive_calls, memo_calls);
        if (memo_value != naive_value) {
            printf(" (MISMATCH)");
        }
        printf("\n");
    }

    int refused = -1;
    if (check_n(refused) != 0) {
        printf("n = %d refused: n must not be negative\n", refused);
    }
    return 0;
}
