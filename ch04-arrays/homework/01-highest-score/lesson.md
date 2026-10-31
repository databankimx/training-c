## Homework: Highest score

Write a program that stores three scores in an array, and prints the highest.

The program should:

* declare an `int` array with three elements
* ask for each score in turn, with the prompts `Score 1: `, `Score 2: `, and `Score 3: `, and store each one in the array
* compare the three elements, and print `The highest score is 85`, using the highest value

Flush the output after each prompt, with `fflush(stdout)`. You don't need a loop yet, so write out the three reads and the comparisons by hand. Keep the highest value found so far in its own variable, and compare each score with it in turn.

### What to check

Try these sets of scores:

* `70`, `85`, `60` should give `85`
* `90`, `90`, `40` should give `90`, since a tie is still a highest score
* `50`, `50`, `50` should give `50`

The tie case matters. Make sure your comparisons don't depend on the scores being different.

### Extensions

* Print the position of the highest score as well, such as `The highest score is 85, in position 2`.
* Add a fourth score, and check that the program still works. What changed?

---

*This exercise is not from the book. It practices the ideas in Chapter 4.*
