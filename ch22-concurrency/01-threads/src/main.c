#include <stdio.h>
#include <windows.h>

/* The function the new thread runs. Windows passes one argument, and it returns a status code. */
static DWORD WINAPI greet(LPVOID argument) {
    const char *name = argument;
    printf("Hello from %s\n", name);
    return 0;
}

int main(void) {
    printf("Start\n");

    /* CreateThread starts the thread at once, as std::thread does. */
    HANDLE worker = CreateThread(NULL, 0, greet, (LPVOID)"worker", 0, NULL);
    if (worker == NULL) {
        printf("Could not start the thread.\n");
        return 1;
    }

    /* WaitForSingleObject is the join: it waits until the thread has finished. */
    WaitForSingleObject(worker, INFINITE);
    CloseHandle(worker);

    printf("After join\n");

    // Try: start a second thread with the name "helper", and join it after the first, before you press Run.
    return 0;
}
