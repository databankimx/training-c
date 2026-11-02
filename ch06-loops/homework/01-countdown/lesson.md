## Homework: Countdown

Write a program that counts down from a number the user enters, and then announces the launch.

The program should:

* ask for a starting number, with the prompt `Enter a starting number: `, and read it as an `int`
* print each number from the starting value down to 1, one per line
* print `Liftoff!` after the last number

Use a `for` loop with a counter that decreases. Flush the output after the prompt, with `fflush(stdout)`, as in the earlier chapters.

### What to check

Try these inputs, and compare your output with the answers:

* `3` should print `3`, `2`, `1`, then `Liftoff!`
* `1` should print `1`, then `Liftoff!`
* `0` should print only `Liftoff!`, because there's nothing to count

The last case is the one to think about. A loop that starts at 0 and counts down with `i > 0` never runs. If you wrote `i >= 0` instead, the output would include 0, which isn't wanted here.

### Extensions

* Print the countdown on a single line, separated by spaces, rather than one number per line. You'll need to think about where the spaces go, so that the last number isn't followed by one.
* Change the loop so it counts down by twos, and check what happens when the starting number is odd.

---

*This exercise is not from the book. It practices the ideas in Chapter 6.*
