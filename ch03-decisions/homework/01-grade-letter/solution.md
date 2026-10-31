## Walkthrough: Grade letter

The example reads the score as a line of text and converts it with `strtol`, the same pattern as the user-input step. The chain then picks one letter, and a single `printf` prints it.

The chain tests the highest band first. A score of 92 passes the first test, so it's an A, and the later tests never run. Because of that order, each test only needs the lower bound of its band: a score that reaches the `>= 80` test has already failed `>= 90`, so it must be below 90.

The boundaries are the risky part. The chain gives 90 to an A, 89 to a B, and 60 to a D, because each test uses `>=`. Writing `>` instead would move every boundary score down a grade, which is the mistake the exercise asks you to check for.

Each branch has braces, as the chapter recommends. That keeps a later edit, such as adding a plus or minus band, from putting a line outside its condition.

The extension about a score outside 0 to 100 belongs at the top of the chain, before the 90 test, since a score of 105 would otherwise be an A without a check. A combined condition such as `score < 0 || score > 100` does the test in one place.
