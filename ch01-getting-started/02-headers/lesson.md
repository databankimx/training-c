## Headers

The first line of a C program is usually an `#include`. Each one brings in a header file, which tells the compiler what a library provides: the names of its functions, their arguments, and their return values. The code of the functions lives in the library itself, and the linker connects your program to it when the program is built.

The program in `src/main.c` uses one function from each of three headers:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *greeting = "Headers bring in declarations";
    printf("Length: %zu\n", strlen(greeting));
    printf("Absolute value of -42: %d\n", abs(-42));
    return 0;
}
```

Press **Run**. The output is:

```
Length: 29
Absolute value of -42: 42
```

`printf` comes from `<stdio.h>`, which handles input and output. `abs` comes from `<stdlib.h>`, which holds general utilities. `strlen` comes from `<string.h>`, which works on text.

### Why angle brackets?

`<stdio.h>` uses angle brackets because the header is part of the C standard library, which the compiler provides. A header of your own uses quotation marks, as you'll see in the headers chapter later in the course. Both forms tell the compiler where to look, and the quotation marks also look in the folder the file is in.

### What a header doesn't do

A header declares a function, but it doesn't contain the function's code. If you call a function whose header you haven't included, the compiler can't check the call. Recent versions of gcc refuse to build the program, and report the function as not declared. When you see that error, check the header first.

### The format string

`printf` takes a format string, and each `%` in it is replaced by a value that follows it. `%zu` is the format for a `size_t`, which is what `strlen` returns. `%d` is the format for an `int`, which `abs` returns. The formats must match the types, or the output is wrong, and some compilers report the mismatch as a warning.

---

### Quiz

*These questions are written for this course.*

````quiz
Which header declares `strlen`?
○ <stdlib.h>
→ Not quite. <stdlib.h> holds general utilities, such as abs.
◉ <string.h>
→ Yes. <string.h> declares the functions that work on text.
○ <stdio.h>
→ Not quite. <stdio.h> declares the input and output functions, such as printf.
````

---

### Try it in the runner

Change `abs(-42)` to `abs(7)`, and predict the second line before you press **Run**. It prints `Absolute value of -42: 7`, since the text in the format string doesn't change, only the value that `abs` returns.

---

Headers are how C tells the compiler what a library provides. The next step is comments, which are for the people who read the code.
