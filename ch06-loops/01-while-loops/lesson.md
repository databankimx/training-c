## While loops

Some work has to be repeated, and you don't know in advance how many times. Reading lines until the user types `quit`, or retrying a connection until it works, are both examples. A loop repeats a block of code as long as a condition is true, and the `while` loop is the simplest kind.

Here's the program for this step, in `src/main.c`. It starts with a plain `while` loop:

```c
int i = 0;
while (i < 3) {
    printf("%d\n", ++i);
}
```

Press **Run**. The output begins:

```
while loop:
1
2
3
```

The condition in parentheses is checked before each pass through the loop. While it's true, the block runs, and when it becomes false, the loop stops and the program carries on below the closing brace. Here, `i` starts at 0, so the condition `i < 3` is true, and the block runs. `++i` adds one to `i` before the value is printed, so the first line is 1, not 0. After the third pass, `i` is 3, the condition is false, and the loop ends.

The loop needs something inside it to change the condition. Without `++i`, `i` would stay at 0 forever, and the program would never leave the loop. A loop that never ends is called an infinite loop. If a program seems stuck with no output, that's usually the cause.

### do-while

The `do-while` loop checks its condition at the end, not the start:

```c
int j = 10;
do {
    printf("j is %d\n", j);
    j++;
} while (j < 10);
```

The output is:

```
do-while loop:
j is 10
```

The condition `j < 10` is false from the start, since `j` is 10. A `while` loop would never run its block. The `do-while` runs the block once first, and then checks the condition. That's useful when the work has to happen at least once, such as asking the user for input before checking the answer.

Notice the semicolon after the closing parenthesis of `while`. A `do-while` needs it, and a `while` on its own doesn't.

---

### Quiz

*These questions are written for this course.*

````quiz
A `while` loop's condition is false the first time it's checked. How many times does its block run?
○ Once.
→ Not quite. A while loop checks its condition before the block, so a false condition at the start means no runs.
◉ Never.
→ Yes. The condition is checked first, so the block is skipped entirely.
○ Forever.
→ Not quite. A loop only runs forever when its condition stays true.
````

````quiz
Which loop is the right choice when the block must run at least once?
○ while
→ Not quite. A while loop checks its condition first, so the block may never run.
◉ do-while
→ Yes. The condition is checked after the block, so the block always runs once.
○ for, with no condition
→ Not quite. A for loop with no condition runs forever, unless something inside stops it.
````

---

### Try it in the runner

Change the do-while condition from `j < 10` to `j < 12`, and press **Run**. Predict the output before you do. The first pass prints `j is 10`, then `j` becomes 11, and the condition is still true, so the loop runs again and prints `j is 11`. After that, `j` is 12, and the loop stops.

Then change the while loop body so the increment comes after the output. Replace `printf("%d\n", ++i);` with `printf("%d\n", i); ++i;`, and predict the output before you press **Run**. The first line is now 0, not 1, because the value is printed before it's increased. The loop still stops after three passes.

---

Loops repeat work, and the while loop is the one that depends most directly on a condition. The next step introduces the `for` loop, which keeps the counter and the condition together.
