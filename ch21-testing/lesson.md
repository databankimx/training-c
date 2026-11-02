## Ch21 · Testing

A program that compiles and runs isn't necessarily correct. Tests are how the answers get checked against what the code should do, and how that checking keeps working as the code changes. This chapter covers writing checks by hand, running them through CTest, and the habits that make a test worth having.

The steps are:

* [Checking results](#goto/01-checking-results): writing checks with known answers, and reading the output of a failing one.
* [Running tests with CTest](#goto/02-running-tests): registering a test with `add_test`, and using the exit code as the result.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. C has no test framework in its standard library, so the checks are written by hand, and CTest runs them.*
