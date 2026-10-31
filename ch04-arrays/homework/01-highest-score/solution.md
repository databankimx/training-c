## Walkthrough: Highest score

The example reads each score into its own element, `scores[0]`, `scores[1]`, and `scores[2]`, with the same prompt, flush, and read pattern used throughout the chapters. Reading the three scores by hand is what the exercise asks for, since a loop would come later.

The comparison starts from the first score: `int highest = scores[0];`. Each of the next two scores is then compared with the highest so far, and replaces it only when it's larger. Starting from the first element, rather than from a value such as 0, means the method still works when every score is negative.

The tie case works because the tests use `>`, not `>=`. When two scores are equal, the first one stays the highest, and the printed value is the same either way. The exercise asks you to check that the comparisons don't depend on the scores being different, and they don't.

The example uses two `if` statements, not an `if` with `else if`. Each `if` compares a score with the running highest, and the chain of `else if` would stop after the first match, which is wrong here. The lesson's hint suggested `else if`, and the walkthrough explains why the separate tests are the right choice for finding a maximum.
