## Walkthrough: Countdown

The example reads the starting number as a line and converts it with `strtol`, the same pattern as the other input exercises. The `for` loop starts its counter at that number, and the condition `i > 0` keeps it going while the counter is still positive. The step `i--` moves the counter down by one after each pass.

The case of 0 is the one the exercise asks you to think about. The loop's first check is `0 > 0`, which is false, so the body never runs, and only `Liftoff!` prints. With `i >= 0`, the body would run for 0 and print it, which is wrong for a countdown that should stop at 1.

`Liftoff!` is printed after the loop, not inside it. Placing it there means it appears once, whatever the starting number is.

The extension about a single line is the place where the spaces need care. Printing a space before each number, instead of after it, avoids a trailing space at the end of the line.
