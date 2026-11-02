## Headers and source files

So far every program has lived in one file. That's fine for a few hundred lines, but a larger program is easier to work with when each module has its own files: a header that says what the module provides, and a source file that says how it works. This step splits a structure and its functions in two, and shows the build finding both.

The program has three files in the step's `src` folder. The header declares the structure and the function:

```c
typedef struct {
    char make[32];
    char model[32];
    int year;
} Car;

void car_display(const Car *car);
```

The header holds declarations only: the structure's layout, and the signatures of the functions. It tells any file that includes it what a `Car` is, and what calls are valid. The source file defines the function:

```c
void car_display(const Car *car) {
    printf("Make: %s\n", car->make);
    printf("Model: %s\n", car->model);
    printf("Year: %d\n", car->year);
}
```

The source file includes the header, so the compiler knows the structure's layout when it reads the definition. `main.c` includes the same header, and uses the structure and its function without knowing how the function works.

### The include line

`#include "car.h"` copies the header's text into the file at that point. The quotes tell the compiler to look in the folder of the including file first, which is why a header in `src` is found without any extra setup. System headers such as `<stdio.h>` use angle brackets, which tell the compiler to look in the standard library's folders instead.

### Telling the build about the files

Press **Run**. The build compiles `main.c` and `car.c` separately, and then links them into one program. The output is:

```
Make: Ford
Model: Escort
Year: 1986

Make: Nissan
Model: Leaf
Year: 2015

```

The step's CMake file lists both sources:

```cmake
add_executable(program src/main.c src/car.c)
```

Each source file becomes an object file, and the linker joins them. A function declared in a header but never given a definition in a source file can't be linked, so the build fails when the function is called. That error means the definition is missing, not the declaration.

### Why the header is public

In C++, a class can keep its members private, even in its header. C can't: a structure defined in a header is visible to every file that includes it. The Chapter 11 encapsulation step avoided this with an opaque type, which declares only the name in the header and keeps the structure in its source file. The `Car` here is public, which is the simpler choice for a structure that has no rules to protect.

### Why separate the two

The header is what other code depends on. Once `main.c` includes `car.h`, changing the way `car_display` prints only means changing `car.c`, and nothing that includes the header needs to change. Keeping the interface in one file and the implementation in another is the main reason for the split.

---

### Quiz

*These questions are written for this course.*

````quiz
What goes in a header file?
○ The complete definitions of every function.
→ Not quite. Definitions go in the source file, and the header holds declarations.
◉ Declarations: the structure, and the signatures of its functions.
→ Yes. The header tells other files what the structure looks like and what can be called.
○ Only the main function.
→ Not quite. main belongs in a source file, and headers are shared by many files.
````

````quiz
What does `#include "car.h"` do?
○ It runs the code in car.h.
→ Not quite. It copies the text of the header into the file, and nothing is run.
◉ It copies the header's text into the including file, so the compiler knows the structure.
→ Yes. Including is text insertion, done before the compiler reads the file.
○ It links car.c into the program.
→ Not quite. Linking is done by the build, from the list of source files.
````

---

### Try it in the runner

Remove the `#include "car.h"` line from `main.c`, and press **Run**. The build fails, because `Car` and `car_display` are unknown to `main`. Restore the line before you continue.

Then remove `src/car.c` from the `add_executable` line in `CMakeLists.txt`, and press **Run**. The build fails at the linking stage, with an error about an undefined reference to `car_display`. The declaration is still there, but no definition is linked in. Restore the line.

---

The header says what a module provides, and the source file says how it works. The next step puts a second module in a header of its own, and shows what happens when a header is included twice.
