## Summary: Getting started

This chapter covered the tools you need, your first program, and the parts it's made from.

* **The compiler turns source into a program.** This course uses gcc from MSYS2, and the runner builds with it.
* **CMake describes the build, and Ninja does it.** The runner shows each stage as Configuring, Building, and Running.
* **`main` is where the program starts.** Every C program has one `int main(void)`, and it returns 0 on success.
* **`printf` writes text.** `\n` starts a new line, and a line without one runs on into the next output.
* **Headers declare what a library provides.** `#include` brings them in. `stdio.h` is for input and output, `stdlib.h` for general utilities, and `string.h` for text.
* **Format strings must match their values.** `%d` takes an `int`, and `%zu` takes a `size_t`.
* **Comments are for people.** `//` runs to the end of a line, and `/* */` can run over several lines.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `return 0;` in `main` tell the operating system?
○ That the program printed nothing.
→ Not quite. Zero says nothing about what was printed.
◉ That the program finished successfully.
→ Yes. Zero means success, and any other value means something went wrong.
○ That the program should run again.
→ Not quite. Returning from main ends the program.
````

````quiz
Which header declares `abs`?
○ <stdio.h>
→ Not quite. <stdio.h> declares the input and output functions.
◉ <stdlib.h>
→ Yes. <stdlib.h> holds general utilities, including abs.
○ <string.h>
→ Not quite. <string.h> declares the functions that work on text.
````

````quiz
What does `\n` do inside a string passed to `printf`?
○ It prints the letter n.
→ Not quite. A backslash starts an escape, and \n is a newline.
◉ It starts a new line.
→ Yes. The newline is printed, so whatever follows starts on the next line.
○ It stops the program.
→ Not quite. A newline doesn't end the program.
````
