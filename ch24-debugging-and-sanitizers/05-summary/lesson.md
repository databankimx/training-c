## Summary: Debugging and sanitizers

This chapter covered the tools for finding bugs once a program is written, and what each one can and can't show. C's standard library provides few of them, so the chapter uses the hand-written call path, the assertion, the Windows debugger, and GCC's static analyzer on this toolchain, and explains the run-time sanitizers.

* **A call path shows how the program got somewhere.** A `TRACE` macro built on `__func__` records the calls as they start, and the debugger's call stack shows the real calls in progress.
* **Record traces where they are needed.** A print in every call costs time, so a trace is for finding a bug, not for normal runs.
* **An assertion checks a promise the code makes to itself.** A failed assertion is a bug, and `NDEBUG` removes the checks in release builds.
* **Assertions are not input checks.** User input needs an error path, such as a return code, not an assertion.
* **An assertion's expression must not do needed work.** The expression disappears in release builds, so the work must be kept outside it.
* **A debugger stops the program and shows its values.** Breakpoints, stepping, and the variables panel find where values go wrong.
* **Off-by-one errors live at loop boundaries.** Check the boundary condition first.
* **The static analyzer finds memory mistakes from the code.** `-fanalyzer` reports double frees and use after free, without running the program. Leaks are harder to find this way, so check them by review.
* **Run-time sanitizers need a supporting toolchain.** AddressSanitizer, UndefinedBehaviorSanitizer, and ThreadSanitizer each cover a different kind of mistake, but this course's MSYS2 UCRT64 setup doesn't package them.

### Check your understanding

*These questions are written for this course.*

````quiz
What does a failed assertion tell you?
○ That the user typed an invalid value.
→ Not quite. A bad input is handled with an error path, not an assertion.
◉ That the code broke a promise it makes to itself, which is a bug to fix.
→ Yes. An assertion states a condition that must hold if the code is correct.
○ That the program is running too slowly.
→ Not quite. Assertions check conditions, not speed.
````

````quiz
Which option finds a second free of the same pointer, without running the program?
○ A call path recorded with TRACE.
→ Not quite. A call path shows the calls, not the memory being freed.
◉ GCC's static analyzer, with the `-fanalyzer` option.
→ Yes. It reads the code's paths, and reports the double free with the line where it happens.
○ A release build.
→ Not quite. Release builds are faster, but they don't check memory.
````

````quiz
An off-by-one error is most likely to be found where?
○ In the output formatting.
→ Not quite. Output formatting rarely causes an off-by-one.
◉ At the boundary condition of a loop, where the first and last values are decided.
→ Yes. The boundary is the first place to check.
○ In the header file.
→ Not quite. Headers rarely hold loop boundaries.
````
