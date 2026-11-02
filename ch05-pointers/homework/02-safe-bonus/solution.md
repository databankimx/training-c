## Walkthrough: Safe bonus

The example keeps the score in `points`, and a pointer `score` that holds its address. The first bonus is added through `score`, and the check `score != NULL` comes first, so the dereference only happens when there's a value to reach.

The second pointer, `missing`, is `NULL` on purpose, to show the branch that has nothing to update. The `else` prints the message and leaves `points` alone. Reading `*missing` or writing through it would be undefined behavior, which is why the test sits in front of every use.

The final `Points: 60` shows that the second bonus changed nothing. If it had gone through the null pointer, the program might have crashed, or changed some other memory, and the output could look wrong in a place far from the bug.

The extension about a function puts the same check inside the function. The check still has to come before the dereference, whether the pointer arrives as a parameter or is declared in `main`.
