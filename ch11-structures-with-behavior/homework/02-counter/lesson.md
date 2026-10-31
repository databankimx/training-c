## Homework: Counter

Write an opaque type that counts, with a creation function that sets a starting value.

The module should:

* provide `counter_create`, which takes a starting count and stores it in the structure, which is defined in `counter.c`
* provide `counter_increment`, which adds one to the count
* provide `counter_reset`, which sets the count back to zero
* provide `counter_value`, which takes a `const Counter *` and returns the count
* provide `counter_destroy`, which releases a counter

In `main`:

* create a counter that starts at zero, with `counter_create(0)`. C has no constructor that runs with no arguments, so the starting value is always passed
* call `counter_increment` three times, then print `Count: 3`
* call `counter_reset`, then print `Count: 0`
* create a second counter starting at 10, call `counter_increment` once, and print `Count: 11`
* destroy each counter once it's no longer needed

### What to check

The output should be:

```
Count: 3
Count: 0
Count: 11
```

The first line depends on the three calls, and the second on `counter_reset` returning the count to zero. The last shows that the starting value is used.

### Extensions

* Add a `counter_decrement` function that refuses to go below zero, and return a code when it's called at zero. Decide what the caller should do with the code.
* Give `counter_create` a default starting value, so that `counter_create` with no argument starts at zero. Think about whether C can do that with a function that has a fixed parameter list, and what a separate function for the default would look like.

---

*This exercise is not from the book. It practices the ideas in Chapter 11.*
