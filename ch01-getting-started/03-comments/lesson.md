## Comments

A comment is text the compiler ignores. It's there for the people who read the code, including you in six months' time. Good comments say why the code does what it does, not what the next line obviously says.

C has two kinds of comment:

* **Block comments** start with `/*` and end with `*/`. They can run over several lines, and they can start in the middle of a line.
* **Line comments** start with `//` and run to the end of the line. They're shorter to write, and most modern code uses them for single-line notes.

The program in `src/main.c` uses both:

```c
#include <stdio.h>

/* A block comment can run over
   several lines. The compiler skips all of it. */
int main(void) {
    // A line comment runs to the end of the line.
    printf("Comments are not part of the program.\n"); /* A comment can sit after code. */
    return 0;
}
```

Press **Run**. The output is:

```
Comments are not part of the program.
```

The program prints one line, and the comments change nothing about it.

### Comments are for people

A comment that repeats the code adds nothing: `i = i + 1; // add one to i` tells the reader nothing they couldn't see already. A comment that explains a choice is worth keeping: `// The sensor reports in tenths of a degree, so divide by ten.`

### Commented-out code

You can use comments to turn a line off while you test something, such as `// printf("debug\n");`. That's useful for a while, but code left in comments for long becomes confusing. Delete it once you're sure you don't need it. Version control keeps the old text if you ever want it back.

### Comments and the build

A comment inside a string isn't a comment. In `"http://example.com"`, the `//` is part of the text, and the compiler reads it as text. A comment can't start inside a string or a character literal.

---

### Quiz

*These questions are written for this course.*

````quiz
Which of these is a valid line comment in C?
○ # this is a comment
→ Not quite. A # starts a preprocessor line, such as #include, and the compiler reads it as a directive.
◉ // this is a comment
→ Yes. A line comment starts with two slashes and runs to the end of the line.
○ -- this is a comment
→ Not quite. Two hyphens are the comment marker in some other languages, but not in C.
````

---

### Try it in the runner

Put `//` in front of the `printf` line, and predict the output before you press **Run**. The output is empty, since the line that prints is now a comment. The program still builds and returns 0.

---

Comments are for the people who read the code, and they cost the computer nothing. The chapter summary comes next, and it covers the whole chapter.
