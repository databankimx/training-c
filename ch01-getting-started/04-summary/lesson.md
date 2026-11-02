## Summary: Getting started

This chapter covered the smallest complete C program, and the tools that build and run it.

* **A program starts in `main`.** Every program has exactly one `main`, and the operating system calls it first. `return 0;` reports success.
* **`printf` writes output.** Its format string holds the text, and `\n` starts a new line. Output sent to a pipe is buffered, so a prompt without a newline needs `fflush(stdout)` to appear before the program waits.
* **`#include` brings in a header.** `<stdio.h>` declares `printf`. The angle brackets mean the header comes from the standard library.
* **Headers declare, and libraries provide.** A header tells the compiler what a library's functions look like, and the linker connects the program to the library's code. A function whose header is missing can't be checked, and recent gcc versions refuse to build the program.
* **Comments are notes for readers.** `//` runs to the end of the line, and `/* ... */` can cover several lines. The compiler ignores both.
* **A run has three stages.** The runner configures the build, builds the program, and then runs it. Knowing which stage failed tells you where to look.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `return 0;` at the end of `main` tell the operating system?
○ That the program is going to run again.
→ Not quite. The operating system doesn't restart the program because of it.
◉ That the program finished successfully.
→ Yes. Zero means success, and any other value means something went wrong.
○ That the output is ready to read.
→ Not quite. The output is written as the program runs, not when it returns.
````

````quiz
Which line is a comment?
◉ // Print the greeting before the prompt
→ Yes. Everything after // on that line is ignored by the compiler.
○ printf("Hello");
→ Not quite. That line is code, and the compiler runs it.
○ #include <stdio.h>
→ Not quite. #include is a preprocessor directive. It brings in a header.
````

````quiz
When the Output pane shows "Configuring" and then "Building", which stage is it?
○ Running the program.
→ Not quite. That's the stage that shows the program's own output.
◉ Building the program from its source.
→ Yes. The compiler turns the source into a program in the building stage.
○ Saving the file.
→ Not quite. The runner doesn't save anything when you press Run.
````
