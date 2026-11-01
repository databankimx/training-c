## Summary: Searching and sorting

This chapter covered two families of algorithms: finding a value in an array, and putting an array in order. For each one, you wrote the algorithm, traced it, counted its work, and then used the library version.

* **Linear search checks values in turn.** It works on any array, costs O(n) in the worst case, and O(1) in the best case.
* **Binary search halves a sorted array.** It costs O(log n) comparisons, but only works on a sorted array, and the sort costs more than a single search.
* **Bubble sort swaps neighbors.** It's O(n²) in the worst case, and O(n) on a sorted array, since it stops early when a pass makes no swaps.
* **Selection sort picks the smallest value for each place.** It's O(n²) comparisons in every case, and at most O(n) swaps.
* **Insertion sort slides each value into place.** It's O(n) on a nearly sorted array and O(n²) in the worst case.
* **Merge sort splits and merges.** It's O(n log n) in every case, at the cost of O(n) extra space.
* **Quick sort partitions around a pivot.** It's O(n log n) on average and O(n²) in the worst case, which depends on the pivot choices.
* **The library sort and search.** `qsort` sorts with a comparison function you supply, and `bsearch` finds a key in a sorted array. C has no `lower_bound`, so the chapter writes one. The costs are O(n log n) for sorting, depending on the implementation, and O(log n) for searching sorted data.

### Check your understanding

*These questions are written for this course.*

````quiz
Which sort makes exactly n(n - 1) / 2 comparisons on any input?
○ Bubble sort
→ Not quite. Bubble sort stops early when a pass makes no swaps, so its count changes with the input.
◉ Selection sort
→ Yes. Each pass looks at every remaining value, whatever the order.
○ Quick sort
→ Not quite. Quick sort's comparisons depend on the pivots it chooses.
````

````quiz
A sorted array is searched many times. Which combination costs the least overall?
○ A linear search on each search
→ Not quite. That costs O(n) for every search.
◉ Sort once, then use binary search on each search
→ Yes. The sort is paid once, and each search costs O(log n).
○ Bubble sort once, then linear search on each search
→ Not quite. Sorting with bubble sort costs O(n²), and linear search is still O(n) for each search.
````

````quiz
Which sort is O(n) in the best case, when the array is already in order?
○ Merge sort
→ Not quite. Merge sort splits the array at every level, so its cost is O(n log n) in every case.
◉ Insertion sort
→ Yes. Each value is compared once with the value before it, and no moves are needed.
○ Quick sort
→ Not quite. Quick sort's best case is O(n log n), when every pivot splits the array evenly.
````
