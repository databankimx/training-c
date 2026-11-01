## Passing a rule

A lambda is a function written where it's needed. It lets code say "here is the rule" directly in the call, and it's the usual way to customize the standard library. C has no lambda syntax, but the same idea exists: a function pointer. A function is written once, with a name, and its address is passed to the code that needs the rule. The standard library's `qsort` already takes a rule this way, and the previous chapter used it.

Here's the rule for this step, in `src/main.c`. It's a named function with the signature that `qsort` expects:

```c
static int compare_descending(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (y > x) - (y < x);
}
```

The function returns a negative number when `a` should come before `b`, zero when they are equal, and a positive number otherwise. The expression `(y > x) - (y < x)` gives 1, 0, or -1 without a branch, and it doesn't overflow the way a subtraction of two large values could. The call passes the function's name, which is its address:

```c
qsort(values, count, sizeof values[0], compare_descending);
```

The C++ lambda in the lesson was `[](int a, int b) { return a > b; }`. This function does the same work, but it has a name, it's declared once, and the caller says which rule to use.

Press **Run**. The output is:

```
Descending: 9 6 5 4 3 2 1 1
Ascending: 1 1 2 3 4 5 6 9
```

The same array, sorted by two rules, with the rule passed as a value. Passing `compare_ascending` instead of `compare_descending` changes the order and nothing else.

### The rule must be a strict order

A comparison used for sorting must be consistent. If `a` comes before `b`, `b` must not come before `a`, and equal values must compare as zero. The C form of the rule in the C++ lesson is that the function returns negative, zero, or positive, and never contradicts itself. The `(y > x) - (y < x)` form is consistent by construction. A rule that returns true or false inconsistently, or that treats unequal values as equal, can make the sort misbehave, and the library does not check for that.

### The parameters are void pointers

`qsort` calls the rule with pointers to two elements, typed as `const void *`, since it works on any element type. The rule casts them back to `const int *` and reads the values, as the previous chapter's comparison did. A rule written for the wrong element type compiles, and reads the wrong values at run time. The caller and the rule must agree on the type, and the compiler can't check that agreement.

### Naming the rule

A named rule has advantages over an inline one. It can be reused, tested on its own, and read by name at the call. The cost is that it's separated from the code that uses it. The next step covers the case where the rule needs values from its surroundings, which a lambda would capture and a named function cannot see.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `compare_descending` return when its first argument is the smaller value?
○ 0, since the values are not equal.
→ Not quite. Zero means equal, and these values are not equal.
◉ A positive number, meaning the first value should come after the second.
→ Yes. In a descending sort, the smaller value belongs later in the order.
○ A negative number, meaning the first value should come before the second.
→ Not quite. That would put the smaller value first, which is the ascending order.
````

````quiz
Why does the program pass the name `compare_descending` to `qsort`, rather than calling it?
○ Because calling it would sort the array in the wrong order.
→ Not quite. The call would be a single comparison, not a sort.
◉ Because qsort calls the rule itself, for each comparison it needs, so the rule is passed as a function pointer.
→ Yes. Passing the address lets qsort decide when the rule runs.
○ Because the rule has no return value.
→ Not quite. It returns a number that qsort uses to order the elements.
````

---

### Try it in the runner

Pass `compare_ascending` to the first `qsort` call instead, and predict the order of the first line before you press **Run**. It prints `Descending` with the values in ascending order, 1 1 2 3 4 5 6 9, since the label and the rule no longer agree. The output shows that the label is only text, and the rule is what decides the order. Restore the original rule before you continue.

---

A rule passed as a function pointer gives `qsort` the same power as the lambda in the sort. The next step covers the cases where the rule needs a value from its surroundings, which C passes in as a context pointer.
