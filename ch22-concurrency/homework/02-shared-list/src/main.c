#include <stdio.h>
#include <windows.h>

#define LIST_CAPACITY 10

/* A list shared by two threads. The lock is held whenever the list changes. */
typedef struct {
    int items[LIST_CAPACITY];
    size_t size;
    CRITICAL_SECTION lock;
} SharedList;

/* What each thread is given: the list, and the range of values to add. */
typedef struct {
    SharedList *list;
    int first;
    int last;
} Job;

/* Adds each value in the range while holding the lock. The lock is entered and left once per value. */
static void add_values(SharedList *list, int first, int last) {
    for (int value = first; value < last; value++) {
        EnterCriticalSection(&list->lock);
        if (list->size < LIST_CAPACITY) {
            list->items[list->size] = value;
            list->size++;
        }
        LeaveCriticalSection(&list->lock);
    }
}

static DWORD WINAPI worker(LPVOID argument) {
    Job *job = argument;
    add_values(job->list, job->first, job->last);
    return 0;
}

int main(void) {
    SharedList list = {{0}, 0, {0}};
    InitializeCriticalSection(&list.lock);

    Job low = {&list, 1, 6};
    Job high = {&list, 6, 11};

    HANDLE first = CreateThread(NULL, 0, worker, &low, 0, NULL);
    HANDLE second = CreateThread(NULL, 0, worker, &high, 0, NULL);
    if (first == NULL || second == NULL) {
        printf("Could not start the threads.\n");
        DeleteCriticalSection(&list.lock);
        return 1;
    }

    WaitForSingleObject(first, INFINITE);
    WaitForSingleObject(second, INFINITE);
    CloseHandle(first);
    CloseHandle(second);

    long sum = 0;
    for (size_t i = 0; i < list.size; i++) {
        sum += list.items[i];
    }
    printf("Size: %zu\n", list.size);
    printf("Sum: %ld\n", sum);

    DeleteCriticalSection(&list.lock);
    return 0;
}
