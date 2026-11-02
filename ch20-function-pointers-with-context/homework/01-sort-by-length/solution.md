## Walkthrough: Sort by length

The comparison first compares lengths, using `strlen` on each word. If the lengths differ, the shorter word comes first. If they're equal, the comparison falls back to the original index, which is unique for each word, so the comparison never reports two different words as equal.

That fallback is what the C++ `std::stable_sort` provides in the library. C's `qsort` has no such promise, so the program states the rule itself. With the tie-break in place, "pear" (original index 0) comes before "kiwi" (index 3), whatever the sort does with equal lengths.

Removing the tie-break is the extension to try. Equal lengths then compare as equal, and the order of "pear" and "kiwi" depends on the sort's internal steps. The output can change with the library, the array size, or the input, and nothing in the rule guarantees it.
