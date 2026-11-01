## Locks

Two threads that change the same variable at the same time can get the wrong result. An increment, `total++`, is really three steps: read the value, add one, and write it back. If two threads read the same value before either writes, one of the increments is lost. That's a data race, and in C a data race is undefined behavior, which means the program's result isn't guaranteed at all.

A critical section is the Windows lock that does the job of the C++ `std::mutex`. Only one thread can hold it at a time. A thread that wants to change shared data enters the critical section first, changes the data, and leaves it. Any other thread that wants the section waits until it's free.

The shared data and its lock live together in one structure:

```c
typedef struct {
    int total;
    CRITICAL_SECTION lock;
} Counter;
```

Each increment is wrapped in the enter and leave calls:

```c
static void add_many(Counter *counter, int times) {
    for (int i = 0; i < times; i++) {
        EnterCriticalSection(&counter->lock);
        counter->total++;
        LeaveCriticalSection(&counter->lock);
    }
}
```

The C++ version used a `std::lock_guard`, which releases the mutex automatically when it goes out of scope. C has no such object, so the release is written in the loop body. It runs on every pass, because the body has no early exit between the enter and the leave. If a later edit added a `return` or a `break` between the two calls, the lock would stay held, and the other thread would wait forever. Keep the code between the calls short and free of exits.

### Sharing the counter

Both threads receive a pointer to the same `Counter`, through a `Job` structure. The argument to `CreateThread` is passed by address, so both threads change one total and use one lock. A copy of the counter would give each thread its own total, which is the mistake the C++ lesson avoids with `std::ref`.

Press **Run**. The output is:

```
Total: 200000
```

Each thread adds 100,000, and the total is 200,000 only because no increment was lost. The lock forces the threads to take turns on the shared counter.

The critical section is initialized with `InitializeCriticalSection` before the threads start, and deleted with `DeleteCriticalSection` after they finish. A lock used before it's initialized, or deleted while a thread still holds it, is a bug of its own.

### The cost of the lock

A lock makes the threads wait for each other. In this program, almost all the time goes into taking and releasing the lock, so the threads gain little from running at the same time. Real programs lock as little as they can, for as short a time as possible, and try to avoid sharing data at all. The homework shows one way to do that.

### Deadlock

Two threads that each hold a lock and wait for the other's lock will wait forever. That's a deadlock. The usual cause is taking locks in different orders in different places. A program that takes its locks in one fixed order avoids it. The C rule is the same as the C++ one, and the course has no library helper for taking several locks at once, so the order must be written in the code.

---

### Quiz

*These questions are written for this course.*

````quiz
Why can two threads that increment a shared counter without a lock get the wrong total?
○ Because the compiler refuses to build the program.
→ Not quite. The program builds, and the problem appears at run time.
◉ Because each increment reads, adds, and writes, and two threads can interleave those steps so that an update is lost.
→ Yes. That's a data race, and the result isn't guaranteed.
○ Because increments are always lost when threads run together.
→ Not quite. Lost updates can happen, but the result isn't always wrong, and the outcome isn't guaranteed either way.
````

````quiz
Why does the loop body in `add_many` have no return or break between the enter and leave calls?
○ Because C does not allow return statements inside loops.
→ Not quite. C allows both, and the rule is about the lock, not the syntax.
◉ Because an exit between the two calls would leave the critical section held, and the other thread would wait forever.
→ Yes. Without a guard object, the release must be on every path, so the code between the calls must not exit.
○ Because the critical section can only be entered once per loop.
→ Not quite. It's entered once per pass, and the loop body is what keeps the enter and leave paired.
````

---

### Try it in the runner

Remove the `EnterCriticalSection` and `LeaveCriticalSection` lines from `add_many`, and run the program several times. Predict whether the total is always 200000. It isn't guaranteed, and in practice it often comes out below 200000. A result that's correct some of the time is still a bug, since a program that is correct only sometimes is not correct. Restore the lines before you continue.

---

A critical section lets one thread at a time change shared data, and the release must be on every path out of the protected code. The chapter's last steps cover the summary and two homework exercises that split work so that little or nothing is shared.
