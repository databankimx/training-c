## Homework: Count inversions

An inversion is a pair of values that are out of order: a value at an earlier index that is larger than a value at a later index. The array {5, 1, 4, 2, 3} has six inversions, one for each of these pairs: (5, 1), (5, 4), (5, 2), (5, 3), (4, 2), and (4, 3).

Insertion sort makes one move for each inversion, since every move swaps an out-of-order pair. So the number of inversions is also the number of moves insertion sort makes.

The program should:

* write `count_inversions(const int values[], size_t n)`, which checks every pair of positions with two nested loops, and returns the number of inversions
* write `insertion_moves(const int values[], size_t n)`, which runs insertion sort on a copy of the array and returns the number of moves it makes; the caller's array must not change
* print the count from each function for the array {5, 1, 4, 2, 3}, and say whether they match

### What to check

The output should be:

```
Inversions: 6
Insertion sort moves: 6
Match: yes
```

Then try an array that is already in order, such as {1, 2, 3, 4, 5}. Both numbers should be 0.

### Extensions

* Count the comparisons that the nested loops make for an array of n values. Say how that count compares with insertion sort's comparisons in the worst case.
* Explain why the nested loop is O(n²), and what a merge-sort-based count would cost instead. You don't need to write it; the merge sort step shows the approach.
* The copy in `insertion_moves` has room for 16 values. Change it so it allocates a copy of the right size with `malloc`, and check that the program still gives the same output. Explain what the check for `NULL` protects against.

---

*This exercise is not from the book. It practices the ideas in Chapter 16.*
