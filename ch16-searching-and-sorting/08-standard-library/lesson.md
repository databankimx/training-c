## The standard library sort and search

In real programs, you almost never write the sort yourself. The C standard library provides sorting and searching in `<stdlib.h>`: `qsort` sorts an array, and `bsearch` searches a sorted one. They're written and tuned by people who spend their time on exactly this problem. The earlier steps in this chapter taught you how the sorts work, which is what you need to choose and use them well. This step shows the library versions.

### Comparison functions

Unlike the C++ library, `qsort` and `bsearch` don't know how to compare the values in your array. They take a comparison function, which is called with pointers to two elements and returns a number that's negative, zero, or positive:

```c
static int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}
```

The function receives `void` pointers, because `qsort` works on any type, so it casts them back to `int *` and reads the values. The comparison returns 1, 0, or -1 without subtracting, since subtracting could overflow for large values. Writing one comparison function per type is the C way to tell the library how to order the data. It's also why the C++ version's `std::sort` call has no third argument: C++ templates generate the comparison for you.

### Sorting

Here's the library sort, from `src/main.c`:

```c
int small[] = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
size_t small_count = sizeof small / sizeof small[0];
qsort(small, small_count, sizeof small[0], compare_ints);
```

That's the whole call. The arguments are the array, its length, the size of one element, and the comparison. It sorts the 20-value list into 1 through 20. The library doesn't count its steps for you and doesn't expose them, so this step has no visualizer. The trace of a library sort would be the library's own work, which is not something to step through.

Press **Run**. The output begins:

```
Short list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
```

The timing list is the same -1000 to 1000 shuffle as before. It's sorted in one call, and the output checks the result with `is_sorted`, which reports whether every value is in order from the first to the last.

### Searching a sorted array

`bsearch` answers the question "is the key present?" using the binary search from the previous steps. It returns a pointer to a matching element, or `NULL`:

```c
int key = 12;
int *found = bsearch(&key, small, small_count, sizeof small[0], compare_ints);
```

The result is a pointer into the array. Subtracting the start of the array, `found - small`, gives the index, as a count of places from the start. The program prints `present at index 11` when the result isn't `NULL`.

C's standard library has no `lower_bound`. The C++ version returns the position of the first value not less than the target, and it's useful when the value might be missing. The program writes that function by hand, as `lower_bound`, using the same halving as `bsearch`. It returns the index where the key would go to keep the array in order.

Press **Run**. The output for the short array is:

```
Search for 12: present at index 11
lower_bound for 12: index 11
```

The value 12 is the twelfth value in the sorted array, so its index is 11. The timing array has the same kind of search, and its output reports both results:

```
Search for 737: present
Search for 5000: absent
```

Both searches use `bsearch` on the long sorted array, so they take about eleven comparisons each, as the binary search step showed for an array of this size.

### Big O analysis

Let n be the number of values.

**Sorting.** `qsort` has no guaranteed cost in the C standard. Most implementations use a merge sort or a quick sort, with O(n log n) cost on average. Check your library's documentation, since the worst case depends on the implementation. The C++ `std::sort` does promise O(n log n) and sets an upper bound on its worst case.

**Sorting space.** The sort works in place where it can. Merge-based implementations need O(n) extra space, which `qsort` may allocate internally.

**Searching a sorted array.** `bsearch` makes O(log n) comparisons, the same as the binary search step. It needs the array to be sorted, and on an unsorted array its answers are meaningless.

**Checking order.** `is_sorted` reads each value once, so it's O(n). It's a cheap check after sorting, and it's useful in tests.

So the library gives O(n log n) sorting and O(log n) searching on sorted data, with no algorithm of your own to get wrong. The trade-off the previous steps measured still holds: sorting costs O(n log n) once, and each later search is O(log n), which pays off when the array is searched many times.

### When to use the library

Use `qsort` and `bsearch` by default. They're faster than most hand-written versions, and they've been tested far more than anything you'd write in a course. Write your own sort when you're learning how sorts work, as this chapter did, or when a special requirement calls for it.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `qsort` take a comparison function?
○ Because C arrays can't be sorted without one.
→ Not quite. Sorting needs a way to compare values, and the library cannot know that for your type.
◉ Because qsort works on any type, so it needs to be told how to compare two elements.
→ Yes. The function receives pointers and says which element comes first.
○ Because the comparison function counts the work the sort does.
→ Not quite. The function only compares two values, and it doesn't count anything.
````

````quiz
What must be true before `bsearch` gives a correct answer?
○ The array must hold only positive numbers.
→ Not quite. bsearch works with any values, as long as they're in order.
◉ The array must be sorted by the same comparison function.
→ Yes. bsearch depends on the order to throw away half the array each time.
○ The array must have an odd number of values.
→ Not quite. The length doesn't matter, only the order.
````

---

### Try it in the runner

Change the key from 12 to 21, which isn't in the array, and predict the results before you press **Run**. `bsearch` prints `absent`, since 21 is missing. `lower_bound` returns index 20, the position where 21 would go, which is one past the last value.

---

The library gives you tested sorting and searching, with the same costs you measured in this chapter. The chapter summary, the homework, and the chapter overview come next, and they bring the search and sort steps together.
