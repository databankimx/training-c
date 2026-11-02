## Looping over arrays

Many loops don't need to count at all. They go through every value in an array, one after another, and the work is the same for each element. C has no loop that hands you each value without an index, so the usual pattern is a `for` loop whose counter is the index. The counter visits each position in turn, and the body reads the element at that position.

Here's the program for this step, in `src/main.c`. It starts with an array of integers:

```c
int scores[] = {10, 20, 30, 40, 50};
size_t count = sizeof scores / sizeof scores[0];

printf("Scores:\n");
for (size_t i = 0; i < count; i++) {
    printf("%d\n", scores[i]);
}
```

Press **Run**. The output is:

```
Scores:
10
20
30
40
50
```

The number of elements comes from the arrays chapter: `sizeof scores` is the size of the whole array, and `sizeof scores[0]` is the size of one element, so their quotient is the count, 5. The loop's condition, `i < count`, keeps the counter inside the array, and `scores[i]` reads the element at that position.

The counter is `size_t`, the type that `sizeof` returns. It's unsigned, so it can never be negative. A plain `int` would work for this array, but `size_t` matches the count it's compared with, and the compiler doesn't warn about the comparison.

Read the loop as "for each position from 0 up to the count, print the element there". Compare that with the arrays chapter, where every element was written out by hand. The loop does the same work for any length, and it gets the bound from the array itself.

### Arrays of text

The program then does the same with an array of strings:

```c
char colors[3][8] = {"red", "green", "blue"};
size_t color_count = sizeof colors / sizeof colors[0];

printf("Colors:\n");
for (size_t i = 0; i < color_count; i++) {
    printf("%s\n", colors[i]);
}
```

The output is `red`, `green`, and `blue`, each on its own line. Each row of `colors` is a string of up to seven characters plus its zero byte, so the row width is 8. `colors[i]` is one row, and `%s` prints it up to its zero byte. Here `sizeof colors / sizeof colors[0]` counts the rows, not the characters.

### When the index matters

The loop gives you the index as well as the value, which a range-based loop in other languages doesn't. Use the index when you need to change an element, to skip some of them, or to report a position. The loop can also start or end anywhere, so it can visit only part of an array.

To change an element through the loop, write to `scores[i]`. A value copied into a separate variable is only a copy, so changing that variable leaves the array alone.

---

### Quiz

*These questions are written for this course.*

````quiz
For `int values[5]`, what does `sizeof values / sizeof values[0]` give?
○ 4
→ Not quite. That's the last index, not the number of elements.
◉ 5
→ Yes. The whole array divided by the size of one element gives the count.
○ 20
→ Not quite. That's the size in bytes. Dividing by the size of one element gives the count.
````

````quiz
In `for (size_t i = 0; i < count; i++) { printf("%d\n", scores[i]); }`, what is printed for each pass?
○ The counter, from 0 up to count.
→ Not quite. The counter is the index, but the body prints the element at that index.
◉ The element at position i, for each position from 0 up to count minus one.
→ Yes. The loop visits each position in turn, and prints the element there.
○ The count, once for each element.
→ Not quite. The body prints the element, not the count.
````

---

### Try it in the runner

Add `60` to the end of the `scores` list, so it has six values, and press **Run**. Predict whether the loop needs any other change. It doesn't: the count is worked out from the list, so the loop visits the new element as well, and the output ends with `60`.

Then change `"green"` in the `colors` array to `"orange"`, and predict the second block of output. The loop visits each row in order, so the output is `red`, `orange`, and `blue`. Notice that `orange` is six characters, so it fits in the row width of 8.

---

The index loop is the C way to visit each element of an array, and the count comes from the array itself. The next step covers the two statements that change how any loop runs: `break` and `continue`.
