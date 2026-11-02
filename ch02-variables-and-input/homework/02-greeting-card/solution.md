## Walkthrough: Greeting card

The example uses the same pattern as the user-input step. Each question is printed and flushed, and each answer is read as a whole line. The name is read with `fgets`, so a name with spaces arrives complete, and the newline is removed with `strcspn`. The age is read as a line and converted with `strtol`.

The greeting uses `age + 1` directly in the `printf`, because the age itself doesn't change. The value of `age` is still 36 afterwards, and only the sentence says 37.

The `const` on `age` says that the answer is never changed after it's read, which is what the lesson asks for. Using `const` on values that are read once and used for output is a good habit, since a reader knows at a glance that the value is fixed.

If the age is typed as `thirty-six`, `strtol` returns 0, and the greeting says the person will be 1 next year. The error handling chapter shows how to reject that input instead.
