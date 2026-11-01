## Quick sort

Quick sort is the sort most libraries use for general-purpose work. Like merge sort, it divides the problem and solves the parts. The difference is where the work happens. Merge sort splits the array in the middle and does its work when merging. Quick sort does its work first, by arranging each part around a chosen value, called the pivot, so that the two sides can be sorted independently.

The arrangement step is called partitioning. The pivot is placed in its final position, with every smaller value to its left and every larger value to its right. Neither side needs to be merged afterwards, because the pivot already separates them.

Here's the partition, from `src/main.c`. This version uses the last value in the part as the pivot:

```c
static size_t partition(int values[], size_t n, size_t lo, size_t hi, long *comparisons, long *swaps,
                        unsigned char done[], FILE *trace, int *first) {
    size_t pivot_index = hi - 1;
    int pivot = values[pivot_index];
    size_t next = lo;
    for (size_t j = lo; j + 1 < hi; j++) {
        (*comparisons)++;
        if (values[j] < pivot) {
            if (next != j) {
                int temp = values[next];
                values[next] = values[j];
                values[j] = temp;
                (*swaps)++;
            }
            next++;
        }
    }
    if (next != pivot_index) {
        int temp = values[next];
        values[next] = values[pivot_index];
        values[pivot_index] = temp;
        (*swaps)++;
    }
    done[next] = 1;
    return next;
}
```

The variable `next` marks the boundary between the smaller values, already moved to the left, and the rest. Each value is compared with the pivot once. A smaller value is swapped to the boundary and the boundary moves on. At the end, the pivot is swapped into the boundary, and the boundary is its final index. The `done` array records that index, so the trace can show it as placed.

The trace frames are written by the same function, between the steps above. The sort and the trace share one implementation, so the counts shown on screen are the counts the program reports.

The sort itself is short:

```c
static void quick_sort_range(int values[], size_t n, size_t lo, size_t hi, long *comparisons, long *swaps,
                             unsigned char done[], FILE *trace, int *first) {
    if (hi - lo <= 1) {
        if (hi - lo == 1) {
            done[lo] = 1;
        }
        return;
    }
    size_t pivot_index = partition(values, n, lo, hi, comparisons, swaps, done, trace, first);
    quick_sort_range(values, n, lo, pivot_index, comparisons, swaps, done, trace, first);
    quick_sort_range(values, n, pivot_index + 1, hi, comparisons, swaps, done, trace, first);
}
```

Once a part is partitioned, its pivot is in its final place, and the two sides are sorted in the same way. A part of one value needs no work.

### The data

The visualized array holds the values 1 through 20, each once, in a scrambled order:

```c
int small[] = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
```

Press **Run**. The output begins:

```
Visualized list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Comparisons: ..., swaps: ...
```

The timing array holds every whole number from -1000 to 1000, in a fixed shuffled order. The output reports its first and last values after sorting, and the counts from the run:

```
Timing list: 2001 values, from -1000 to 1000
First three after sorting: -1000 -999 -998
Last three after sorting: 998 999 1000
Comparisons: ..., swaps: ...
Sorted correctly: yes
```

The counts for a scrambled array depend on the order, so read them from your run. The "Try" uses a sorted array, where the count is exact.

### Watch the sort

The program writes `trace.js` for the visualized array. Press **Run** first, then press **Visualize**. The visualizer shows:

* each comparison against the pivot, with the value being checked and the pivot shown in amber
* each swap in purple, with a message saying whether it moves a smaller value to the boundary or the pivot into its final place
* each pivot that reaches its final place, shown in green, which stays green for the rest of the sort

Since the array is short, the whole sort is a few hundred frames. **Fast** or **Very fast** is the practical way to watch it through.

### Big O analysis

Let n be the number of values.

**One partition.** Partitioning a part of size m makes m − 1 comparisons, so it's O(m).

**Balanced splits.** If each pivot lands near the middle, the parts halve at each level of recursion, just as in merge sort. There are about log₂n levels, and the partitions at each level add up to n values. That's O(n log n) comparisons.

**Unbalanced splits.** If each pivot is the smallest or largest value in its part, one side is empty and the other has one fewer value. The partitions then have sizes n, n − 1, n − 2, and so on, which add up to n(n − 1) / 2 comparisons. That's O(n²).

**Best case.** The best case is a balanced split at every level, which gives O(n log n).

**Worst case.** The worst case is the unbalanced split at every level, which gives O(n²). A sorted array with the last value as the pivot is exactly this case, and the "Try" uses it.

**Average case.** For values in a random order, the pivot is about as likely to land in any position as any other. The splits are usually reasonably balanced, so the average is O(n log n).

**Space.** The partition works in place, so it needs only a few variables. The recursion uses stack space, one level for each split: about log₂n on average, and up to n in the worst case.

Quick sort's worst case is O(n²), like insertion sort's, but its average is O(n log n), which is much better for large arrays. Merge sort's worst case is O(n log n), but it needs O(n) extra space for the merge. Choosing the pivot well is how quick sort avoids its worst case: a random pivot, or the middle value of three, makes the bad splits rare. Those variations are common in practice, and they're the reason quick sort is used so widely.

Quick sort isn't stable. Equal values can change order during the swaps, which matters when the values carry other data.

---

### Quiz

*These questions are written for this course.*

````quiz
Why is quick sort's worst case O(n²)?
○ Because the partition step is slower than the merge step.
→ Not quite. A single partition costs O(m) for a part of size m, the same as a merge of that size.
◉ Because the pivot can split the part into one empty side and one side with one fewer value, at every level.
→ Yes. Those unbalanced splits add up to n(n − 1) / 2 comparisons.
○ Because the sort has to be repeated for each value.
→ Not quite. Each value is handled once per level, and the sort isn't repeated.
````

````quiz
Which statement about the space used by quick sort is true?
○ It needs O(n) extra space for a temporary array, like merge sort.
→ Not quite. Quick sort partitions in place, so it doesn't need that array.
◉ It needs only a few variables for the partition, plus stack space for the recursion.
→ Yes. The stack grows with the number of levels of splitting.
○ It needs no space at all.
→ Not quite. The recursion uses stack space, one level for each split.
````

---

### Try it in the runner

Change the visualized array to the values 1 through 20 in order, and predict the comparison count before you press **Run**. Each partition compares every remaining value with the pivot, which is the largest value, so every value is compared once per level. The parts shrink by one value each time, so the count is 19 + 18 + ... + 1, which is 190. The swap count is 0, since every smaller value is already in place. Then press **Visualize** and watch the pivot take one step at a time.

---

Quick sort is fast on average and simple to run in place, but its worst case is O(n²). Pivot choice is how that risk is managed. The next step shows the standard library sorts, which handle those choices for you.
