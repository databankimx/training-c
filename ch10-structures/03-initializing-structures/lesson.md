## Initializing structures

A new variable with no initial values can hold anything, and that's a risk for a structure as much as for a plain variable. C gives you two tools, and they work differently from C++. Brace initialization lists the values in the order the members are declared. A structure that's partly initialized has its remaining members set to zero, which is the closest C has to a default. C has no default member values of its own, so a program that needs defaults writes them out once, in a function.

Here's the structure for this step, in `src/main.c`:

```c
typedef struct {
    char name[16];
    int volume;
    bool muted;
} Settings;
```

The structure has no default values. The defaults live in a function, which builds a complete `Settings` and returns it:

```c
Settings default_settings(void) {
    Settings s = {"default", 5, false};
    return s;
}
```

Press **Run**. The output is:

```
default 5 no
Scott 9 yes
Scott 1 yes
```

### The defaults function

`default_settings` lists every member in braces, in declaration order: the name, the volume, and `muted`. Because every member is given, nothing is left to chance. The caller gets a complete structure:

```c
Settings a = default_settings();
show(a);
```

The first line of output comes from that call. In C++, a structure can declare its defaults once, so every variable starts with them. In C, the function is where those defaults are written, and each caller that needs them calls it.

### Brace initialization

`Settings b = {"Scott", 9, true};` gives the values in order: the first goes to `name`, the second to `volume`, and the third to `muted`. The order must match the declaration. Swapping the volume and the name would fail to compile, since a number can't be stored in a text array. The compiler checks each value against its member's type.

### Members left out are zero

If a brace list gives fewer values than there are members, the rest are set to zero. That's a rule for every initializer in C: `Settings d = {"Ada"};` sets `volume` to 0, and `muted` to `false`. The result isn't the same as the C++ defaults, so a program that needs a non-zero starting value gives it in the braces, as `default_settings` does. The same rule means `Settings e = {0};` zeroes every member, which is a common way to start a structure in a known state.

### Copies are independent

`Settings c = b;` creates a new variable that starts as a copy of `b`. The next line changes only `c`:

```c
c.volume = 1;
```

The third line of output shows the change, and `b` still has volume 9. A copy is a separate structure, and changing one never changes the other.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `Settings d = {"Ada"};` give for `volume`?
○ 5, the same as the defaults in default_settings.
→ Not quite. C has no member defaults, so the rule is different.
◉ 0, because members left out of the braces are set to zero.
→ Yes. Members not given a value in the braces are zero.
○ The program won't compile, because volume is missing.
→ Not quite. Leaving members out of the braces is allowed.
````

````quiz
In `Settings b = {"Scott", 9, true};`, which member receives 9?
○ name
→ Not quite. name receives the first value, "Scott".
◉ volume
→ Yes. The values are matched to the members in the order they are declared.
○ muted
→ Not quite. muted receives the third value, true.
````

---

### Try it in the runner

Add `Settings d = {"Ada"};` and `show(d);` to the program, and predict the output before you press **Run**. The name is `Ada`, the volume is 0, and `muted` is `no`. The line should read `Ada 0 no`, not `Ada 5 no`, since C doesn't apply the defaults from `default_settings`.

Then write `Settings e = {5, "Ada"};`, with the values in the wrong order, and press **Run**. The build fails, because 5 can't be stored in the text array.

---

Brace initialization sets a structure's starting values, and a function is the place where a program keeps its defaults in C. The homework applies structures to a small task, and the summary brings the chapter together.
