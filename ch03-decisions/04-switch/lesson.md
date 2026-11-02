## Switch statements

The `else if` chain from the last step is the right tool when each condition is different: a range of scores, or a test that combines two values. When every condition compares the same value with a fixed constant, a `switch` is clearer. It names the value once, and lists the cases beneath it.

Here's the program for this step, in `src/main.c`. It starts with a day number:

```c
int day = 3;
switch (day) {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    default:
        printf("Not a workday\n");
        break;
}
```

Press **Run**. The output is:

```
Wednesday
```

The value in parentheses after `switch` is compared with each `case` label in turn. The code under the matching label runs, and the `default` label runs when nothing else matches. `default` plays the role of a final `else`, and it's optional, just as `else` is.

### break

Each case ends with `break`. Without it, the program carries on into the next case and runs that code too. This is called falling through, and it's the most common `switch` mistake. Leave out one `break`, and you'll see output from two cases.

The program has a second rule to notice: the value in a `switch` must be an integer type or a `char`. You can't switch on a `double`, and you can't switch on a string. C strings are arrays of characters, so a `switch` can't test their text, and comparisons of text need an `if` chain with `strcmp` instead, as the strings chapter showed.

### Several labels for one block

Labels with no code between them share the code that follows:

```c
char grade = 'B';
switch (grade) {
    case 'A':
        printf("Excellent\n");
        break;
    case 'B':
    case 'C':
        printf("Good\n");
        break;
    default:
        printf("Keep going\n");
        break;
}
```

The output is `Good`. Both `'B'` and `'C'` reach the same line, so the two labels stack. This is the case where a `switch` is clearer than an `if` chain, since the shared code is written once.

### Falling through on purpose

Sometimes you do want one case to run into the next. When that's deliberate, say so with a comment:

```c
int level = 1;
switch (level) {
    case 1:
        printf("Level 1 tasks\n");
        /* fall through */
    case 2:
        printf("Level 2 tasks\n");
        break;
}
```

The output is:

```
Level 1 tasks
Level 2 tasks
```

The `/* fall through */` comment tells the next reader that the missing `break` is intended. GCC recognizes that comment, so it doesn't warn about the fall-through, and this course keeps the build warning-free. Standard C23 has a `[[fallthrough]];` attribute for the same purpose, which the modern-features chapter covers, since this course's code is written for C17. Use the comment rarely. Most switches should break at the end of every case.

Braces around each `case` aren't needed, but any case that declares a variable needs its own braces, so the variable is confined to that case. Add them when you declare something.

---

### Quiz

*These questions are written for this course.*

````quiz
What happens if a case has no `break` and no fall-through comment?
○ The switch ends, and the next case is skipped.
→ Not quite. That's what break does. Without it, the next case runs too.
◉ The code runs into the next case as well, and GCC warns about it.
→ Yes. Execution continues into the next case unless you stop it.
○ The program won't compile.
→ Not quite. It compiles, but GCC warns about the fall-through.
````

````quiz
Which of these can you use as the value of a `switch`?
○ A string such as "Monday"
→ Not quite. A switch works on integer types and char, not on strings.
◉ An int
→ Yes. Integers are a valid switch value.
○ A double
→ Not quite. A switch doesn't accept floating-point values.
````

---

### Try it in the runner

Change `level` to `2`, and press **Run**. Predict how many lines the last switch prints. Starting at case 2 skips the first label, so only `Level 2 tasks` prints.

Then remove the `break;` after `Good`, and predict whether `Keep going` also prints. It does, because without the `break`, the `'B'` case falls into the `default` label. The compiler warns about the missing break, which is the same fall-through that the `/* fall through */` comment makes deliberate.

---

A `switch` names the value once and lists each case beneath it. Reach for it when one value is compared with several constants, such as a menu choice or a set of codes.
