## Homework: Word totals

Print each word and its count from a list of words and counts, then print the total of all the counts. C has no map and no structured bindings, so the words are kept in an array of structures with named members, and each loop reads the parts by name.

The program should:

* create an array of structures, each with a word and a count, holding "apple" with 3, "fig" with 2, and "pear" with 5, in that order
* loop over the array with a pointer to each entry, printing the word and its count on one line, separated by a space
* add the counts in a second loop, and print `Total: ` followed by the sum

### What to check

The output should be:

```
apple 3
fig 2
pear 5
Total: 10
```

The array keeps the order it was written in, so the words come out in alphabetical order only because they were written that way. Reorder the array, and the output follows the new order, which is the difference from the C++ map.

### Extensions

* Add an entry for "kiwi" with 4, and check that the total becomes 14. Decide where the entry belongs in the array, and explain what would happen if it were added to the wrong place.
* Write a function that returns the count for a given word, and returns -1 when the word is missing. Explain why -1 is a weaker answer here than the optional structure from the chapter.

---

*This exercise is not from the book. It practices the ideas in Chapter 25, with the structures from Chapter 10.*
