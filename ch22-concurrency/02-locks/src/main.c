#include <stdio.h>
#include <windows.h>

/* The shared total, and the critical section that protects it. */
typedef struct {
    int total;
    CRITICAL_SECTION lock;
} Counter;

/* What each thread is given: the shared counter and how many increments to make. */
typedef struct {
    Counter *counter;
    int times;
} Job;

/* Each pass takes the lock, adds one, and releases it. C has no lock_guard, so the release is written
   in the loop body, and it runs on every pass. */
static void add_many(Counter *counter, int times) {
    for (int i = 0; i < times; i++) {
        EnterCriticalSection(&counter->lock);
        counter->total++;
        LeaveCriticalSection(&counter->lock);
    }
}

static DWORD WINAPI worker(LPVOID argument) {
    Job *job = argument;
    add_many(job->counter, job->times);
    return 0;
}

int main(void) {
    Counter counter = {0};
    InitializeCriticalSection(&counter.lock);

    Job job = {&counter, 100000};
    HANDLE first = CreateThread(NULL, 0, worker, &job, 0, NULL);
    HANDLE second = CreateThread(NULL, 0, worker, &job, 0, NULL);
    if (first == NULL || second == NULL) {
        printf("Could not start the threads.\n");
        return 1;
    }

    WaitForSingleObject(first, INFINITE);
    WaitForSingleObject(second, INFINITE);
    CloseHandle(first);
    CloseHandle(second);

    printf("Total: %d\n", counter.total);
    DeleteCriticalSection(&counter.lock);

    // Try: remove the EnterCriticalSection and LeaveCriticalSection lines from add_many, run several times, and predict whether the total is always 200000.
    return 0;
}
