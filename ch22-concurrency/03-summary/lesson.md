## Summary: Concurrency

This chapter covered running work on several threads, and keeping shared data safe when they touch it. The course uses the Windows thread and critical-section functions, and the points below apply to the C++ thread and mutex types the lessons compare them with.

* **A thread runs alongside the code that started it.** `CreateThread` starts it, and the argument is passed as a pointer, so the data it points to must stay alive until the thread is done.
* **`WaitForSingleObject` is the join.** A thread must be waited for, and its handle closed, before the code that depends on it continues.
* **Output from threads can interleave.** Without the wait, or with unsynchronized printing, the order changes from run to run.
* **A data race is undefined behavior.** Two threads that change the same data without coordination can lose updates.
* **A critical section lets one thread through at a time.** A thread enters it before using shared data, and leaves it when done.
* **Every path must leave the critical section.** C has no guard object, so the leave call must run on every route out of the protected code.
* **Less sharing means fewer locks.** Splitting work so each thread writes its own result avoids most of the problem.
* **Deadlock comes from inconsistent lock order.** Taking locks in one fixed order avoids it.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `WaitForSingleObject` guarantee about a thread that it waits for?
○ That the thread has started.
→ Not quite. Creating the thread already starts it.
◉ That the thread has finished before the calling code continues past the wait.
→ Yes. The wait is the point where the program waits for the thread's work.
○ That the thread's output appears before the program's output.
→ Not quite. The wait orders the finish of the work, not the order of unrelated output.
````

````quiz
Why is a data race a serious bug, even when the result is sometimes correct?
○ Because it makes the program slower.
→ Not quite. The problem is correctness, not speed.
◉ Because the result isn't guaranteed, so a program that works in testing can fail later.
→ Yes. A result that is correct only some of the time is not a correct program.
○ Because the compiler refuses to build such a program.
→ Not quite. The program builds, and the problem appears at run time.
````

````quiz
Two threads each take lock A, then lock B. A third thread takes lock B, then lock A. What is the risk?
○ The program runs more slowly.
→ Not quite. The risk is that it stops making progress at all.
◉ A deadlock, in which the threads wait for each other's locks forever.
→ Yes. Taking locks in inconsistent orders is the usual cause.
○ The locks are shared, so each one counts twice.
→ Not quite. Lock counts don't change in that way.
````
