## Walkthrough: Count inversions

`count_inversions` is the direct definition: for each position `i`, it counts the later positions `j` whose value is smaller. It makes n(n − 1) / 2 comparisons, so it's O(n²), and it needs no extra space.

`insertion_moves` runs insertion sort on a copy. The copy keeps the caller's array unchanged, as the exercise requires. Each swap in the sort moves one value past one larger value, which fixes exactly one inversion. So the move count equals the inversion count, and the two outputs match.

The fixed copy of 16 values is the unchecked path the comment marks. The extension replaces it with `malloc`. The check for `NULL` matters because `malloc` returns `NULL` when it can't get the memory, and copying into `NULL` is undefined behavior. The function should return an error, rather than continue, when the allocation fails.

The merge-sort approach in the extension counts inversions in O(n log n), by counting the inversions that cross between the two halves while merging. The merge sort step shows the merge that does the work.
