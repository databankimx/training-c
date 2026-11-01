## Homework: Stairs

Someone climbing a staircase takes one step or two at a time. The number of ways to climb n stairs, written ways(n), is defined by:

* ways(0) = 1 and ways(1) = 1
* ways(n) = ways(n − 1) + ways(n − 2) for n of 2 or more

That's the Fibonacci definition with a different starting point. Your job is to count the calls the recursive version makes, and to compare it with a memoized version.

The program should:

* write `ways_naive(int n, long long *calls)`, which refuses a negative `n` with a return code, and then calls a helper, `ways_naive_helper`, to do the recursive count. The helper counts its own calls, and it doesn't repeat the check
* write `ways_memo`, which refuses a negative `n` in the same way, then calls a helper that stores each answer the first time it's worked out, in an array that starts with every entry set to -1
* print, for n = 5 and n = 10, a line such as `n = 5: ways 8, naive calls 15, memoized calls 9`

### What to check

The output should be:

```
n = 5: ways 8, naive calls 15, memoized calls 9
n = 10: ways 89, naive calls 177, memoized calls 19
```

The naive count for n = 10 is the same as the Fibonacci count for n = 10 in the step, since the two recursions have the same shape. The memoized count is 2n − 1 for n of 2 or more.

### Extensions

* Add a loop version that computes ways(n) from the bottom up, keeping the last two values. Check that it agrees with the other two.
* Print the naive counts for n = 20 and n = 30, and compare them with the Fibonacci counts from the step. Say why the two sequences grow the same way.

---

*This exercise is not from the book. It practices the ideas in Chapter 15.*
