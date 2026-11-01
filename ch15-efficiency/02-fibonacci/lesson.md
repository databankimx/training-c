## Fibonacci: one problem, three costs

The Fibonacci sequence starts with 0 and 1, and each later number is the sum of the two before it: 0, 1, 1, 2, 3, 5, 8, and so on. Its definition is recursive, since the value for `n` is defined in terms of the values for `n - 1` and `n - 2`. That makes it the usual first example of recursion, and the usual first example of a recursion that is correct but slow.

Here's the program for this step, in `src/main.c`. It has three versions of the calculation. The naive helper follows the definition exactly:

```c
static long long fib_naive_helper(int n, long long *calls) {
    (*calls)++;
    if (n < 2) {
        return n;
    }
    return fib_naive_helper(n - 1, calls) + fib_naive_helper(n - 2, calls);
}
```

The naive helper is easy to read. The `calls` parameter is a pointer to a counter, as the pointer parameters step described. Each call adds one to the counter that `main` owns, so the program can report how much work the recursion did.

Press **Run**. The output is:

```
n = 10: value 55, naive calls 177, memoized calls 19
n = 20: value 6765, naive calls 21891, memoized calls 39
n = 30: value 832040, naive calls 2692537, memoized calls 59
n = -1 refused: n must not be negative
```

The output has no thousands separators, since `printf` doesn't add them portably. The numbers are the same as the C++ version's.

### The naive count grows fast

Look at the naive column. Ten more steps in `n` multiply the calls by about a hundred. Each call to `fib_naive_helper(n)` makes two more calls, one for `n - 1` and one for `n - 2`, and those make two more each. The calls form a tree, and the tree is nearly as large as the Fibonacci number it computes. The count grows at the same rate as the value itself, which grows exponentially. The program counts the calls directly, so the growth is measured rather than assumed.

Most of that work is repeated. `fib_naive_helper(20)` calls `fib_naive_helper(18)` directly, and it also calls `fib_naive_helper(19)`, which calls `fib_naive_helper(17)` and `fib_naive_helper(18)` again. The value for `18` is worked out twice, and the value for `17` is worked out three times. The repetition is the whole problem.

---

### Remember the answers

The memoized version fixes the repetition. The memo array stores each value the first time it's worked out, and a later call for the same `n` returns the stored value straight away. Here is the whole helper, as it appears in the program:

```c
static long long fib_memo_helper(int n, long long memo[], long long *calls) {
    (*calls)++;
    if (n < 2) {
        return n;
    }
    if (memo[n] >= 0) {
        return memo[n];
    }
    long long result = fib_memo_helper(n - 1, memo, calls) + fib_memo_helper(n - 2, memo, calls);
    memo[n] = result;
    return result;
}
```

The two lines that matter are the check on `memo[n]`, which returns the stored answer, and the line `memo[n] = result`, which stores a new one. The array starts with every entry set to -1. A Fibonacci value is never negative, so -1 can mean "not yet computed" without a second flag.

The C++ version uses a `std::map` for this job. C's standard library has none, and the containers chapter built a hash table that could do it. An array is enough here, because the keys are the whole numbers from 0 to a known limit. The array is the simpler choice when the keys are small and known in advance.

Each value from 2 up to `n` is worked out once, and each one makes two calls. The count works out to `2n - 1`, which is why the memoized column grows by 2 per step rather than by a factor.

---

### The loop is the cheapest

The loop version doesn't recurse at all:

```c
static long long fib_loop(int n) {
    long long previous = 0;
    long long current = 1;
    if (n == 0) {
        return 0;
    }
    for (int i = 1; i < n; i++) {
        long long next = previous + current;
        previous = current;
        current = next;
    }
    return current;
}
```

It keeps the last two values, and moves forward one step at a time. Its work is `n` passes through the loop, which is the simplest possible growth: O(n), with no memo and no call tree. The three columns in the output agree, and the program checks that they do: a `(MISMATCH)` note would appear after any line where they differed.

Recursion isn't wrong. It's the most direct way to write a definition like this one. The lesson is that a recursive definition can hide a large amount of repeated work, and that a program should be checked for it, either by counting or by reasoning about the tree of calls.

### Checking the input

The Fibonacci sequence is defined for whole numbers from zero upwards, so the input has to be checked. The check is a separate function, `check_n`, which returns a code and runs once before any recursion starts:

```c
static int check_n(int n) {
    if (n < 0) {
        return -1;
    }
    return 0;
}
```

The recursive calls only ever pass `n - 1` and `n - 2` from a value of two or more, so they can't go negative. The check belongs at the entry point, and the helpers never see a negative value.

Without the check, a negative `n` would never reach a base case. `n - 1` and `n - 2` would keep going below zero, and the recursion would run until the program runs out of stack space and crashes. The return code stops that before the first call, and `main` reports the refusal. C has no exceptions, so the check is a return value, as the error-handling chapter showed.

You could make `n` an unsigned type, which holds only zero and positive values. It would not give the same protection, since a negative value passed in would become a very large positive one. A check on a signed value is the clearer option, and it reports the problem.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the naive Fibonacci recursion repeat so much work?
○ Because the compiler runs each call twice.
→ Not quite. Each call is made once, but the calls overlap with each other.
◉ Because the same smaller values are needed by many different calls, and each one is worked out again.
→ Yes. The tree of calls reaches the same values through different paths.
○ Because the sequence has no base case.
→ Not quite. It has base cases at 0 and 1, which stop the recursion.
````

````quiz
How many calls does the memoized version make for `n = 10`, according to the output?
○ 10
→ Not quite. The count is about twice n, since each value makes two calls.
◉ 19
→ Yes. The count is 2n - 1, so 2 times 10 minus 1.
○ 177
→ Not quite. That's the naive count, which repeats work.
````

---

### Try it in the runner

Change the first size in `sizes` from `10` to `40`, and predict the naive call count before you press **Run**. The formula is 2 times the Fibonacci number for 41, minus 1, which is 331,160,281. That's more than three hundred million calls, so the program takes a few seconds. Predict the memoized count too. It's 79.

Then change `fib_memo_helper` so it doesn't store the result in `memo[n]`, and predict the memoized count for `n = 10`. The memo is then never filled, so the memoized version makes the same calls as the naive one, 177. The stored answers are what make the difference. Restore the line before you continue.

---

The naive recursion is clear and expensive, the memoized recursion keeps the clarity and removes the repeated work, and the loop is cheapest. The next step puts these counts into a summary of how to read a growth rate from a program.
