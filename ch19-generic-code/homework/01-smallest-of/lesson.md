## Homework: Smallest of

Write a generic function that returns the smallest element of an array, and use it for numbers and for strings.

The program should:

* write `smallest_of(const void *base, size_t count, size_t size, int (*compare)(const void *, const void *))`, which returns a pointer to the smallest element. It starts with the first element as the smallest, and compares each later element with it. When `count` is 0, it returns `NULL`
* write a comparison for `int` values, and one for strings, where the array holds `const char *` pointers
* in `main`, create an array of the numbers 5, 2, and 9, and print `Smallest number: ` followed by the result
* create an array of the words "pear", "apple", and "fig", and print `Smallest word: ` followed by the result
* call `smallest_of` with a count of 0, and print whether it returned `NULL`

### What to check

The output should be:

```
Smallest number: 2
Smallest word: apple
Empty array: no smallest value
```

The same function gives both results. The string comparison is alphabetical, so "apple" comes before "fig" and "pear". For the string array, the element size is the size of a pointer, not the size of the text.

### Extensions

* Add a generic function that returns the largest element, and check that it works for both arrays.
* Explain why the empty case has to return `NULL`, rather than reading the first element. Say what the caller must do before it uses the result.

---

*This exercise is not from the book. It practices the ideas in Chapter 19, with the void pointers and comparisons from the previous step.*
