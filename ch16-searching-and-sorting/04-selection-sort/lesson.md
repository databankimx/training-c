## Selection sort

Selection sort works the way many people sort a hand of cards. It looks through the cards that are still unsorted, picks out the smallest, and moves it into the next place at the front. Then it does the same again for the rest.

Here's the sort, from `src/main.c`. The trace code is in the same file but is left out of this listing:

```c
static void selection_sort(int values[], size_t n, long *comparisons, long *swaps) {
    for (size_t i = 0; i + 1 < n; i++) {
        size_t smallest = i;
        for (size_t j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (values[j] < values[smallest]) {
                smallest = j;
            }
        }
        if (smallest != i) {
            int temp = values[i];
            values[i] = values[smallest];
            values[smallest] = temp;
            (*swaps)++;
        }
    }
}
```

Each pass has two parts. The inner loop walks through the values from `i + 1` to the end, and remembers the index of the smallest one it has seen. The outer step then swaps that smallest value into place at index `i`, if it isn't there already. After pass `i`, the values before `i + 1` are in their final places, and the search for the next pass starts one place further along.

### The data

The visualized array holds the values 1 through 20, each once, in a scrambled order:

```c
int small[] = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
```

Press **Run**. The output begins:

```
Visualized list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Comparisons: 190, swaps: ...
```

The comparison count is 190 for any 20 values, since selection sort always makes n(n − 1) / 2 comparisons. The swap count depends on the order, so read it from your own run.

The timing array holds every whole number from -1000 to 1000, in a fixed shuffled order. The output reports its first and last values after sorting, and the counts from the run:

```
Timing list: 2001 values, from -1000 to 1000
First three after sorting: -1000 -999 -998
Last three after sorting: 998 999 1000
Comparisons: 2001000, swaps: ...
Sorted correctly: yes
```

The comparison count is n(n − 1) / 2, which for 2001 values is 2,001,000. The program checks the whole array, and prints `Sorted correctly: yes` only when every neighbor is in order.

### Watch the sort

The program writes `trace.js` for the visualized array. Press **Run** first, then press **Visualize**. Each comparison is a frame in which the current smallest value and the value being checked are shown in amber. When a swap happens, a frame shows the two values swapped in purple. The green bars on the left are the values already in their final places.

The full sort is about 200 frames, so **Fast** or **Very fast** is the practical way to watch it through.

### Big O analysis

Let n be the number of values.

**Comparisons.** Pass `i` compares the value at each of the remaining `n - 1 - i` places with the smallest seen so far. Adding those counts over all passes gives (n − 1) + (n − 2) + ... + 1, which is n(n − 1) / 2 comparisons. That's O(n²).

**Best case.** This is the same as the worst case. Even if the array is already in order, every pass still looks through the rest of it, because selection sort has no early stop. The comparison count is n(n − 1) / 2 whatever the input, so the best case is O(n²).

**Swaps.** Each pass makes at most one swap, and there are at most n − 1 passes, so the swaps are at most n − 1. That's O(n). An array already in order needs no swaps at all, since the smallest value is always already in place.

**Space.** The sort works on the array itself and keeps only a few indexes, so its extra space is O(1).

So selection sort is O(n²) in every case for its comparisons, and O(n) in the worst case for its swaps. Bubble sort's early stop helps it on nearly sorted input. Selection sort makes fewer swaps, but it can't take advantage of sorted input in the same way.

---

### Quiz

*These questions are written for this course.*

````quiz
How many comparisons does selection sort make on an array of n values?
○ It depends on how the values are ordered.
→ Not quite. Its comparison count is the same for every order, which is what makes it easy to predict.
◉ n(n - 1) / 2, for every input.
→ Yes. Each pass looks at every remaining value, whatever the order.
○ n, since it stops as soon as the array is sorted.
→ Not quite. Selection sort has no early stop, so it doesn't finish sooner on sorted input.
````

````quiz
What is the most swaps selection sort can make on an array of n values?
○ n(n - 1) / 2
→ Not quite. That's the number of comparisons, not swaps.
◉ n - 1, since each pass makes at most one swap.
→ Yes. That's O(n), which is far fewer swaps than bubble sort can make.
○ n squared
→ Not quite. Each pass makes at most one swap, so the swaps grow in step with n.
````

---

### Try it in the runner

Change the visualized array to the values 1 through 20 in order, and predict the swap count before you press **Run**. The answer is 0, since the smallest value is already in place for every pass. The comparison count is still 190, which is the point of the Big O discussion above.

---

Selection sort is simple, and it makes few swaps, but its comparisons are always O(n²). Insertion sort is the next sort, and it can finish early on nearly sorted input, which selection sort can't do.
