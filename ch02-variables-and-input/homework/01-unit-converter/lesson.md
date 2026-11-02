## Homework: Unit converter

Write a program that converts a temperature from Celsius to Fahrenheit.

The program should:

* ask for a temperature in Celsius, with the prompt `Enter a temperature in Celsius: `
* read it as a `double`, so decimals work
* calculate the Fahrenheit value with the formula `F = C * 9 / 5 + 32`
* print the result as `<celsius> C is <fahrenheit> F`

Store the Fahrenheit value in a `const` variable, since it's calculated once and never changes. Flush the output after the prompt, with `fflush(stdout)`, so the question shows before the program waits for an answer.

### What to check

Try these inputs, and compare your output with the answers:

* `100` should give `100 C is 212 F`
* `0` should give `0 C is 32 F`
* `-40` should give `-40 C is -40 F`

Watch out for integer division. If you write `9 / 5` with two whole numbers, C gives `1`, not `1.8`. Make one of the numbers a decimal, such as `9.0 / 5.0`, to avoid it.

### Extensions

* Add a second conversion, from Fahrenheit back to Celsius, and ask the user which one they want.
* Print the result to one decimal place, using a `%.1f` format in place of `%g`. Explain why `%g` prints `212` and not `212.0`.

---

*This exercise is not from the book. It practices the ideas in Chapter 2.*
