## Homework: Sort by length

Sort a list of words from shortest to longest, with a comparison function that decides the order. Words of the same length should keep the order they had in the list.

The program should:

* create an array of the words "pear", "fig", "banana", and "kiwi", in that order
* give each word its original position, in a structure with a `word` pointer and an `original` index
* write a comparison function for `qsort` that returns the shorter word first, using `strlen`
* when two words have the same length, order them by their original index, so the result doesn't depend on how `qsort` handles equal values
* print `By length:` followed by each word, with a space before each one

### What to check

The output should be:

```
By length: fig pear kiwi banana
```

"pear" and "kiwi" both have four letters, and "pear" came first in the list, so it stays first. That's the stability this exercise is testing. `qsort` does not promise that equal values keep their order, so the tie-break on the original index is what makes the result certain.

### Extensions

* Remove the tie-break, and run the program several times, or with a different array size. Explain whether the order of "pear" and "kiwi" is guaranteed.
* Write the comparison so equal lengths are ordered alphabetically instead, and check the output.

---

*This exercise is not from the book. It practices the ideas in Chapter 20, with the sorting from Chapter 16.*
