## Homework: Operator menu

Write a calculator that asks for an operator and two numbers, and prints the result. This exercise uses a `switch`, and it also needs an `if` inside one of its cases.

The program should:

* ask for an operator, with the prompt `Enter an operator (+, -, *, /): `, and read the first character as a `char`
* ask for two numbers, as `double` values, with the prompts `Enter the first number: ` and `Enter the second number: `
* use a `switch` on the operator to choose the calculation: `+`, `-`, `*`, or `/`
* print `Cannot divide by zero.` when the operator is `/` and the second number is 0, rather than dividing
* print `Unknown operator.` for any other character

Flush the output after each prompt, with `fflush(stdout)`, and put a `break` at the end of every case.

### What to check

Try these inputs, and compare the output with the answers:

* `+`, `2`, `3` should print `5`
* `*`, `4`, `2.5` should print `10`
* `/`, `9`, `3` should print `3`
* `/`, `7`, `0` should print `Cannot divide by zero.`
* `%`, `1`, `2` should print `Unknown operator.`

The division by zero case matters most. Dividing a `double` by zero doesn't cause an error in C, but it gives infinity, which isn't a useful answer for this program.

### Extensions

* Add a `%` case that gives the remainder. Think about whether `double` values support `%`, and what you'd need to change if they don't. The math library has a function for remainders of decimals.
* Print the result to two decimal places, using `%.2f` in place of `%g`. Check whether whole-number answers, such as `5`, now print as `5.00`.

---

*This exercise is not from the book. It practices the ideas in Chapter 3.*
