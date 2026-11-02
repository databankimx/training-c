## Void pointers and element sizes

A macro repeats its text, and it isn't type-checked. The function-template approach is closer to what C can do well: write one function that works on any type. C does it with `void *`, a pointer that can point at any object. The function can't know the type of what it points at, so the caller tells it what it needs: the size of one element, and a function that compares two elements.

This is how `qsort` and `bsearch` from the previous chapter work. Here's the swap from `src/main.c`, which swaps two elements of any type:

```c
static void swap_elements(void *a, void *b, size_t size) {
    unsigned char *first = a;
    unsigned char *second = b;
    for (size_t i = 0; i < size; i++) {
        unsigned char temp = first[i];
        first[i] = second[i];
        second[i] = temp;
    }
}
```

The function converts each `void *` to a pointer to bytes, and swaps the bytes one at a time. It never needs the type, because the `size` says how many bytes make up one element. The same function swaps two `double` values, two structures, or any other type, as long as the caller passes the element's size.

Press **Run**. The output is:

```
Swapped doubles: 2.5 1.5
Found 9 at index 1
Found bob at index 1
Not found: 7
```

### The search needs a comparison

The search function, `index_of`, uses the same ideas. It takes the array as a `void *`, the number of elements, the size of each, the target as a `void *`, and a comparison function:

```c
static size_t index_of(const void *base, size_t count, size_t size, const void *target,
                       int (*compare)(const void *, const void *)) {
    const unsigned char *bytes = base;
    for (size_t i = 0; i < count; i++) {
        if (compare(bytes + i * size, target) == 0) {
            return i;
        }
    }
    return count;
}
```

The element at index `i` is found by moving `i * size` bytes from the start. The comparison is a pointer to a function, and the caller chooses it. That's the part a template would have generated: a version of the comparison for each type. In C, the programmer writes one comparison per type, and passes it in.

### Comparisons are typed

Each comparison function reads its arguments with the correct type. `compare_int` reads `int` values, and `compare_string` reads pointers to `char`. The string comparison has one more step, since the array holds pointers, so the function reads a pointer first and then compares the text. Passing the wrong comparison compiles, because the parameters are `void *`, so the mistake shows up only when the program runs. That's the cost of this approach.

### Element sizes must match

The caller passes `sizeof values[0]`, the size of one element, rather than the size of the whole array. A wrong size reads the wrong bytes: too small, and the search misses elements; too large, and it reads past the end of the array. Writing the size as `sizeof` of an element keeps the two in step, since the size comes from the same declaration as the array.

### Compared with a template

A C++ function template gets its comparison and its type from the compiler, and checks both at compile time. The C version does neither: the comparison and size are supplied by the caller and checked only by care. The benefit is that the code is compiled once, and it works with any type, including types not known when the library was written. That's the same trade-off `qsort` makes, and it's why its comparison is a function pointer.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `swap_elements` take a size?
○ Because C needs a size for every function parameter.
→ Not quite. Only the functions that work on untyped memory need to be told the size.
◉ Because a void pointer doesn't know the type, so the size of one element says how many bytes to swap.
→ Yes. The function swaps bytes, and the size tells it how many make up one element.
○ Because the function reads the size from the array.
→ Not quite. A void pointer carries no size, so the caller must pass it.
````

````quiz
What goes wrong if a caller passes the size of the whole array instead of one element?
○ Nothing, since the size is only a hint.
→ Not quite. The size decides which bytes are read, so the wrong size changes the result.
◉ The search reads the wrong bytes, and can read past the end of the array.
→ Yes. Each element is found by moving the element size, so an oversized value runs off the end.
○ The compiler refuses the call.
→ Not quite. A void pointer accepts any size, so the mistake is not caught at compile time.
````

---

### Try it in the runner

Change `compare_int` to compare only the first byte of each `int`, by reading the values as `unsigned char`, and predict what `index_of` reports for the value 9 before you press **Run**. The first byte of 9 and 4 and 2 differ in a small-endian machine, so the search still finds 9 at index 1. The lesson's point is that the comparison decides what counts as equal, and a comparison that looks at too little can report a match where none exists. Restore `compare_int` before you continue.

---

A void pointer with an element size and a comparison function gives one routine for many types, at the cost of checks the compiler no longer makes. The chapter summary follows, and then two homework exercises that use these functions.
