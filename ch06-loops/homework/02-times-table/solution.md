## Walkthrough: Times table

The example reads the number as a line and converts it with `strtol`. The loop counter runs from 1 to 10 inclusive, which is why the condition is `i <= 10` and not `i < 10`. A condition of `i < 10` would stop at 9 and miss the last line, which is the mistake the exercise asks you to check for.

Each line computes `number * i` directly inside the `printf`, so the loop body does one thing: print one row of the table. The counter and the product are both shown, which makes each line easy to check by hand.

The loop runs ten times whatever the number is. A zero entered by the user gives ten lines ending in `= 0`, because the product is zero each time.

The first extension uses `break`. The line that passes 50 is the one to decide about: if the loop breaks before printing it, that line is missing, and the table stops at the last product that is 50 or less. Choosing the other behavior means checking the product before the break, not after the print.
