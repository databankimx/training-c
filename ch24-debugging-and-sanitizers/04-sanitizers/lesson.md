## Sanitizers

A debugger finds a bug once you know roughly where to look. Some bugs don't show themselves until much later: a write past the end of an array that corrupts a value elsewhere, or a read of a variable that was never set. Sanitizers are tools built into the compiler that check for those mistakes while the program runs, and they report the exact place where the mistake happened.

The common ones are:

* **AddressSanitizer** (`-fsanitize=address`) finds reads and writes outside an array or a block, and memory that is used after it's freed. It's the check that would have found the double free and use after free from the dynamic-memory chapter.
* **UndefinedBehaviorSanitizer** (`-fsanitize=undefined`) finds signed overflow, division by zero, and some misuse of pointers, which C leaves undefined.
* **ThreadSanitizer** (`-fsanitize=thread`) finds data races, like the one in the concurrency chapter.

A sanitized build is slower and uses more memory, so it's used for testing, not for release.

### What this toolchain supports

This course's runner uses the MSYS2 UCRT64 toolchain. On that toolchain, the sanitizer libraries aren't packaged, so a program built with `-fsanitize=address` fails to link here. That's a limit of this environment, not of the sanitizers themselves. Because of that, this step explains the sanitizers without running them.

The assertion and call-path steps in this chapter do run here, and they cover the most common debugging needs. For the memory errors, the course has a different tool that does work on Windows: Dr. Memory, fetched by the script in the dynamic-memory chapter. Dr. Memory checks allocations and frees as the program runs, and it reports leaks, double frees, and use after free, which covers much of what AddressSanitizer does for heap memory. A team that needs the sanitizers themselves should use a toolchain that supports them, such as GCC or Clang on Linux.

### Using a sanitizer

On a supported toolchain, a sanitizer is a compile and link option. In CMake, it looks like this:

```cmake
target_compile_options(program PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
target_link_options(program PRIVATE -fsanitize=address,undefined)
```

The first line adds the checks to the compiled code, and the second links the runtime library that reports them. The `-fno-omit-frame-pointer` option keeps stack traces readable in the report.

A sanitizer report names the kind of error, the line where it happened, and the memory involved. Read the first report only, since later reports are often a result of the first mistake.

### What to expect

A sanitizer finds the mistakes that happen in the code that runs. It doesn't find mistakes in code paths the tests never reach, so a clean sanitizer run is evidence, not proof. Run the tests under a sanitizer as well as in a normal build, and treat any report as a bug to fix, not as noise.

---

### Quiz

*These questions are written for this course.*

````quiz
What kind of mistake does AddressSanitizer find?
○ A mistake in the logic of a loop that gives a wrong total.
→ Not quite. That's a logic error, which needs a debugger or a test.
◉ A read or write outside an array, or use of memory after it's freed.
→ Yes. Those errors often corrupt data silently, which is why a sanitizer helps.
○ A slow function, measured in seconds.
→ Not quite. Sanitizers look for memory and undefined behavior, not speed.
````

````quiz
Why should a sanitized build not be used for release?
○ Because sanitizers change the output of a correct program.
→ Not quite. A correct program prints the same thing, with the checks active.
◉ Because the checks make the program slower and use more memory.
→ Yes. Sanitizers are for testing, where that cost is worth paying.
○ Because the compiler refuses to build release programs with sanitizers.
→ Not quite. The compiler allows it, but the cost is usually too high for release.
````

---

A sanitizer finds memory mistakes and undefined behavior while the program runs, and reports where they happen. This course's toolchain can't run them, so Dr. Memory covers the heap errors on Windows. The next step is the chapter summary, and then two homework exercises that use assertions and the debugger.
