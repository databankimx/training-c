## Merge sort

Merge sort uses a different idea from the sorts so far. Instead of working through the whole array at each step, it splits the array in half, sorts each half the same way, and then combines the two sorted halves. Each half is split again until a piece holds a single value, which is already sorted. The combining step is where the work happens.

This is called divide and conquer. The problem is divided into smaller copies of itself, the smaller copies are solved, and the answers are combined. Because each half is handled by the same method, the sort is written as a function that calls itself, which makes it the first recursive sort in this chapter.

Here's the sort, from `src/main.c`. The function works on the range from `lo` up to, but not including, `hi`:

```c
static void merge_sort_range(int values[], int temp[], size_t n, size_t lo, size_t hi,
                             long *comparisons, FILE *trace, int *first) {
    if (hi - lo <= 1) {
        return;
    }
    size_t mid = lo + (hi - lo) / 2;
    merge_sort_range(values, temp, n, lo, mid, comparisons, trace, first);
    merge_sort_range(values, temp, n, mid, hi, comparisons, trace, first);
    merge_runs(values, temp, n, lo, mid, hi, comparisons, trace, first);
}
```

A range of one value is already sorted, so the function returns straight away. Otherwise it finds the middle, sorts the left half and the right half, and merges them. The whole array is sorted by calling the function with `lo` set to 0 and `hi` set to the length.

The `trace` and `first` parameters are for the visualizer. When `trace` is `NULL`, the sort only sorts and counts. When it's a file, the same function also writes a frame for each split and each merge. Because one function does both jobs, the frames always show the same work the count measures.

### The merge

Merging two sorted halves is simple. Keep one index at the front of each half. Compare the two front values, take the smaller, and move that index on. When one half runs out, copy the rest of the other half. The result is one sorted run:

```c
while (left < mid && right < hi) {
    (*comparisons)++;
    if (values[left] <= values[right]) {
        temp[out++] = values[left++];
    } else {
        temp[out++] = values[right++];
    }
}
```

The merge uses `<=` rather than `<`. When two values are equal, the one from the left half goes first, so equal values keep their original order. That makes merge sort a stable sort, which matters when the values carry other data.

The merge writes into a temporary array, `temp`, and copies the result back when it's done. That's the extra space the Big O section counts. The program allocates `temp` once, at the top, and every merge reuses it.

### The data

The visualized array holds the values 1 through 20, each once, in a scrambled order:

```c
int small[] = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
```

Press **Run**. The output begins:

```
Visualized list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Comparisons: ...
```

The timing array holds every whole number from -1000 to 1000, in a fixed shuffled order. The output reports its first and last values after sorting, and the comparison count from the run:

```
Timing list: 2001 values, from -1000 to 1000
First three after sorting: -1000 -999 -998
Last three after sorting: 998 999 1000
Comparisons: ...
Sorted correctly: yes
```

The comparison counts depend on the order of the values, so read them from your run. The one case you can predict exactly is an already sorted array, which the "Try" uses.

### Watch the sort

The program writes `trace.js` for the visualized array. Press **Run** first, then press **Visualize**. The visualizer shows the splitting and the merging:

* A split frame describes the range being divided into two halves.
* Each comparison during a merge shows the two front values in amber, and its message says which one is taken.
* When a merge finishes, the merged run is shown in green, and it's now in order.

The full sort is about a hundred frames, so **Fast** or **Very fast** is the practical way to watch it through.

### Big O analysis

Let n be the number of values.

**Levels.** Each split halves the size of the pieces, so the array is split until each piece holds one value. That takes about log₂n levels of splitting. The pieces at each level add up to all n values.

**Merge work.** Merging two runs takes at most one comparison for each value in them, so merging all the pieces at one level takes at most n comparisons. Over all the levels, that's at most n × log₂n comparisons. That's O(n log n).

**Best case.** Even for an array that's already in order, the splitting still happens at every level, so the sort still does O(n log n) work. The merge is cheaper on sorted input, since the left half is used up first, but the count is still O(n log n).

**Worst case.** The worst case has at most n log₂n comparisons, which is O(n log n).

**Average case.** For values in a random order, the average is also O(n log n).

**Space.** The merge needs a temporary array the size of the run being merged, so the extra space is O(n).

Merge sort is O(n log n) in every case, which is its main strength. Insertion sort is faster on a nearly sorted array, since its best case is O(n), but its worst case is O(n²). Merge sort never reaches O(n²), which makes it the safer choice for large arrays where the order is unknown.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does merge sort take about log₂n levels of splitting?
○ Because the array has to be split into exactly log₂n pieces.
→ Not quite. The number of pieces is not fixed in advance: the pieces keep halving until each holds one value.
◉ Because each split halves the size of the pieces, and halving n repeatedly reaches 1 after about log₂n steps.
→ Yes. That's the same halving that makes binary search O(log n).
○ Because the merge step has to be repeated log₂n times.
→ Not quite. The merge is done once for each split, and the number of splits follows from the halving.
````

````quiz
Why does merge sort use `<=` when comparing the front values of the two halves?
○ Because `<` would make the sort slower.
→ Not quite. The choice affects the order of equal values, not the speed.
◉ So that equal values keep their original order, which makes the sort stable.
→ Yes. The value from the left half is taken first when the two are equal.
○ So that the sort doesn't need a temporary array.
→ Not quite. The merge still needs a temporary array, whichever comparison is used.
````

---

### Try it in the runner

Change the visualized array to the values 1 through 20 in order, and predict the comparison count before you press **Run**. Each merge takes the left half's front value first, since it's always the smaller, so the right half is never compared until the left half is used up. The count is then the number of left-half values at each merge, added over all the levels. Then press **Visualize** and watch how quickly the sorted runs combine.

---

Merge sort gives O(n log n) in every case, at the cost of extra space for the merge. The next sort, quick sort, also aims for O(n log n), but it works in place and its worst case depends on the choice it makes at each split.
