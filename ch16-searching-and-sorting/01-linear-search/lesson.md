## Linear search

Searching is the most common thing a program does with a list. Given a list and a value, the question is where the value is, or whether it's there at all. The simplest answer is to look at each element in turn, from the start, until the value turns up or the list runs out. That's linear search.

Here's the search, from `src/main.c`:

```c
static long linear_search(const int values[], size_t count, int target, long *comparisons) {
    for (size_t i = 0; i < count; i++) {
        (*comparisons)++;
        if (values[i] == target) {
            return (long)i;
        }
    }
    return -1;
}
```

The function returns the index of the first match, or `-1` if no element matches. The `comparisons` parameter is a pointer to a counter, as the pointer parameters step showed, and it counts every element the search looked at. That's the measure the efficiency chapter asked for.

### The data

Search works on any list, sorted or not. This step's short list is in no particular order, so you can see every value and its position:

```c
int small[] = {4, 7, 10, 0, 2, 8, 9, 3, 5, 6, 1, 11};
```

The value 3 sits at index 7, so searching for it takes eight comparisons.

The long list holds every whole number from 0 to 1000, once each, in a shuffled order. The shuffle uses a fixed seed, so the order is the same on every run. Its exact order doesn't matter for the lesson, since the search only needs to know where the match is.

Press **Run**. The output is:

```
Data: 12 values
Searching for 3: index 7 after 8 comparisons
Searching 1,001 values
  for 737: index N after N+1 comparisons
  for 5000: NOT FOUND after 1001 comparisons
```

The `N` in the second line is the position of 737 in the shuffled list. It depends on the seed, so the output you see will show a specific number there, and the rule for it is the one in the next section. The C output has no thousands separators, since `printf` doesn't add them portably.

### Two kinds of search

The program searches the long list twice, once for a value that's there and once for one that isn't.

The first search is for 737. Every value from 0 to 1000 is in the list, so 737 is guaranteed to be there, but its position comes from the shuffle. What you can predict is the rule: a value found at index N takes N + 1 comparisons, because the search checks indexes 0 through N before it stops. So the count is never more than 1001.

The second search is for 5000. That's outside the range the list covers, so it can't be in the list. The search still checks all 1001 values, since linear search has no way to know the value is out of range without looking.

### NOT FOUND

The search returns `-1` to mean "not there". Indexes start at 0, so `-1` can never be a real position, which makes it a safe signal. The `describe` function turns that signal into a word, so the output reads `NOT FOUND` instead of a number that looks like an index. Code that calls the search should always check for `-1` before using the index, since using it as a position would read the wrong element, and in C that read has no bounds check to stop it.

### What the counts show

Searching for 3 looks at eight values, from index 0 up to index 7, and then stops at the match. The search for 737 looks at N + 1 values, wherever 737 happens to sit, and the search for 5000 looks at all 1001.

A miss forces the search to check every element, so the cost grows in step with the length of the list. That's O(n), the same growth the efficiency chapter measured for a single loop, and it's the worst case for linear search. The search doesn't get faster just because the list is ordered, since it never uses the order. That changes in the next step.

### Big O analysis

Let n be the number of values in the list.

**Comparisons.** In the worst case, the target is missing or sits at the end of the list, and the search makes n comparisons. That's O(n).

**Best case.** If the target is the first value, the search makes one comparison and stops. That's O(1).

**Average case.** If a found value is equally likely to sit anywhere in the list, the search makes about (n + 1) / 2 comparisons on average. That's still O(n), since the constant factor of one half is dropped.

**Space.** The search keeps only an index and a counter, so its extra space is O(1).

### Watch the search

The program writes `trace.js`, which records every comparison for the short list. Press **Run** first, since the visualizer shows the trace that the run writes. Then press **Visualize** to open the visualizer in your browser. Each bar is one value, and its height is its size. The amber bar is the one being compared. The green bar is the match, when the search finds one.

Use **Next**, **Previous**, the slider, or the arrow keys to move through the search one comparison at a time. **Play** runs it through automatically, and **Speed** sets how long each step stays on screen.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does linear search check the values from the start, one at a time?
○ Because the list has to be sorted first.
→ Not quite. Linear search works on a list in any order, which is why it's the simplest search.
◉ Because it has no information about where the value might be, so it can only look at each one in turn.
→ Yes. Without any order to use, the only safe method is to check every element until the value turns up.
○ Because the computer can only read the first element.
→ Not quite. The search can read any element. It simply doesn't know which one to read first.
````

````quiz
In the example, searching for 5000 checks all 1001 values. What does that show about the worst case?
○ Linear search is fast, since the comparisons are simple.
→ Not quite. The count is the measure of cost, and the simplicity of each comparison doesn't change it.
◉ When the value is missing, every element is checked, so the cost grows with the length of the list.
→ Yes. That's the O(n) worst case, the same growth as a single loop.
○ The search has a bug, since it should stop earlier.
→ Not quite. Checking every element is the only way to be sure a value is missing from an unsorted list.
````

---

### Try it in the runner

Search the short list for 12, and predict what the program prints and how many comparisons it makes before you press **Run**. The value isn't in the list, so the program prints `NOT FOUND`, and every one of the 12 values is checked, which makes 12 comparisons.

Then press **Visualize**, and step through the search. Count the amber bars, and check that the number of frames matches the eight comparisons the program printed.

---

Linear search is the simplest search, and it's the baseline for the rest of this chapter. Its cost is easy to predict, and it doesn't need the list to be sorted. The next step uses sorted data to make the search much cheaper.
