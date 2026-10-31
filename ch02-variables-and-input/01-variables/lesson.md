## Variables

A variable is a named place in memory that holds a value. C asks you to say what kind of value it holds, its type, before you use it. The type decides how much memory the variable takes, what values it can hold, and what operations make sense on it.

The program in `src/main.c` declares four variables, one of each kind:

```c
int students = 24;
double average = 87.5;
char grade = 'B';
const int maximum = 100;
```

Press **Run**. The output is:

```
Students: 24
Average: 87.5
Grade: B
Out of: 100
```

### The basic types

* **`int`** holds a whole number, such as 24 or -3.
* **`double`** holds a number with a fraction, such as 87.5. It's stored approximately, so very precise values can be slightly off.
* **`char`** holds a single character, written in single quotation marks, such as `'B'`. Underneath, it's a small whole number, which is why you can do arithmetic with it, though rarely a good idea.

The sizes of these types depend on the compiler. `int` is at least 16 bits, and on this toolchain it's 32 bits. The C standard only promises the minimums, so don't write code that relies on an exact size without checking it.

### Declaring and initializing

A declaration gives a variable its type and name. An initializer, the `= 24` part, gives it a first value. A variable declared without an initializer holds whatever happened to be in that memory, which is a bug waiting to happen. Give every variable a value when you declare it.

### Constants

`const` says that a variable's value can't change after it's set. `const int maximum = 100;` can be read but not assigned to, and the compiler reports an error if you try. Use `const` for values that never change, so a reader knows that and the compiler can check it.

### The format specifiers

`printf` needs a placeholder for each value. Each one starts with `%` and says what kind of value goes in that spot:

| Specifier | Type it's for | Used in this program | Example output |
|---|---|---|---|
| `%d` | An `int` | `Students: %d` | `Students: 24` |
| `%.1f` | A `double`, with one digit after the point | `Average: %.1f` | `Average: 87.5` |
| `%c` | A single `char` | `Grade: %c` | `Grade: B` |

The placeholder must match the type of the value. `%d` given a `double` prints a meaningless number, and `%f` given an `int` does the same. The compiler usually warns about the mismatch, so read the warnings before you ignore them.

A plain `%f` prints a `double` with six digits after the point. The number between the point and the `f`, as in `%.1f`, sets the number of digits.

Two more are worth knowing. `%%` prints a single percent sign, and `%zu` is for a `size_t`, which the strings chapter covers.

---

### Quiz

*These questions are written for this course.*

````quiz
Which type should hold the value 3.5?
○ int
→ Not quite. An int holds whole numbers, so the .5 would be lost.
◉ double
→ Yes. A double holds numbers with a fraction.
○ char
→ Not quite. A char holds a single character, such as 'A'.
````

---

### Try it in the runner

Change `grade` to `'A'`, and predict the output before you press **Run**. The third line becomes `Grade: A`, since the `%c` specifier prints the character.

---

Variables give values names and types, and the types decide what the program can do with them. The next step is arithmetic.
