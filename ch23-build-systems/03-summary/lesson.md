## Summary: Build systems

This chapter covered the parts of CMake that go beyond a single program: libraries, the settings that connect them, and options that change a build.

* **A library target is built once and linked.** `add_library` makes a static or shared library, and `target_link_libraries` links it into a program.
* **Include folders are part of the target's interface.** `target_include_directories` with `PUBLIC` shares the folder with anything that links the library.
* **PUBLIC, PRIVATE, and INTERFACE control who sees a setting.** PRIVATE is for the target itself, PUBLIC for it and its users, and INTERFACE for its users only.
* **Rebuilds are incremental.** Only the changed files are recompiled, and the programs that depend on a changed library are relinked.
* **An option is a named on or off setting.** `option` declares it with a default and a description.
* **A compile definition lets the code check the option.** `target_compile_definitions` defines a symbol, and `#ifdef` checks it.
* **The cache keeps option values.** `CMakeCache.txt` holds the values set on the command line until they're changed.
* **The symbol must match.** A compile definition works only when the code checks the same name the build defines.

### Check your understanding

*These questions are written for this course.*

````quiz
Why is a library built once and then linked, rather than compiled into each program that uses it?
○ Because libraries can only be used by one program.
→ Not quite. A library can serve many programs, which is part of its purpose.
◉ So a change to the program's own code rebuilds only the program, and the library is reused as it is.
→ Yes. Incremental builds depend on keeping the shared code in its own target.
○ Because programs can't include headers from other folders.
→ Not quite. Headers can come from other folders, using the include settings.
````

````quiz
What does `target_include_directories(greeting PUBLIC src)` do for a program that links `greeting`?
○ It copies the header files into the program's folder.
→ Not quite. The headers stay where they are, and the folder is added to the include path.
◉ It adds the src folder to the program's include path, so `#include "greeting.h"` works.
→ Yes. PUBLIC shares the setting with targets that link the library.
○ It compiles the headers into the library.
→ Not quite. Headers are not compiled on their own.
````

````quiz
An option is set to ON, but the code doesn't change its behavior. What is the most likely cause?
○ The option is a string, not a boolean.
→ Not quite. Options are on or off, and the value is not a string.
◉ The code checks a symbol that the option never defines, so the preprocessor skips the change.
→ Yes. A compile definition has to match the name the code checks.
○ The option was set after the build started.
→ Not quite. Setting it after a build is a different matter, and the usual cause is a symbol name that doesn't match.
````
