## Walkthrough: Counter

The structure keeps two values: the current count and the starting value. The starting value isn't used by any function in this exercise, but it records what the counter was created with, which the extension about a getter could use.

`counter_create` allocates the counter and sets both values from its argument. The count begins at the starting value, so `counter_create(10)` gives a counter that counts from 10.

`counter_reset` sets the count to zero, as the exercise asks. It doesn't set the count back to the starting value, which is a different behavior, and the output's second line shows the difference: 0, not 10.

The output's last line depends on `counter_create(10)` starting at 10, then one increment to 11. Each counter is destroyed once, at the point it's no longer needed.

For the extension about a default starting value, C can't overload `counter_create`, as the return-values step explained. A separate function such as `counter_create_zero` is the usual C choice, and the names say what each one does.
