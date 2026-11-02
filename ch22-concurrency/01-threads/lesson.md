## Threads

So far every program has run one thread of work, one step after another. A thread is an independent sequence of work that runs alongside the others. Modern computers have several processors, and threads let a program use them at the same time, or let one part of a program wait while another keeps going.

C++ starts a thread with `std::thread`. C's standard library has a thread interface, but it isn't reliably provided by MinGW on Windows, so this course uses the Windows functions. The C++ `std::thread` has three jobs, and each has a Windows call:

* Starting the thread: `CreateThread`. The thread starts running at once.
* Waiting for it: `WaitForSingleObject`, which is the C form of `join`.
* Releasing its handle: `CloseHandle`, which the C++ thread object does when it goes out of scope.

Here's the program for this step, in `src/main.c`. The function the thread runs has the signature Windows requires:

```c
static DWORD WINAPI greet(LPVOID argument) {
    const char *name = argument;
    printf("Hello from %s\n", name);
    return 0;
}
```

The thread is started, waited for, and closed in `main`:

```c
HANDLE worker = CreateThread(NULL, 0, greet, (LPVOID)"worker", 0, NULL);
WaitForSingleObject(worker, INFINITE);
CloseHandle(worker);
```

Press **Run**. The output is:

```
Start
Hello from worker
After join
```

The `WaitForSingleObject` call is what puts the output in this order. The thread prints its message while `main` waits, and `After join` prints only once the thread has finished.

### Passing the argument

Windows passes a single `LPVOID` to the thread function, which is a `void *`. The program passes the string's address and converts it back inside `greet`. The string must still exist while the thread uses it. A string literal lives for the whole program, so it's safe here. A pointer to a local variable in `main` would be safe only if `main` waited for the thread before that variable went out of scope, which `WaitForSingleObject` ensures.

### Why waiting matters

Without the wait, `main` would carry on while the thread runs, and the two could print in either order. A thread can outlive the code that started it, and it can still be using data from the function that created it, which is a common source of bugs. The wait makes the rule explicit: the work is finished before the code that depends on it continues.

A thread whose handle is never closed keeps its resources until the program ends. `CloseHandle` releases the handle once the thread has finished, which is the step the C++ thread object's destructor performs for you.

### Output from several threads

When two threads print at once, their output can interleave in any order. A message can be split between threads in the middle of a line. The course won't show that here, because the output would differ from run to run. The next step shows how to share data between threads safely.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `WaitForSingleObject` do, in the C++ terms of this chapter?
○ It starts a new thread.
→ Not quite. CreateThread starts the thread.
◉ It is the join: it waits until the thread has finished before the calling code continues.
→ Yes. Without the wait, the two threads can run in either order.
○ It stops the thread.
→ Not quite. The wait doesn't stop the thread, it only waits for it to finish.
````

````quiz
Why must the string passed to the thread still exist while the thread runs?
○ Because Windows copies the string at the time the thread starts.
→ Not quite. Windows passes the pointer, and it doesn't copy the string.
◉ Because the thread reads it through the pointer, so a string that has gone out of scope would be read from memory that is no longer valid.
→ Yes. The pointer must stay valid for the whole time the thread can use it.
○ Because the string must be stored on the heap for threads to work.
→ Not quite. A string literal works because it lives for the whole program, not because it's on the heap.
````

---

### Try it in the runner

Add a second thread that runs `greet` with the name "helper", and wait for it after the first thread, before the `After join` line. Predict whether the two greetings always appear in the same order before you press **Run**. They might not. Without a wait between the two starts, the threads run at the same time, so the order can change from one run to the next.

---

A thread runs a function at the same time as the code that started it, and waiting for it is how the program makes sure the work is done. The next step is the harder part: two threads that change the same data, and the lock that keeps those changes from colliding.
