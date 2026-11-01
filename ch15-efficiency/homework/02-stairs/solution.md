## Walkthrough: Stairs

The recurrence has the same shape as Fibonacci, so the call tree has the same shape too. Each call for n makes calls for n − 1 and n − 2, and the naive count is the same as the Fibonacci count for the same n. That's why the output's naive column for n = 10 is 177, the value from the Fibonacci step.

The base cases are the difference. Both ways(0) and ways(1) are 1, where Fibonacci has 0 and 1. The helper returns 1 for any n below 2, and the sums are the same from there on. The ways are larger than Fibonacci numbers at each n: ways(10) is 89, which is Fibonacci's 55 shifted one place along.

The memoized count is 2n − 1, since each value from 2 up to n is worked out once, and each one makes two calls. The check on the memo array comes after the call counter goes up, so the counter measures calls, not computed values, the same as in the Fibonacci step.

The negative check happens at the entry point, before the helper starts, so a refused value never reaches the recursion and isn't counted.
