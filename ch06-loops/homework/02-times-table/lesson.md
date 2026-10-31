## Homework: Times table

Write a program that prints the times table for a number the user enters, from 1 to 10.

The program should:

* ask for a number, with the prompt `Enter a number: `, and read it as an `int`
* use a `for` loop that counts from 1 to 10
* print each line in the form `7 x 3 = 21`, with the number, the counter, and the product

Flush the output after the prompt, with `fflush(stdout)`. The loop should run exactly ten times, whatever number the user enters.

### What to check

Try these inputs, and compare the output with the answers:

* `7` should print `7 x 1 = 7` through `7 x 10 = 70`
* `12` should print `12 x 1 = 12` through `12 x 10 = 120`
* `0` should print ten lines, each ending in `= 0`

Check the last line of each set first. A loop that stops one step early is a common mistake, and the last line shows it straight away.

### Extensions

* Stop the table early when the product passes 50, using `break`. Think about whether the line that passes 50 should print.
* Print the table for every number from 1 to 5 as well, using a nested loop. The inner loop is the table, and the outer loop chooses the number.

---

*This exercise is not from the book. It practices the ideas in Chapter 6.*
