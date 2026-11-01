## Homework: Count and sum

A function that is called once for each value in a range is a common job. In this exercise, you write one, and give it a rule that updates two totals through pointers in a context, so the totals are available after the loop.

The program should:

* create an array holding the numbers 1 through 10
* declare two `int` variables, `even_count` and `even_sum`, both starting at 0
* put pointers to both variables in a `Totals` structure
* write `for_each_value(const int values[], size_t count, void (*visit)(void *, int), void *context)`, which calls `visit` once for each value, passing the context
* write `count_and_sum_evens`, which adds 1 to `even_count` and adds the value to `even_sum` only when the value is even
* print `Even count: ` followed by `even_count`, and then `Sum of evens: ` followed by `even_sum`

### What to check

The output should be:

```
Even count: 5
Sum of evens: 30
```

The even numbers are 2, 4, 6, 8, and 10. Their sum is 30. The rule changes the two variables through the pointers in its context, so the totals are still there after `for_each_value` returns.

### Extensions

* Change the context so it holds copies of the two totals instead of pointers, and predict what the program prints. Explain why the totals can't be updated from inside the rule.
* Write the same count and sum as a plain loop in `main`, without `for_each_value`. Compare the two versions. Which one makes it easier to see that the totals are updated?

---

*This exercise is not from the book. It practices the ideas in Chapter 20, with the arrays from Chapter 4.*
