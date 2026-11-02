## Homework: Grade letter

Write a program that turns a numeric score into a letter grade.

The program should:

* ask for a score from 0 to 100, with the prompt `Enter a score (0-100): `, and read it as an `int`
* print the letter for the score, using these bands:
  * 90 or above is `A`
  * 80 or above is `B`
  * 70 or above is `C`
  * 60 or above is `D`
  * anything below 60 is `F`
* print the result as `Your grade is B`, for example

Use an `if` and `else if` chain, with braces around every branch. Don't write a separate test for every score. Let the order of the chain do the work, since each test only needs to check the lower bound of its band.

Flush the output after the prompt, with `fflush(stdout)`, so the question shows before the program waits for an answer.

### What to check

Try these scores:

* `95` should give `A`
* `90` should give `A`, because 90 is in the top band
* `89` should give `B`
* `60` should give `D`
* `59` should give `F`

The boundary values matter most. A score of exactly 90 is an A, and 89 is a B.

### Extensions

* Reject a score outside 0 to 100, and print a message instead of a grade. You'll need a condition that combines two comparisons, which the logical operators lesson covers.
* Add plus and minus grades, such as `B+` for 87 to 89. Think about where the new tests belong in the chain.

---

*This exercise is not from the book. It practices the ideas in Chapter 3.*
