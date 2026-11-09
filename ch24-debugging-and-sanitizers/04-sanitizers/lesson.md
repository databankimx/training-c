## Sanitizers and the static analyzer

A debugger finds a bug once you know roughly where to look. Some bugs don't show themselves until much later: a write past the end of an array that corrupts a value elsewhere, or a free of memory that was already freed. Tools that check for those mistakes help find them early, and the course has two kinds.

- **Run-time sanitizers** are built into the compiler. They check the program while it runs, and report the exact place where a mistake happened. The common ones are AddressSanitizer (`-fsanitize=address`), UndefinedBehaviorSanitizer (`-fsanitize=undefined`), and ThreadSanitizer (`-fsanitize=thread`).
- **The static analyzer** is also built into the compiler. It reads the code at compile time, and reports mistakes it can prove from the code's paths, without running the program. GCC's analyzer is `-fanalyzer`.

### What this toolchain supports

This course's runner uses the MSYS2 UCRT64 toolchain. Its sanitizer libraries aren't packaged, so a program built with `-fsanitize=address` fails to link. You can see that for yourself:

```pwsh
gcc -g -fsanitize=address san.c -o san.exe
```

```text
cannot find -lasan: No such file or directory
```

That's a limit of this environment, not of the sanitizers. The static analyzer needs no extra libraries, so it works here, and this step uses it for the memory errors from the dynamic-memory chapter.

### Using the static analyzer

Add `-fanalyzer` to the compile command. Take this program, which frees the same pointer twice:

```c
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof *p);
    free(p);
    free(p);
    return 0;
}
```

Compile it with the analyzer:

```pwsh
gcc -fanalyzer -g dbl.c -o dbl.exe
```

The analyzer reports the mistake without running the program:

```text
dbl.c: In function 'main':
dbl.c:6:5: warning: double-'free' of 'p' [CWE-415] [-Wanalyzer-double-free]
    6 |     free(p);
      |     ^~~~~~~
  'main': events 1-3
    4 |     int *p = malloc(sizeof *p);
      |              ^~~~~~~~~~~~~~~~~
      |              |
      |              (1) allocated here
    5 |     free(p);
      |     ~~~~~~~
      |     |
      |     (2) first 'free' here
    6 |     free(p);
      |     ~~~~~~~
      |     |
      |     (3) ⚠️  second 'free' here; first 'free' was at (2)
```

The report names the kind of mistake, the line where it happens, and each step that led there: where the memory was allocated, where it was first freed, and where it was freed again. Read the events in order, from the first one.

The analyzer's leak warnings are less reliable than its double-free warnings, so check for leaks by review. In `leak.c`, the block below is allocated and never freed:

```c
#include <stdlib.h>

int main(void) {
    int *p = malloc(10 * sizeof *p);
    p[0] = 1;
    return 0;
}
```

This program has a leak, and the analyzer may not report it. Find it by reading the code: every `malloc` needs a `free` on every path.

### What the analyzer can and can't do

The analyzer reports only the paths it can follow from the code. It can miss a mistake that depends on input it can't predict, and it can report a path that the program never takes. So read each warning and check it against the code, rather than assuming every warning is a bug or that a clean result means the code is correct.

It doesn't need the program to run, so it finds mistakes in code the tests never reach. Use it alongside the tests, not in place of them. The compile time is longer than a normal build, and that's the cost of the extra checking.

### Using a run-time sanitizer

On a toolchain that supports them, the sanitizers are a compile and link option. In CMake, it looks like this:

```cmake
target_compile_options(program PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
target_link_options(program PRIVATE -fsanitize=address,undefined)
```

The first line adds the checks to the compiled code, and the second links the runtime library that reports them. The `-fno-omit-frame-pointer` option keeps stack traces readable in the report. A sanitized build is slower and uses more memory, so it's used for testing, not for release.

A run-time report names the kind of error, the line where it happened, and the memory involved. Read the first report only, since later reports are often a result of the first mistake.

### What to expect

A sanitizer finds the mistakes that happen in the code that runs, and the analyzer finds the mistakes its paths can reach. Neither proves that a program is correct. Use both on your own code, and treat each warning as a bug to fix, not as noise.

---

### Quiz

*These questions are written for this course.*

````quiz
What kind of mistake does `-fanalyzer` find?
○ A mistake in the logic of a loop that gives a wrong total.
→ Not quite. That's a logic error, which needs a debugger or a test.
◉ A double free or a use after free, found from the code's paths.
→ Yes. The analyzer reports these from the code, without running the program.
○ A slow function, measured in seconds.
→ Not quite. The analyzer looks for memory mistakes, not speed.
````

````quiz
Why does this course use `-fanalyzer` rather than `-fsanitize=address` here?
○ Because the analyzer is faster to run.
→ Not quite. The reason is what the toolchain can do.
◉ Because this toolchain doesn't package the sanitizer libraries, and the analyzer needs no extra libraries.
→ Yes. The analyzer is built into the compiler, so it works without them.
○ Because the sanitizers find fewer mistakes.
→ Not quite. The two find different mistakes, and the sanitizers aren't available on this toolchain.
````

---

The static analyzer finds double frees and use after free by reading the code, and it runs with the compiler you already have. The run-time sanitizers need a toolchain that packages them, and this course's toolchain doesn't. The next step is the chapter summary, and then two homework exercises that use assertions and the debugger.
