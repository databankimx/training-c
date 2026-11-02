## Bubble sort

Sorting puts a list into order. Bubble sort is the simplest sort to understand, and the slowest one for large lists. It works by walking along the list, comparing each value with the next one, and swapping the pair when they're out of order. Each full walk, called a pass, carries the largest value that's left to its final place at the end, the way a bubble rises through water.

Here's the sort, from `src/main.c`:

```c
static void bubble_sort(int values[], size_t n, long *comparisons, long *swaps) {
    for (size_t pass = 0; pass + 1 < n; pass++) {
        int swapped = 0;
        for (size_t j = 0; j + 1 < n - pass; j++) {
            (*comparisons)++;
            if (values[j] > values[j + 1]) {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
                (*swaps)++;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
```

The sort changes the array in place, so it takes a pointer to the array and its length. The two counters are pointers too, so the caller sees the totals. The inner loop stops one place short of the part that's already in order, because each pass finishes the end of the array. The `swapped` flag does something important: if a whole pass makes no swaps, the array must already be in order, so the sort can stop early.

The C version uses `size_t` for the positions and the length. Those are unsigned, so `n - pass` is safe, since `pass` never passes `n - 1` inside the loop's condition.

### The data

The visualized array holds the values 1 through 20, each once, in a scrambled order. It's non-negative, so each bar's height matches its value:

```c
int small[] = {14, 3, 19, 7, 1, 12, 20, 5, 16, 9, 2, 17, 6, 11, 18, 4, 13, 8, 15, 10};
```

The program keeps a copy of this array before it sorts, because the trace has to show the scrambled order from the start.

Press **Run**. The output begins:

```
Visualized list: 20 values
Sorted: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Comparisons: ..., swaps: ...
```

The timing array is the long one. It holds every whole number from -1000 to 1000, in a fixed shuffled order, and it's counted rather than drawn. The output reports its first and last values after sorting, which are always the same, and it reports the counts from the run:

```
Timing list: 2001 values, from -1000 to 1000
First three after sorting: -1000 -999 -998
Last three after sorting: 998 999 1000
Comparisons: ..., swaps: ...
Sorted correctly: yes
```

The counts depend on the shuffle, so read them from your own run. The first and last values are the check that the sort worked: whatever the order was before, the smallest values come first and the largest come last. The program also checks the whole array, and prints `Sorted correctly: yes` only when every neighbor is in order.

### Watch the sort

The program writes `trace.js` for the visualized array. Press **Run** first, then press **Visualize**. Each comparison is one frame, with the two values being compared shown in amber. If they're out of order, a second frame shows them after the swap, in purple. The green bars at the end are the values that are already in their final places, so you can see the sorted tail grow after each pass.

Use the controls as you did for the searches. **Speed** sets how long each frame stays on screen. With 20 values, a full sort is a few hundred frames, so **Fast** or **Very fast** is the practical way to watch the whole run.

### Big O analysis

Let n be the number of values.

**Comparisons.** In the worst case, every pass compares the same pairs as before, minus the part already placed. The first pass makes n - 1 comparisons, the next n - 2, and so on down to 1. That's a total of n(n - 1) / 2 comparisons, which is O(n²).

**Swaps.** Each swap fixes exactly one out-of-order pair. Reversed input has the most of these, every pair, which is n(n - 1) / 2 swaps. Random input averages about half that. Either way, the swap count is O(n²) too.

**Space.** The sort works on the array itself and needs only a few variables, so its extra space is O(1).

**Best case.** If the array is already in order, the first pass makes n - 1 comparisons, finds no swaps, and stops. That's O(n). The early stop is what makes this case fast, and it's the reason the `swapped` flag is there.

So bubble sort is O(n) on sorted input and O(n²) on everything else. For the 2001-value timing array, the worst case would be about two million comparisons, which is why bubble sort is taught as a baseline and rarely used on large data.

---

### Quiz

*These questions are written for this course.*

````quiz
How many comparisons does bubble sort make in the worst case for n values?
○ n
→ Not quite. That's the cost of one pass, and the worst case needs many passes.
◉ n(n - 1) / 2, which grows with the square of n
→ Yes. The passes make n - 1, then n - 2, and so on down to 1 comparisons.
○ log n
→ Not quite. Bubble sort compares neighbors in every pass, so its growth is quadratic.
````

````quiz
What does the swapped flag let bubble sort do?
○ Sort the array in reverse.
→ Not quite. The flag doesn't change the order the sort produces.
◉ Stop early when a pass makes no swaps, since the array must already be in order.
→ Yes. That's why sorted input takes only one pass, which is O(n).
○ Swap values without a temporary copy.
→ Not quite. The flag only records whether a swap happened in the pass.
````

---

### Try it in the runner

Change the visualized array to the values 20 down to 1, in reverse order. Predict the comparison count before you press **Run**. Every pass swaps every pair, and the sort makes 19 passes, with 19, then 18, and so on down to 1 comparison. That totals 190, which is 20 times 19 divided by 2. Then press **Visualize** and watch the purple swaps.

---

Bubble sort is the simplest sort to follow, and it's the baseline for the rest of the chapter. Its growth is O(n²) in the worst case, and the next sorts aim to do better.
