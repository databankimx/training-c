#include <stdio.h>
#include <windows.h>

/* What each thread is given: the range to add, and the place to store its own result. */
typedef struct {
    int first;
    int last;
    long long *total;
} Range;

/* Adds the numbers from first up to, but not including, last. Writes only to its own total, so no lock is needed. */
static void sum_range(int first, int last, long long *total) {
    long long sum = 0;
    for (int i = first; i < last; i++) {
        sum += i;
    }
    *total = sum;
}

static DWORD WINAPI worker(LPVOID argument) {
    Range *range = argument;
    sum_range(range->first, range->last, range->total);
    return 0;
}

int main(void) {
    long long first_half = 0;
    long long second_half = 0;

    Range low = {1, 501, &first_half};
    Range high = {501, 1001, &second_half};

    HANDLE first = CreateThread(NULL, 0, worker, &low, 0, NULL);
    HANDLE second = CreateThread(NULL, 0, worker, &high, 0, NULL);
    if (first == NULL || second == NULL) {
        printf("Could not start the threads.\n");
        return 1;
    }

    WaitForSingleObject(first, INFINITE);
    WaitForSingleObject(second, INFINITE);
    CloseHandle(first);
    CloseHandle(second);

    printf("Sum: %lld\n", first_half + second_half);
    return 0;
}
