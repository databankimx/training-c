## Break and continue

Sometimes a loop has to change course partway through a pass. You may have found the value you were looking for, or you may want to skip the rest of one pass and move on. Two statements do that: `break` stops the loop, and `continue` skips to the next pass.

Here's the first part of this step's program, in `src/main.c`. It uses `true` from `<stdbool.h>`, which the booleans chapter introduced:

```c
int i = 0;
while (true) {
    ++i;
    printf("%d\n", i);
    if (i == 5) {
        break;
    }
}
```

Press **Run**. The output is:

```
Break at 5:
1
2
3
4
5
```

The condition is `true`, so on its own the loop would never end. The `break` inside the `if` is what stops it. When `i` reaches 5, `break` leaves the loop at once, and the program carries on below it.

A `while (true)` loop is a common pattern for a loop whose exit point is in the middle of its body, such as a menu that repeats until the user chooses to quit. Make sure every path through the loop can reach a `break`, or the loop never ends.

### Continue

The second loop uses `continue`:

```c
for (int j = 1; j <= 10; ++j) {
    if (j <= 5) {
        continue;
    }
    printf("%d\n", j);
}
```

The output is:

```
Continue past 5:
6
7
8
9
10
```

When `j` is 5 or less, `continue` skips the rest of the body, so the `printf` line doesn't run for those values. The loop doesn't end, though. It moves straight to the next pass, and the step `++j` still runs. Once `j` is 6, the test fails, `continue` isn't reached, and the number is printed.

Notice what `continue` doesn't do: it doesn't skip the step. In a `for` loop, the step always runs before the next check of the condition. If you wrote the same thing as a `while` loop, you would have to move the increment to the top of the body, or the loop would never reach its end.

### Which loop does break affect?

`break` and `continue` apply only to the innermost loop they sit in. In nested loops, a `break` in the inner loop ends the inner loop, and the outer loop carries on with its next pass. Keep that in mind when you read a nested loop with a `break`, since it's easy to assume it stops everything.

---

### Quiz

*These questions are written for this course.*

````quiz
In a `for` loop, what does `continue` do?
○ It ends the loop.
→ Not quite. That's what break does.
◉ It skips the rest of the current pass, and the step still runs before the next check.
→ Yes. The loop moves on to its next pass, with the step applied as usual.
○ It restarts the loop from the beginning, with the counter reset.
→ Not quite. continue doesn't reset anything, and the counter keeps its value.
````

````quiz
A `break` is inside an inner loop, which is inside an outer loop. What does the break end?
○ The whole program.
→ Not quite. A break only ends a loop, not the program.
○ The outer loop.
→ Not quite. A break affects only the loop it sits in.
◉ The inner loop only.
→ Yes. The outer loop carries on with its next pass.
````

---

### Try it in the runner

Change the break condition from `i == 5` to `i == 3`, and press **Run**. Predict how many lines the first loop prints. It prints 1, 2, and 3, and then stops, so three lines.

Then change `j <= 5` to `j <= 7` in the second loop, and predict the output. The loop prints 8, 9, and 10, since the first seven values are skipped.

---

`break` and `continue` give you control inside a loop, without rearranging the loop itself. The summary and homework put all of the chapter's loops to work.
