## Include guards

A header is included wherever it's needed, and often a file ends up including the same header by more than one route. A header that includes `battery.h`, and a `main.c` that also includes it, would give the compiler two copies of the same structure. C doesn't allow a type to be defined twice, so the build fails. Include guards prevent this.

The header for this step starts and ends with a guard:

```c
#ifndef BATTERY_H
#define BATTERY_H

typedef struct {
    int charge;
    int capacity;
} Battery;

#endif /* BATTERY_H */
```

`#ifndef BATTERY_H` means "if BATTERY_H isn't defined". The first time the header is read, the name isn't defined, so the code runs. `#define BATTERY_H` then defines the name. Any later include finds the name already defined, skips everything down to `#endif`, and the structure is defined only once.

The name should be unique to the header, so that two headers never share one. The convention is the file name in capitals, with an underscore in place of the dot.

`main.c` includes the header twice on purpose:

```c
#include "battery.h"
#include "battery.h"
```

Press **Run**. The output is:

```
Charge: 20
Capacity: 50

Charge: 50
Capacity: 50

Charge: 50
Capacity: 50

```

The program works, and the duplicate include does nothing. The second `battery_recharge(&battery, 100)` shows the cap at work: the charge would be 150, but the capacity of 50 limits it.

### The recharge rules

`battery_recharge` has two cases. An amount of zero fills the battery, which is the C way of giving the function a default, since C has no default arguments. Any other amount adds to the charge, and the final check stops the charge from passing the capacity. The check runs in both cases, so a full recharge is never above the capacity either.

### Guards and pragma once

Many compilers also accept `#pragma once` at the top of a header, which has the same effect in one line. It isn't part of the C standard, so this course uses the guard, which works everywhere.

---

### Quiz

*These questions are written for this course.*

````quiz
What does an include guard prevent?
○ A header from being written to.
→ Not quite. Guards are about reading a header more than once, not about writing to it.
◉ A structure from being defined twice when its header is included twice.
→ Yes. The second include finds the name already defined, and skips the header.
○ A function from being called more than once.
→ Not quite. Guards are checked by the compiler, not by the program at run time.
````

````quiz
What is the purpose of `#define BATTERY_H` in a guarded header?
○ It defines the Battery structure.
→ Not quite. The definition of the structure is between the guard lines, not in the define.
◉ It marks the header as already read, so later includes are skipped.
→ Yes. The name exists after the first read, and the guard checks for it.
○ It sets the value of the battery's capacity.
→ Not quite. The define is a preprocessor name, and has no effect on the values.
````

---

### Try it in the runner

Remove the `#ifndef`, `#define`, and `#endif` lines from `battery.h`, and press **Run**. The build fails, since `Battery` is defined twice when `main.c` includes the header twice. Restore the three lines.

Then remove only the second `#include "battery.h"` line in `main.c`, and press **Run**. The program builds and runs as before, which confirms the second include changed nothing.

---

Include guards make it safe for a header to be included from anywhere, however many times. The next step puts two modules in pairs of files, and shows one structure built from another.
