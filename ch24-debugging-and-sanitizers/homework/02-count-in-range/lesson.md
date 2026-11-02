## Homework: Count in range

Write a function that counts how many values in an array fall within a range, including both ends. Getting the boundaries right is the point of the exercise, since an off-by-one error here is easy to make and hard to spot.

The program should:

* write `count_in_range(const int values[], size_t count, int low, int high)`, which counts the values that are at least `low` and at most `high`
* in `main`, create an array holding 1, 2, 3, 4, and 5, and print `Count between 2 and 4: ` followed by `count_in_range` for 2 to 4
* print `Count between 1 and 5: ` followed by the count for 1 to 5

### What to check

The output should be:

```
Count between 2 and 4: 3
Count between 1 and 5: 5
```

The values 2, 3, and 4 are all counted, so the first answer is 3. Both ends are included, which is what the second check confirms, since 1 and 5 are counted when they're the range's limits.

### Extensions

* Write a version that counts only the values strictly between the limits, and check it against the same two ranges. Explain the difference in the two answers.
* Use the debugger from the finding-bugs step to step through `count_in_range` for the range 2 to 4, and watch which values are counted and which are not.

---

*This exercise is not from the book. It practices the ideas in Chapter 24, with the loops from Chapter 6.*
