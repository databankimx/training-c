## Optional values

Many functions can't always produce a result. A search might find nothing, a parse might fail, and a lookup might have no entry. Older C code often returned a magic value, such as -1, to mean "no answer". That works only until a valid result happens to match the magic value, and the caller can forget to check for it.

C++ solves this with `std::optional`, which puts the possibility of no answer in the return type. C has no optional type, but it can express the same idea with a small structure. The result carries a flag that says whether the value is present, and the caller must read the flag before reading the value.

Here's the structure from `src/main.c`:

```c
typedef struct {
    bool found;
    size_t index;
} MaybeIndex;
```

`find_index` returns that structure. It sets `found` to true and fills in `index` when it finds the target, and clears `found` when it doesn't:

```c
static MaybeIndex find_index(const int values[], size_t count, int target) {
    for (size_t i = 0; i < count; i++) {
        if (values[i] == target) {
            MaybeIndex result = {true, i};
            return result;
        }
    }
    MaybeIndex result = {false, 0};
    return result;
}
```

Press **Run**. The output is:

```
Found at 1
Not found
-1
```

The first search finds 8 at index 1, so `found` is true and the program prints the index. The second search finds nothing, so the program prints `Not found`, and the fallback function gives -1.

### Checking and using the result

The caller reads the flag before the value, as the C++ lesson's `if (found)` does:

```c
MaybeIndex found = find_index(values, count, 8);
if (found.found) {
    printf("Found at %zu\n", found.index);
}
```

The fallback works like `value_or`, and is written as a function, since C has no member functions on a structure:

```c
static long index_or(MaybeIndex maybe, long fallback) {
    return maybe.found ? (long)maybe.index : fallback;
}
```

The `index` member holds 0 when nothing was found, so reading it directly on an empty result gives a value that looks valid. That's the C version's weakness. The C++ optional makes `*` on an empty result undefined behavior, which is also a mistake, but the struct here does not even stop the read. Only the convention that the flag is checked first protects the program.

### Why a flag beats a magic value

A magic value has no room for a valid answer that happens to equal it. An index of -1 can't be confused with a real position, but a value of 0 could be, and a function that returns 0 for "not found" would report index 0 as a real match. The flag removes that choice: the value can take any number, since the flag carries the answer to whether it's there.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `MaybeIndex` tell the caller that a bare `size_t` return value would not?
○ How many values the array holds.
→ Not quite. The count is passed in separately.
◉ Whether an index was found at all, so the caller can tell a missing result from a real one.
→ Yes. The flag is the answer to the question the caller needs to ask first.
○ The type of the array elements.
→ Not quite. The structure says nothing about the element type.
````

````quiz
Why is returning 0 for "not found" a mistake in this design?
○ Because 0 is not a valid index.
→ Not quite. 0 is a valid index, which is the whole problem.
◉ Because index 0 is a real position, so the caller can't tell "not found" from a match at the first element.
→ Yes. That's the same problem a magic value always has, and the flag avoids it.
○ Because the compiler refuses to return 0 from a function.
→ Not quite. The compiler accepts it, and the mistake is in the design.
````

---

### Try it in the runner

Call `find_index` for 4, and print the index with `index_or` and a fallback of -1. Predict the output before you press **Run**. The value 4 is at index 0, and the flag is set, so the output is 0. The answer is a real zero, not a missing value, and the flag is what shows the difference.

---

A flag next to the value gives C the same visible case for "no answer" that `std::optional` gives C++. The next step is the chapter summary, and then two homework exercises that use these structures and the C23 features.
