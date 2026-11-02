## Homework: Count pairs

Write a function that counts the pairs of different items in a list of n items, where each pair is counted once. A pair is two positions i and j with i less than j, so the pairs for n = 3 are (0,1), (0,2), and (1,2).

The program should:

* write `count_pairs(long n)`, which uses two nested loops, with the inner loop starting one place after the outer one, and returns the number of pairs
* write `pair_formula(long n)`, which returns n times (n − 1) divided by 2, using integer arithmetic
* print, for n = 4, 10, and 100, a line such as `n = 4: pairs 6, formula 6`

### What to check

The output should be:

```
n = 4: pairs 6, formula 6
n = 10: pairs 45, formula 45
n = 100: pairs 4950, formula 4950
```

The two columns should always agree. If they don't, check where the inner loop starts.

The C output has no thousands separators, since `printf` doesn't add them portably.

### Extensions

* Count the operations the nested loops perform for n = 1000, and say how that compares with n squared.
* Explain why the formula is faster than the loops, and why the loops still matter for understanding the count.

---

*This exercise is not from the book. It practices the ideas in Chapter 15.*
