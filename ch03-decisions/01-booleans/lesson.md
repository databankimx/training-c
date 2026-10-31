## Booleans and comparisons

Every program makes decisions. It checks whether a value is big enough, whether a name was entered, or whether two things match, and then it chooses what to do next. The data type for those decisions is `bool`, which comes from `<stdbool.h>` and holds one of two values: `true` or `false`.

Here's the program for this step, in `src/main.c`. It begins with two `bool` variables, printed in two ways:

```c
bool is_coding_fun = true;
bool is_fish_tasty = false;

printf("Without words:\n");
printf("is_coding_fun: %d\n", is_coding_fun);
printf("is_fish_tasty: %d\n", is_fish_tasty);
```

Press **Run**. The output is:

```
Without words:
is_coding_fun: 1
is_fish_tasty: 0
```

A `bool` is stored as an integer, so `printf` with `%d` prints `true` as `1` and `false` as `0`. That's how C has always worked, and you'll see it in older code. The next part of the program prints the words instead:

```c
printf("is_coding_fun: %s\n", is_coding_fun ? "true" : "false");
printf("is_fish_tasty: %s\n", is_fish_tasty ? "true" : "false");
```

The conditional operator `? :` picks the text that matches the value. Each line is a little longer, but the output is what a reader expects:

```
With words:
is_coding_fun: true
is_fish_tasty: false
```

C has no setting that changes how `printf` shows a bool, so the choice is made in each line. The conditional works for every bool and every comparison, which is why the program uses it below.

### Comparisons

A comparison asks a question about two values, and the answer is a `bool`. The operators are:

| Operator | Meaning | Example | Result |
|---|---|---|---|
| `==` | Equal to | `x == 10` | `true` |
| `!=` | Not equal to | `x != y` | `true` |
| `>` | Greater than | `x > y` | `true` |
| `<` | Less than | `x < y` | `false` |
| `>=` | Greater than or equal to | `x >= 10` | `true` |
| `<=` | Less than or equal to | `y <= 8` | `false` |

With `x` as 10 and `y` as 9, the results in the table are what the program prints:

```
x == 10: true
x != y: true
x > y: true
x < y: false
x >= 10: true
y <= 8: false
```

Notice that equality is `==`, with two equals signs, and not `=`. A single `=` is assignment, which you've been using since the variables lesson. Writing `if (x = 10)` assigns 10 to `x`, and then tests whether 10 is true, which is almost never what you meant. Here the test is always true, since 10 is not zero, so the bug is quiet. Most compilers warn you about it, so keep the warnings on.

### Comparing types

You can compare `int` values with each other, and `double` values with each other. Mixing them works as well, because the `int` is converted to a `double` for the comparison. That's the same promotion you saw in arithmetic, and it's the one place where an `int` and a `double` can meet without any conversion on your part.

The program shows this with the last comparison:

```c
double ratio = 9.5;
printf("ratio > 9: %s\n", ratio > 9 ? "true" : "false");
```

The `9` is an `int`, and it's converted to `9.0` before the comparison. The output is `ratio > 9: true`.

Comparing text is a different matter, and it's covered when we return to strings later in the course. The `==` in C compares the addresses of two strings, not their text, so the strings chapter introduces `strcmp` for that job.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `printf` print for a `bool` variable holding `false` when you use `%d`?
○ false
→ Not quite. %d prints the number, not the word.
◉ 0
→ Yes. A bool is stored as an integer, so false is 0, and %d prints that number.
○ An empty line.
→ Not quite. The value is printed as the number 0.
````

````quiz
Which expression is true when `x` is 10?
○ x = 9
→ Not quite. That assigns 9 to x, and it doesn't ask a question at all.
◉ x == 10
→ Yes. == asks whether x is equal to 10.
○ x != 10
→ Not quite. That's true only when x is not 10.
````

---

### Try it in the runner

Change `y` to `10`, and press **Run**. Before you do, predict the values of `x == y` and `x < y`. Both `x` and `y` will be 10, so `x == y` becomes `true` and `x < y` becomes `false`.

Then add a line to the program that reads `printf("x = 3: %d\n", (x = 3));`, and press **Run**. The program still builds, because `x = 3` is a valid assignment, and it changes `x` to 3, so any line that uses `x` afterwards sees the new value. Writing `=` where you meant `==` is a common mistake, and it's the one to watch for when you read code.

---

Booleans are the raw material of every decision a program makes. The next step combines them, so one condition can depend on two others.
