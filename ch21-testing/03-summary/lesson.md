## Summary: Testing

This chapter covered checking code against known answers, and running those checks through the build system.

* **A test compares a result with a known answer.** Work the expected answer out from the specification, not from the program's output.
* **Cover the edges.** Zero, negative values, and the ends of a range are where mistakes tend to show.
* **Name each test.** The name tells you where to look when it fails.
* **A failing test may mean the test is wrong.** Check the expectation before changing the code.
* **A checker counts failures through a pointer.** The `check` function prints each result and adds to the count in `main`.
* **The exit code carries the result.** `main` returns zero when every check passed, and one otherwise.
* **CTest runs a program as a test.** `add_test` registers it, and the exit code decides the result.
* **The runner's Test button runs CTest.** It's the same mechanism a team's build uses.

### Check your understanding

*These questions are written for this course.*

````quiz
Why are the edges of a range good test inputs?
○ Because they are the easiest to compute.
→ Not quite. Ease of computing isn't the reason.
◉ Because mistakes in code often show at the boundaries, such as an off-by-one error.
→ Yes. Boundaries are where conditions change, so they're where errors hide.
○ Because the compiler checks them automatically.
→ Not quite. The compiler doesn't check the results of tests.
````

````quiz
A test fails. What is the first thing to check?
○ Whether the program is too slow.
→ Not quite. Speed isn't what a failing test is measuring.
◉ Whether the expected answer is correct, since the test may be wrong.
→ Yes. Checking the expectation first avoids changing correct code.
○ Whether the compiler version is old.
→ Not quite. That's rarely the reason a test fails.
````

````quiz
What exit code tells CTest that a test passed?
○ 1
→ Not quite. A non-zero exit code means the test failed.
◉ 0
→ Yes. Zero is success, and CTest treats any other value as a failure.
○ The number of checks that ran.
→ Not quite. The exit code is a plain success or failure signal.
````
