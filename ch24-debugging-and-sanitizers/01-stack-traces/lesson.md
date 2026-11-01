## Call paths

When a program fails deep inside a call, the error message tells you what went wrong, but not how the program got there. A stack trace is the list of functions that were running at that moment, from the innermost call out to `main`. It answers the question "who called this?", which is often the first thing you need to know.

C++ captures this with `std::stacktrace`. The C standard library has no equivalent, so this step records the path by hand. Each function announces itself as it starts, using `__func__`, which holds the function's name:

```c
#define TRACE() printf("  in %s\n", __func__)
```

Every function in the chain begins with `TRACE();`. Here's the chain from `src/main.c`: `main` calls `middle`, and `middle` calls `inner`, which finds a negative value and reports it:

```c
static int inner(int value) {
    TRACE();
    if (value < 0) {
        printf("inner failed: value %d is negative\n", value);
        return -1;
    }
    return value * 2;
}
```

Press **Run**. The output is:

```
  in main
  in middle
  in inner
inner failed: value -5 is negative
main got -1
```

The first three lines are the call path, read from the outermost call inward, and the failure comes after them. The order shows who called whom: `main` called `middle`, which called `inner`.

### The debugger's call stack

A hand-written trace is useful, but it has to be written in advance, and it costs a line in every function. The Windows debugger shows the real call stack for any program, without any extra code. When the program stops at a breakpoint, the Call Stack panel lists the functions from the innermost outward, with their line numbers, as the C++ lesson's Backtrace option did.

The runner's debug build adds symbols to the program, which is what lets the debugger name each function and line. The build setting is the same one the Backtrace checkbox controls in the C++ course. A stripped build can show only addresses, so turn on debug information when diagnosing a problem.

### The cost

A hand-written trace adds a print to every call, which slows a program that calls its functions often. Use it while finding a bug, then remove it. The debugger has no cost while the program runs normally, so it's the better tool once you can start the program under it.

---

### Quiz

*These questions are written for this course.*

````quiz
What does the trace from `TRACE()` show?
○ The values of every variable in the program.
→ Not quite. The trace shows which functions have started, not their variables.
◉ The chain of function calls that led to the current point, from the outermost call inward.
→ Yes. Each function prints its name as it starts, which reads as who called whom.
○ The lines of code that were never reached.
→ Not quite. The trace shows the calls that are in progress.
````

````quiz
Why is the Windows debugger's call stack better than a hand-written trace for a program you're not changing?
○ Because the debugger makes the program faster.
→ Not quite. The debugger shows the stack, and doesn't change how fast the code runs.
◉ Because it needs no print in each function, and shows the real call stack when the program stops.
→ Yes. A debugger reads the stack the program already has, so no code has to change.
○ Because hand-written traces can't show function names.
→ Not quite. They can, through __func__, but they need code in each function.
````

---

### Try it in the runner

Change `middle(-5)` to `middle(5)`, and predict how many lines the trace prints before you press **Run**. The trace prints three lines, one each for `main`, `middle`, and `inner`, and no failure message appears, since 5 is not negative. The output ends with `main got 10`. Restore `-5` before you continue.

---

A recorded or debugged call path turns a failure into a route through the program, which shows who called the code that went wrong. The next step covers assertions, which check conditions that must always hold.
