## Counting operations

Big O notation describes how the work a program does grows with the size of its input. Before the notation, it helps to see the growth directly, so this step counts operations for a few input sizes and lets the numbers speak.

Here's the program for this step, in `src/main.c`. It has two functions, each of which counts the work it does for `n` items. The first is a single loop:

```c
long linear_operations(long n) {
    long count = 0;
    for (long i = 0; i < n; i++) {
        count++;
    }
    return count;
}
```

The loop runs once for each item, so the count is `n`.

The second function nests a loop inside another, and each of them runs over `n` items:

```c
long quadratic_operations(long n) {
    long count = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            count++;
        }
    }
    return count;
}
```

For each of the `n` passes of the outer loop, the inner loop runs `n` times. The count is `n` times `n`.

Press **Run**. The output is:

```
n = 10: linear 10, quadratic 100
n = 100: linear 100, quadratic 10000
n = 1000: linear 1000, quadratic 1000000
```

The C output has no thousands separators. `printf` doesn't add them portably, so the numbers are printed plainly. The values are the same as the C++ version's.

### What the numbers show

Look at the linear column. Each time `n` grows tenfold, the count grows tenfold too. The quadratic column behaves differently: each tenfold growth in `n` multiplies the count by a hundred. Doubling `n` doubles the linear count, and quadruples the quadratic count.

The operations are not the cost, but they stand in for it. A count of a million loop passes takes measurably longer than a count of a thousand, and the ratio between the two is the same as the ratio between the counts. That's why operation counts are the right thing to compare.

### Big O

Big O notation names these two growth patterns. The linear count is written O(n), read as "order n", and the quadratic count is O(n²). The notation drops the constants and the smaller terms. A loop that does `2n + 5` operations is still O(n), because for large `n` the `n` term decides how the count grows.

The notation describes the worst case. It says how the work grows as the input gets large, and it doesn't predict the exact time on a particular machine. Use it to compare approaches, not to estimate seconds.

---

### Quiz

*These questions are written for this course.*

````quiz
What is the operation count of a single loop over n items?
○ n²
→ Not quite. That's the count for two loops nested over the same n items.
◉ n
→ Yes. The loop runs once for each item, so the count grows at the same rate as n.
○ log n
→ Not quite. Logarithmic growth comes from halving the input each step, not from a plain loop.
````

````quiz
If the input size doubles, what happens to the count of a quadratic algorithm?
○ It doubles.
→ Not quite. That's the linear pattern.
◉ It becomes four times as large.
→ Yes. Two squared is four, so the count of n² quadruples.
○ It stays the same.
→ Not quite. Its count grows with n.
````

---

### Try it in the runner

Change the first size from `10` to `10000`, and predict the quadratic count before you press **Run**. It's 100,000,000, since 10000 squared is 100 million. The program takes noticeably longer than the others, which is the point: the count, not the size, decides the cost.

Then remove the inner loop from `quadratic_operations`, and predict the output for that size. The count drops back to n, the same as the linear version, so the nested loop is what made the difference.

---

Operation counts make growth visible, and Big O gives the growth a name. The next step applies the same counting to recursion, which is where the Fibonacci example shows a large difference between a simple method and an efficient one.
