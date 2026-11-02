#include <stdio.h>

int factorial_recursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial_recursive(n - 1);
}

int factorial_loop(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void) {
    for (int n = 0; n <= 10; n++) {
        int recursive = factorial_recursive(n);
        int looped = factorial_loop(n);
        printf("%d! = %d (%s)\n", n, recursive, recursive == looped ? "agree" : "differ");
    }
    return 0;
}
