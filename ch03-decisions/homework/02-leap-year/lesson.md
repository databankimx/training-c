## Homework: Leap year

Write a program that decides whether a year is a leap year.

The rules are:

* A year divisible by 4 is a leap year.
* But a year divisible by 100 is not, unless it's also divisible by 400.

So 2024 is a leap year, 1900 is not, and 2000 is.

The program should:

* ask for a year, with the prompt `Enter a year: `, and read it as an `int`
* print `2024 is a leap year.` or `2023 is not a leap year.`, using the year the user entered

Use the `%` operator for divisibility. A value is divisible by 4 when `year % 4` is 0. Combine the rules with `&&`, `||`, and `!`, and use braces on every `if`.

Flush the output after the prompt, with `fflush(stdout)`, so the question shows before the program waits for an answer.

### What to check

Try these years:

* `2024` should be a leap year
* `2023` should not be
* `1900` should not be, because it's divisible by 100 but not by 400
* `2000` should be, because it's divisible by 400

The 1900 and 2000 pair is the test that matters most. A program that only checks for divisibility by 4 gets 1900 wrong.

### Extensions

* Write the rule as a single `bool` condition, without any `if`, and print the result as `1` or `0` with `%d`. Then rewrite it with `if`, and check that both versions agree on all four years above.
* Print the year as a number and as a word, such as `2024 (leap)`. You'll need an `if` for the word, and a conditional such as `? "yes" : "no"` may help for a `bool`.

---

*This exercise is not from the book. It practices the ideas in Chapter 3.*
