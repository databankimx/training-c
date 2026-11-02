## Hello, world

Every programming course starts with a program that prints a message. It's the smoke test of the whole setup: if this runs, your compiler, your build tools, and the runner are all on speaking terms. This one prints two lines, so you can also see how a C program is put together.

Here's the program, in `src/main.c`:

```c
#include <stdio.h>

int main(void) {
    printf("Hello World!\n");
    printf("I am learning C");

    return 0;
}
```

Press **Run**, or press F5. The Output pane should look something like this:

```
Configuring 01-hello-world...
Building 01-hello-world...
Running program.exe

Hello World!
I am learning C
— Finished with exit code 0 —
```

The first line is the important one to understand. C is a compiled language, which means the text in `main.c` isn't the program. It's a set of instructions that a compiler turns into one. Running the program happens in three stages, and the runner shows you each one:

* **Configuring** is CMake reading the step's `CMakeLists.txt`, and working out how to build it. This only changes when the build setup changes, so it's quick.
* **Building** is the compiler turning `main.c` into a program. The first build can take several seconds, and later ones are much faster, because only the changed files are compiled again.
* **Running** starts the program that the build produced.

The blank line before the program's output is there on purpose. It separates the build from what your program prints, so the two don't run together.

At the end, the runner shows the exit code. Zero means the program finished without a problem.

### What the program is made of

Each part of the program has a job, and you'll meet every one of them again.

* `#include <stdio.h>` brings in the input and output functions. Without it, `printf` doesn't exist. The angle brackets tell the compiler to look in the standard library's headers.
* `int main(void)` is where the program starts. Every C program has exactly one `main`, and the operating system always calls it first. The `void` means the function takes no arguments.
* `printf("...")` writes text to the output. The text in quotation marks is what it prints.
* `\n` is a newline. Without it, the second line would follow the first on the same line, which is why the first line has one and the second doesn't.
* `return 0;` tells the operating system the program finished successfully. A non-zero value means something went wrong, and that matters when scripts run your program.

---

### Quiz

*These questions are written for this course.*

````quiz
Which header declares `printf`?
○ <iostream.h>
→ Not quite. C has no iostream header. Output in C comes from the standard I/O library.
◉ <stdio.h>
→ Yes. <stdio.h> declares printf, along with the other standard input and output functions.
````

---

### Try it in the runner

Add a third line to the program, after the second one. Predict the output before you press **Run**. The second line has no `\n` at its end, so the third `printf` would continue on the same line. Add a `\n` to the end of the second line, and then predict again: the third line now starts on its own line.

Then put `fflush(stdout);` after the first `printf`, and press **Run** again. The output looks the same. `\n` ends a line, and `fflush` pushes out whatever is waiting in the output buffer. For a program like this, either one is fine, but a prompt that asks for input needs the flush so the question appears on screen.

---

And that's your first C program, built and run by the same tools that the professionals use. Nothing about it was magic, and every line had a reason to be there.
