## Running tests with CTest

Checks in `main` are useful, but a person has to read the output to see whether they passed. The build system can do better. CTest is the test runner that comes with CMake. It runs a program and reads the result from its exit code: zero means the test passed, and anything else means it failed. The runner's **Test** button runs CTest for you.

The program in this step follows that rule. Here's the end of `main`, from `src/main.c`:

```c
printf("Failures: %d\n", failures);
return failures == 0 ? 0 : 1;
```

The conditional operator from the decisions chapter gives 0 when no check failed, and 1 when any did. That single number is the test result.

The test is registered in the step's `CMakeLists.txt`:

```cmake
enable_testing()
add_test(NAME clamp_checks COMMAND program)
```

`enable_testing` turns on CTest for the project, and `add_test` names the test and the program that runs it. The runner's **Test** button builds the step, then runs CTest, and reports the result.

### The function under test

The program checks a `clamp` function, which limits a value to a range:

```c
static int clamp(int value, int low, int high) {
    if (value < low) {
        return low;
    }
    if (value > high) {
        return high;
    }
    return value;
}
```

A value inside the range is returned unchanged. A value below the range becomes the low end, and a value above it becomes the high end. The five checks cover each of those cases, plus the two ends of the range, which are the edges where a mistake would show.

Press **Run**. The output is:

```
PASS inside the range stays the same
PASS below the range becomes the low end
PASS above the range becomes the high end
PASS the low end stays the same
PASS the high end stays the same
Failures: 0
```

Press **Test** to run the same checks through CTest. The runner reports that the test passed, because the exit code is 0.

### Why exit codes matter

A program's exit code is how the rest of the system learns whether it succeeded. Build scripts, continuous integration, and CTest all read it. A test that only prints PASS and FAIL is readable by people, but a test that returns a failing exit code is readable by machines too, and that's what makes automated checking possible.

---

### Quiz

*These questions are written for this course.*

````quiz
What does CTest use to decide whether a test passed?
○ The words the program prints.
→ Not quite. CTest doesn't read the output text.
◉ The program's exit code, where zero means success.
→ Yes. Any other value means the test failed.
○ The number of lines the program prints.
→ Not quite. The count of lines has no meaning for the test result.
````

````quiz
What does `add_test(NAME clamp_checks COMMAND program)` do?
○ It compiles the program.
→ Not quite. The compile happens from add_executable.
◉ It registers a test named clamp_checks, which runs the program and reads its exit code.
→ Yes. That's what makes the Test button and ctest work.
○ It copies the program into the test folder.
→ Not quite. The test runs the program where it's built.
````

---

### Try it in the runner

Change the low end in the second check to 10, so the check fails, and predict the exit code before you press **Test**. The result is 1, since one check failed, and CTest reports the test as failed.

---

CTest turns the checks into a test the build system can run, and the exit code carries the result. The next chapter steps are a summary, two homework exercises that write tests of their own, and the chapter overview.
