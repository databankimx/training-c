## Summary: Efficiency

This chapter covered how to describe the cost of a program as its input grows, and how to check that cost by counting.

* **Count operations to see growth.** A single loop over n items does n operations, and nested loops over n items do n² operations. Doubling n doubles the first count and quadruples the second.
* **Big O names the growth.** O(n) and O(n²) describe the growth pattern. Constants and smaller terms are dropped, since the largest term decides the growth for large inputs.
* **Big O describes the worst case as input grows.** It compares approaches. It doesn't predict the time on a particular machine.
* **Recursion can repeat work.** The naive Fibonacci recursion makes a tree of calls, and the same values are worked out again and again.
* **Remembering answers removes the repetition.** A memoized version stores each value the first time it's computed, and makes about 2n calls. An array is enough when the keys are small whole numbers.
* **A loop can be the cheapest.** The iterative Fibonacci does n passes and keeps only the last two values.
* **Measure when in doubt.** A counter, passed through a pointer, shows the real growth of a recursive function.
* **Check input at the entry point.** A recursive helper should never see a value that would stop its recursion, so the check runs once, before the first call.

### Check your understanding

*These questions are written for this course.*

````quiz
A loop runs once for each of n items, and inside it another loop runs n times for each item. How many operations does the whole thing take?
○ n
→ Not quite. That's the count for a single loop.
◉ n times n, which is n squared
→ Yes. The inner loop runs n times for each of the n passes of the outer loop.
○ 2n
→ Not quite. Two loops of n each would give 2n, but here the inner loop runs inside the outer one.
````

````quiz
Why is the memoized Fibonacci recursion much cheaper than the naive version?
○ Because it doesn't use recursion.
→ Not quite. It still calls itself, but it avoids work it has already done.
◉ Because each value is worked out once and stored, so later calls for it return at once.
→ Yes. The stored answers remove the repeated calls.
○ Because the compiler optimizes it.
→ Not quite. The difference comes from the algorithm, not from the compiler.
````

````quiz
What does Big O describe?
○ The exact time a program takes on one machine.
→ Not quite. Big O doesn't predict exact times, only how the cost grows.
◉ How the cost grows as the input size grows, usually the worst case.
→ Yes. It describes the growth pattern, and drops the constants and smaller terms.
○ The number of lines of code in a program.
→ Not quite. Big O is about the work done, measured against the input size.
````
