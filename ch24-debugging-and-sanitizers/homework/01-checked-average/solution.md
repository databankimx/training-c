## Walkthrough: Checked average

`average` accumulates the total in a `long long`, so the sum can't overflow for any reasonable list of `int` values, and then divides as `double`. The cast to `double` is what keeps the fraction: 20 divided by 4 is 5 either way, but 21 divided by 4 would otherwise give 5 and lose the 0.25.

The assertion states the caller's promise. With a count of 0, the division would be by zero, and the assertion stops the program at the call with a clear message, which is the bug report the assertions chapter described. A debug build keeps the assertion, so the mistake is found while the program is tested.

For the extension that returns an error instead, the caller can be given a way to handle an empty list, which fits a case where empty input really does happen. The function then reports the condition through its return value, and `main` decides what to print.
