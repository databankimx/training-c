## Walkthrough: Count in range

The condition `values[i] >= low && values[i] <= high` includes both ends, which is the boundary the exercise tests. Using `<` where `<=` belongs would drop a value that sits exactly on a limit, which is the off-by-one error from the finding-bugs step. The 1-to-5 range is the check that catches it, since both 1 and 5 must be counted.

The extension that counts strictly between the limits changes both comparisons to `>` and `<`. For the range 2 to 4 it counts only the 3, so the answer is 1 rather than 3. The difference is exactly the two values on the limits.

For the debugger extension, step over the loop for the range 2 to 4 and watch `matches`. It increases on the passes for 2, 3, and 4, and stays the same on the others. That's the behavior the output depends on, and the debugger shows it directly.
