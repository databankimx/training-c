## Walkthrough: Swap with pointers

The example reads both numbers into `a` and `b`, then makes two pointers, `pa` and `pb`, that hold their addresses. The swap is three lines. `temp` saves the value at `pa`, then the value at `pb` is copied into the place `pa` points to, and finally `temp` is copied into the place `pb` points to.

The temporary variable is needed because the first copy overwrites `a`. Without `temp`, the value of `a` would be lost before it's copied into `b`, and both variables would end up holding `b`'s original value.

The second case, two equal values, works without any special check. Copying 5 over 5 changes nothing, so the output is `a = 5, b = 5`, as the exercise expects.

The extension asks for the swap inside a function. The pointers and the three lines of the swap stay the same, and the function receives `&a` and `&b` from `main`. Once you write that version, notice that the function's parameters are pointers, and the body reads and writes through them with `*`, just as these lines do.

The extension about `NULL` belongs before the swap. A swap through a null pointer reads memory at address zero, which is undefined behavior. The check must come first, because the first read is already the mistake.
