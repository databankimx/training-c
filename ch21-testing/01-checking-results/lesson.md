## Checking results

A program that runs without crashing isn't necessarily correct. A test is a check that a piece of code gives the answer it should, for inputs where the answer is known. Tests are how a team keeps code correct as it changes, and writing them is part of writing the code.

C has no test framework in its standard library, so the checks are written by hand. The simplest test is a comparison, reported in a clear form. Here's the checker from `src/main.c`:

```c
static void check(int passed, const char *name, int *failures) {
    if (passed) {
        printf("PASS %s\n", name);
    } else {
        printf("FAIL %s\n", name);
        (*failures)++;
    }
}
```

The function prints one line per check and counts the failures. The `failures` parameter is a pointer to the count, so the increment made inside `check` is visible in `main`. Each test is then a single line in `main`:

```c
check(add(2, 3) == 5, "add 2 and 3", &failures);
```

The first argument is the comparison, which is true when the function gives the expected answer. The second is a name, so the output says which test it was.

Press **Run**. The output is:

```
PASS add 2 and 3
PASS add -4 and 4
PASS add 0 and 0
FAIL add 2 and 3 expects 6
Failures: 1
```

The last check is wrong on purpose. The expected answer, 6, is not what `add` returns for 2 and 3, so the check fails. The program then exits with code 1, which the runner shows as the finish line. A program that passes every check exits with code 0.

A failing test can mean the code is wrong, or the test is wrong. Here it's the test, and the lesson is to work out which one before you change anything.

### Good tests

A good test has three properties:

* **It has a known answer.** You work the answer out first, from the specification, not by reading the code's output.
* **It covers the edges.** Zero, negative numbers, and the largest and smallest values are where code tends to break.
* **It has a name that says what it checks.** When it fails, the name tells you where to look.

A test that only checks one easy input proves little. Several cases, including the edges, show much more.

### Edges in C

The largest and smallest values are the cases where C's arithmetic misbehaves. Adding to `INT_MAX` overflows, which is undefined behavior for a signed `int`, so a test for the edge shows the danger before the code meets it. The `<limits.h>` header provides the limits, and a test that uses them states the edge in the code, not in a comment.

---

### Quiz

*These questions are written for this course.*

````quiz
Why should the expected answer in a test be worked out before the code runs?
○ Because the test is faster to write that way.
→ Not quite. The reason is correctness, not speed.
◉ So that the test checks the code against a known answer, rather than confirming whatever the code produces.
→ Yes. A test copied from the program's output proves nothing.
○ Because the compiler needs the answer to build the program.
→ Not quite. The compiler doesn't use test answers.
````

````quiz
Which set of inputs is most useful for testing an add function?
○ Only 2 and 3.
→ Not quite. One easy case shows little about the rest of the function.
◉ Zero, negative numbers, and a mix of signs, along with ordinary values.
→ Yes. Those are the inputs where a mistake is most likely to show.
○ Only the largest number the program can store.
→ Not quite. The edges are useful, but a test needs more than one kind of input.
````

---

### Try it in the runner

Change the expectation in the last check from 6 to 5, and predict the failure count before you press **Run**. All four checks pass, so the output ends with `Failures: 0`, and the program exits with code 0. The wrong test was the one that failed, not `add`.

---

A check reports whether a result matches a known answer, and a set of checks covers the cases where code is likely to go wrong. The next step makes the checks part of the build, so the runner's Test button runs them.
