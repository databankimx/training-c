## Homework: Lower bound

The C++ standard library has `std::lower_bound`, which returns the position of the first value that is not smaller than a target. C's standard library doesn't have an equivalent, and the binary search step's chapter wrote one. In this exercise, you write that search yourself, and check it against the positions you can work out by hand.

Write `lower_bound(const int values[], size_t count, int target)`, which returns the index of the first value that is not smaller than `target`, or `count` when every value is smaller. Use binary search: keep a range of indexes, check its middle, and throw away the half that can't contain the answer.

The array must be sorted, and it may repeat values. For the array {1, 3, 3, 3, 5, 8}:

* the target 3 gives index 1, the first of the three 3s
* the target 4 gives index 4, the position of the 5
* the target 9 gives index 6, the size of the array, since every value is smaller

The program should print each answer, and check the three answers against the positions above.

### What to check

The output should be:

```
lower_bound(3): 1
lower_bound(4): 4
lower_bound(9): 6
Matches the expected positions: yes
```

The duplicated 3s are the test that matters most. A search that stops at the first 3 it finds, rather than the first one in the array, will print 2 or 3.

### Extensions

* Write the same function with a loop that keeps `high` as the position just past the range, so the range is never empty and the update rules are simpler. Compare how the two versions handle a target smaller than every value.
* Explain why this search makes about log₂n comparisons, and why it still works when the array has duplicates.

---

*This exercise is not from the book. It practices the ideas in Chapter 16, with the binary search from the binary search step.*
