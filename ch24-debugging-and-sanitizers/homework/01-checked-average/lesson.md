## Homework: Checked average

Write a function that returns the average of a list of numbers, and protect it with an assertion. An empty list has no average, so the function's caller must never pass one. That promise is what the assertion checks.

The program should:

* write `average(const int values[], size_t count)`, which returns a `double`, and assumes `count` is not zero
* start `average` with `assert(count > 0);`
* in `main`, create an array holding 2, 4, 6, and 8, and print `Average: ` followed by the result with two decimal places

### What to check

The output should be:

```
Average: 5.00
```

The list is not empty, so the assertion holds and the program runs to the end. The division must use `double` values, or the result would be cut to a whole number.

### Extensions

* Call `average` with a count of 0, and predict the output and the exit code before you run it. Explain why this is a bug in the caller, not a condition the function should handle quietly.
* Replace the assertion with a check that returns an error for a count of 0, and have `main` print a message. Explain why a return value is the right choice when a caller can really pass an empty list.

---

*This exercise is not from the book. It practices the ideas in Chapter 24, with the arrays from Chapter 4.*
