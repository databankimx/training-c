## Assertions

Some conditions should never be false if the program is correct. A function that divides by a value must never be given zero. A sorted array must stay sorted. An index must stay in range. An assertion states such a condition in the code, and checks it while the program runs, so a broken assumption is caught at the point where it breaks, rather than later as a wrong answer.

C provides the `assert` macro in `<assert.h>`. Here's the function from `src/main.c`:

```c
static int divide(int a, int b) {
    assert(b != 0);
    return a / b;
}
```

If the condition is true, `assert` does nothing. If it's false, the program stops, and prints a message that includes the condition, the file, the line, and the function. Nothing after the failed assertion runs, and the program exits with a non-zero code.

Press **Run**. The output is:

```
All assertions passed
```

The runner builds in Debug mode, which leaves assertions switched on. The two calls in `main` are true, so the program runs to the end.

### Assertions are for bugs

An assertion checks a promise the program makes to itself, not input from a user. If a user types zero, the program should say so and handle it, for example by returning an error code, as the error-handling chapter showed, because that's a condition that can happen. An assertion should only fire when the code is wrong, and then the right response is to fix the code.

For that reason, a failing assertion is a bug report, and the message is written for the programmer who has to find the cause.

### Assertions in release builds

In a release build, assertions are removed. The `assert` macro checks the `NDEBUG` symbol, and when that symbol is defined it expands to nothing. CMake defines `NDEBUG` for release builds, so the checks cost nothing at run time, which is why they can be used freely while developing. The cost is that a condition checked only by an assertion is no longer checked in release. If a check must always happen, it belongs in an `if` with a proper error, not in an assertion.

### Assertions and side effects

The expression inside `assert` disappears in a release build, so it must never change anything the program needs. `assert(fgets(line, sizeof line, stdin) != NULL);` would skip the read in a release build, which is a serious bug that a debug build would never show. Keep the work outside the assertion, and let the assertion only test a result that's already been computed.

---

### Quiz

*These questions are written for this course.*

````quiz
What should an assertion check?
○ Input that a user types.
→ Not quite. User input can be wrong in ways the program has to handle, so it needs an error path, not an assertion.
◉ A condition that should always be true if the code is correct.
→ Yes. A failed assertion means a bug in the program.
○ The result of a function that prints to the screen.
→ Not quite. An assertion checks a condition, and printing isn't one.
````

````quiz
Why does the `assert` macro vanish in a release build?
○ Because it makes the program's output wrong.
→ Not quite. Assertions don't change what a correct program prints.
◉ Because it expands to nothing when NDEBUG is defined, and CMake defines NDEBUG for release builds.
→ Yes. That's why a check that must always happen belongs in an if, not an assertion.
○ Because the compiler doesn't support assert in release builds.
→ Not quite. The preprocessor removes it, based on the NDEBUG symbol.
````

---

### Try it in the runner

Add `divide(1, 0);` before the final message, and predict what the program prints and its exit code before you press **Run**. The assertion fails, so the program prints a message naming the condition `b != 0`, the file, the line, and the function, then stops with a non-zero exit code. The message `All assertions passed` doesn't print.

---

An assertion turns a broken promise into an immediate, visible failure while the program is being developed. The next step is a bug hunt, where a program runs and gives the wrong answer, and the debugger shows where it goes wrong.
