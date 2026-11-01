## Walkthrough: Count and sum

`for_each_value` knows nothing about the totals. It only calls the rule once for each value and passes the context along. The rule is the part that knows what to do, and the context is the part that carries the state. Keeping the two separate is the reason the same loop can be used with a different rule later.

The rule receives the context as a `void *`, and casts it back to `Totals *`. The cast is safe only because `main` passed a `Totals` as the context. The rule does its work through the pointers, which refer to the variables in `main`, so the counts persist after the loop.

For the extension with copies, the rule would update its own copies. The caller's variables would keep their zeros, and the output would be `Even count: 0` and `Sum of evens: 0`. The copy is updated, but nothing outside it sees the change, which is the same effect as the lambda that captured by copy.
