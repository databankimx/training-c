## Ch16 · Searching and Sorting

Finding a value and putting values in order are two of the most common jobs a program does. This chapter covers the classic algorithms for both, traces each one step by step, and counts the work it does, so you can compare them with the growth rates from the efficiency chapter. It ends with the standard library versions, which you'll use in practice.

The steps are:

* [Linear search](#goto/01-linear-search): checking values in turn, and the cost of a miss.
* [Binary search](#goto/02-binary-search): halving a sorted array, and why the sort has to come first.
* [Bubble sort](#goto/03-bubble-sort): swapping neighbors, and the early stop on sorted input.
* [Selection sort](#goto/04-selection-sort): picking the smallest value for each place.
* [Insertion sort](#goto/05-insertion-sort): sliding each value into place, and adapting to nearly sorted input.
* [Merge sort](#goto/06-merge-sort): splitting, sorting, and merging, with O(n log n) in every case.
* [Quick sort](#goto/07-quick-sort): partitioning around a pivot, and the pivot choices that decide the worst case.
* [The standard library sort and search](#goto/08-standard-library): `qsort` and `bsearch`, with comparison functions in place of C++ iterators.
* [Summary](#goto/09-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C arrays are sorted and searched through indexes and pointers, and the standard library provides `qsort` and `bsearch` in place of the C++ iterator-based functions.*
