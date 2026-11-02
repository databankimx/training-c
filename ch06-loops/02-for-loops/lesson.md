## For loops

A `while` loop leaves the counter to you. You set it before the loop, and you change it inside the loop. Counting loops are so common that C has a loop built for them: the `for` loop. It keeps the start, the condition, and the step together, on one line at the top.

Here's the first part of this step's program, in `src/main.c`:

```c
for (int i = 0; i < 5; ++i) {
    printf("%d\n", i + 1);
}
```

Press **Run**. The output is:

```
Counting up:
1
2
3
4
5
```

The three parts inside the parentheses are separated by semicolons:

* `int i = 0` runs once, before the loop starts. It creates the counter, which exists only inside the loop.
* `i < 5` is checked before each pass, as in a `while` loop. When it's false, the loop stops.
* `++i` runs after each pass. It moves the counter on before the next check.

The output starts at 1 because the body prints `i + 1`, while the counter itself starts at 0. The counter stops at 4 because the loop stops as soon as `i` reaches 5.

The counter is declared in the first part, and it exists only while the loop runs. Declaring it there, rather than before the loop, keeps the name from being used by mistake after the loop ends. C99 and later allow this form, and this course uses it throughout.

### Changing the step

The step doesn't have to be 1. The next loop adds 2 each time:

```c
for (int i = 0; i < 10; i += 2) {
    printf("%d\n", i + 2);
}
```

The output is 2, 4, 6, 8, 10. The counter takes the values 0, 2, 4, 6, and 8, and the body adds 2 to each one for display.

The loop can also count down. Here `i--` subtracts 1 after each pass:

```c
for (int i = 5; i > 0; i--) {
    printf("%d\n", i);
}
```

The output is 5, 4, 3, 2, 1. Notice that the condition is `i > 0`, not `i < 0`. The loop has to keep going while the counter is still positive.

It doesn't matter whether you write `++i` or `i++` in the step part of a `for` loop, because the value of the step isn't used. Many programmers prefer `++i`, so it's the form this course uses.

### Nested loops

A loop can sit inside another loop. The inner loop runs completely for each pass of the outer one:

```c
for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
        printf("%d, %d\n", i, j);
    }
}
```

The output is:

```
0, 0
0, 1
0, 2
1, 0
1, 1
1, 2
```

The outer counter `i` stays at 0 while the inner counter `j` runs through 0, 1, and 2. Then `i` moves to 1, and `j` starts again from 0. The inner loop has its own `j`, so the two counters don't interfere.

Nested loops are how you work with grids and tables. They're also a common place to make mistakes, because it's easy to use the wrong counter in the inner loop. Give each counter a clear name when the loops are big.

---

### Quiz

*These questions are written for this course.*

````quiz
In `for (int i = 0; i < 5; ++i)`, when does `++i` run?
○ Before the first pass.
→ Not quite. The start part, `int i = 0`, runs before the first pass.
◉ After each pass, before the next check of the condition.
→ Yes. The step runs after the body, and then the condition is checked again.
○ Only once, at the end of the loop.
→ Not quite. It runs after every pass that finishes.
````

````quiz
How many lines does this loop print in total?
`for (int i = 0; i < 2; ++i) { for (int j = 0; j < 3; ++j) { ... } }`
○ 2
→ Not quite. The inner loop runs three times for each pass of the outer loop.
○ 3
→ Not quite. The outer loop runs twice, so the inner loop runs in full twice.
◉ 6
→ Yes. Two passes of the outer loop, each with three passes of the inner loop.
````

---

### Try it in the runner

Change the step in the counting-by-twos loop from `i += 2` to `i += 3`, and press **Run**. Before you do, predict the numbers. The counter takes the values 0, 3, 6, and 9, and the body adds 2 to each, so the output is 2, 5, 8, and 11.

Then change the nested loops so the outer loop runs three times, and predict how many lines print. The answer is nine, since three passes of the outer loop each run three passes of the inner loop.

---

The `for` loop is the one to reach for whenever you know how many times something should repeat. The next step uses it with arrays, visiting each element by its index.
