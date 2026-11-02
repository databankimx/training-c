## Library targets

Every program in the course so far has been one executable, built from one `main.c`. Real projects are split into parts. A piece of code that several programs use is built once, as a library, and each program links against it. CMake calls each thing it builds a target, and this step adds a library target to the program's build.

The step's `CMakeLists.txt` declares two targets:

```cmake
add_library(greeting STATIC src/greeting.c)
target_include_directories(greeting PUBLIC src)

add_executable(program src/main.c)
target_link_libraries(program PRIVATE greeting)
```

`add_library` builds `greeting.c` into a static library, a file that the program's build can link in. `target_include_directories` with `PUBLIC` says that any target which links `greeting` also gets the `src` folder on its include path. `target_link_libraries` tells the program to link against `greeting`. That's why `main.c` can write `#include "greeting.h"` without any path.

Press **Run**. The output is:

```
Hello, Scott!
Hello, Ada!
```

The greeting comes from `greeting.c`, and `main.c` only calls it. Neither file includes the other's body, and the header is the only thing they share. This is the header-and-source split from the headers chapter, now with the build system keeping track of which file belongs to which target.

### The buffer in the interface

The greeting function writes its text into a buffer that the caller provides, rather than returning a string, as the earlier chapters' text functions did. The header states the rule: the buffer must have room for `size` bytes, and the function returns -1 when the text doesn't fit. `snprintf` never writes past the size it's given, so the check on the return value is the only thing the caller must handle.

### Why split the build

A library is compiled once and reused. If `main.c` changes, the build recompiles only `main.c` and relinks the program, since the library is up to date. A large project with dozens of libraries depends on this, because rebuilding everything on each change would be too slow.

### PUBLIC, PRIVATE, and INTERFACE

The keywords after a target name say who else needs a setting. `PRIVATE` means only this target uses it. `PUBLIC` means this target and any target that links it both use it. `INTERFACE` means only the targets that link it use it. The include folder is `PUBLIC` here, because `main.c` needs the header. A setting that only the library's own source needs would be `PRIVATE`.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `add_library(greeting STATIC src/greeting.c)` produce?
○ An executable called greeting.
→ Not quite. A library is linked into a program, not run by itself.
◉ A static library, which programs can link against.
→ Yes. The library is built once, and each program that uses it links it in.
○ A header file.
→ Not quite. A header is a text file that the build doesn't produce.
````

````quiz
Why is the include folder declared `PUBLIC` on the library?
○ Because the library is the only target that uses headers.
→ Not quite. The program uses the header too, which is why the setting is shared.
◉ Because the program that links the library also needs the header's folder on its include path.
→ Yes. PUBLIC passes the setting on to anything that links the library.
○ Because it makes the library faster.
→ Not quite. The keyword controls which targets get the setting, not speed.
````

---

### Try it in the runner

Add a third greeting in `main.c` for a name of your choice, and predict its output before you press **Run**. It prints the greeting for that name. You didn't change `greeting.c`, since the library is already built, and the program only calls it.

---

A library target builds shared code once, and a program links it in. The next step adds an option, so the library can be built in two different ways from the same CMake file.
