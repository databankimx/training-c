## Summary: Headers and multiple files

This chapter covered how a C program is split across files, so each module has an interface in a header and an implementation in a source file.

* **A header declares, and a source file defines.** The header holds structures, typedefs, and function declarations. The source file holds the function bodies.
* **`#include "name.h"` inserts a header's text.** Quotes look in the including file's folder first. Angle brackets look in the system folders.
* **Every source file goes in the build.** Each `.c` file is compiled separately and then linked. A declared function without a definition causes a link error.
* **Include guards stop double definitions.** `#ifndef`, `#define`, and `#endif` make a header safe to include more than once.
* **Headers should not define variables or functions.** A header is included everywhere, so a definition in it would be repeated in every file that includes it, and the linker would find duplicates.
* **C has no base-class constructor.** A structure built from other structures is set up in an init function, in the order its parts must be ready.
* **Include what the declarations need.** A header includes the headers for the types it uses, and nothing more.

### Check your understanding

*These questions are written for this course.*

````quiz
Which file should hold the body of a function?
○ The header.
→ Not quite. Headers declare, and the bodies go in a source file.
◉ The source file for that module.
→ Yes. The source file defines what the header declares.
○ The main file, always.
→ Not quite. Each module's functions usually live in that module's own source file.
````

````quiz
What happens if a header has no include guard, and a file includes it twice, and the header defines a structure?
○ The second copy is ignored.
→ Not quite. Without a guard, the compiler reads both copies.
◉ The structure is defined twice, and the build fails.
→ Yes. A structure may only be defined once in a translation unit.
○ The program runs twice.
→ Not quite. The problem is at compile time, and the program never runs.
````

````quiz
A declared function is called, but no source file defines it. At which stage does the build fail?
○ Preprocessing.
→ Not quite. Preprocessing only inserts headers and handles guards.
○ Compiling each file.
→ Not quite. Each file compiles on its own, and it's allowed to call a declared function.
◉ Linking.
→ Yes. The linker can't find a definition for the function, and reports an undefined reference.
````
