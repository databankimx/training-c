## Homework: Factorial

The factorial of a whole number n, written n!, is the product of all the whole numbers from 1 to n. So 4! is 1 × 2 × 3 × 4, which is 24, and 0! is defined as 1.

Write two functions that calculate factorials, and check that they agree:

* `factorial_recursive(int n)` calls itself on n − 1. Its base case is n of 1 or less, which returns 1.
* `factorial_loop(int n)` uses a `for` loop, multiplying a running result by each number from 2 to n.

In `main`, print the factorial of each number from 0 to 10, using the recursive version. Print the loop version's result beside it, and say whether the two agree. The output for each line should look like this:

```
5! = 120 (agree)
```

### What to check

Look at the first few lines first:

* `0! = 1`, because the base case covers 0 as well as 1
* `1! = 1`
* `2! = 2`
* `10! = 3628800`

Both versions should agree on every line. If they don't, check the base case in the recursive version, and the starting value of the loop.

### Extensions

* Print the value of 13! with each version. It doesn't fit in an `int` on this toolchain. What do you see, and why? In C, signed overflow is undefined behavior, so the program may print a wrong number, a different wrong number on each version, or nothing sensible at all. Think about the range of the type, which the variables lesson touched on.
* Time the two versions for a large number, such as 12, and say which you'd choose. The efficiency chapter covers how to think about that question properly.

---

*This exercise is not from the book. It practices the ideas in Chapter 7, and it prepares for the efficiency chapter.*
