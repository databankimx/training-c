## Walkthrough: Factorial

Each function has one job. `factorial_recursive` calls itself on one less than its argument, and stops at the base case, which is 1 or less. Every call multiplies its own `n` by the result of the smaller call, so the product builds up on the way back.

`factorial_loop` starts its result at 1, and multiplies it by each number from 2 up to `n`. For n of 0 or 1 the loop body never runs, so the result stays at 1, which is why the loop version gets 0! right without a special case.

`main` uses a loop of its own to visit each value from 0 to 10, and the conditional in the `printf` prints `agree` only when the two results match. The check is what makes the exercise a test of the functions, not just a printout.

The extension about 13! is worth doing carefully. 12! is 479001600, which fits in an `int`, but 13! is about 6.2 billion, which doesn't. In C that's signed overflow, which is undefined behavior, so the printed value can't be relied on. The fix is a wider type such as `long long`. The variables lesson noted that the size of a type depends on the compiler, and `long long` is the type C provides for larger whole numbers.
