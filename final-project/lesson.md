## Final Project: A Calculator

Build a calculator that reads expressions such as `2 + 3 * (4 - 1)` and prints the result. It's a small program, but it uses most of what this course has covered: variables, functions, loops, structures, error handling with clear messages, recursion, and tests.

The work is in two parts. The **core** is the calculator itself, and you should finish it first. The **bonus items** add exponents, square roots, and more kinds of brackets, and each one builds on the core. The steps are in the `homework` folder of this project, and each step has an example you can reveal when you're stuck.

---

### How the calculator is built

Most calculators work in three stages, and it's worth keeping them separate in your code:

1. **Tokenizer.** Turns the text into tokens: numbers, operators, and brackets. Each token records the column where it starts.
2. **Parser.** Reads the tokens and works out their grouping, following the rules of precedence.
3. **Evaluator.** Works out the value. It can be part of the parser, so long as the rules are still followed.

Wrap these in a small read-eval-print loop (REPL), which keeps asking for expressions until the user types `quit`.

C has no exceptions, so errors are recorded in a structure that the parser checks. The first error is the one reported, and the later steps stop once an error is recorded.

---

### The core (required)

Your calculator must do all of these.

- **Numbers** with an optional decimal part, such as `3`, `2.5`, and `0.75`. Use `double` for values.
- **Operators** `+`, `-`, `*`, and `/`, with the usual precedence. `*` and `/` bind tighter than `+` and `-`, so `2 + 3 * 4` is 14.
- **Left-to-right** order for operators of equal precedence, so `10 - 4 - 3` is 3, and `8 / 4 / 2` is 1.
- **Parentheses** `( )` for grouping, which can be nested.
- **Unary minus**, so `-3 + 5` is 2, and `2 * -3` is -6.
- **Clear errors** for bad input, which name the column where the problem is. See the error messages below.
- **A REPL.** Blank lines are ignored, `quit` exits, and each result is printed on its own line.
- **Tests** that check the examples and the error messages. A `selftest` mode runs them, and CTest runs that mode.

#### The grammar

Your parser should follow this grammar. Each line is one rule, and `*` means "zero or more":

```text
expr    := term (('+' | '-') term)*
term    := factor (('*' | '/') factor)*
factor  := '-' factor | number | '(' expr ')'
```

Each rule calls the rules below it, so precedence falls out of the structure. Writing one function per rule is the usual way to build this, and it's called recursive descent.

#### Error messages

Columns are counted from 1, starting at the first character of the input. The calculator prints an error as `error: ` followed by the message, and your messages must match these forms:

| Input | Message |
|---|---|
| `2 + $` | `unexpected character '$' at column 5` |
| `1 / 0` | `division by zero at column 3` |
| `(2 + 3` | `expected ')', found end of input at column 7` |
| `2 + 3)` | `expected end of input, found ')' at column 6` |
| `2 +` | `expected a number or '(', found end of input at column 4` |
| `1.2.3` | `invalid number '1.2.3' at column 1` |

The column for "end of input" is one past the last character. The column for a division by zero is the column of the `/` operator.

#### Output

A result is printed with up to 15 significant digits. Whole numbers print without a decimal point, so `2 * 7` prints as `14`. That limit also hides small floating-point errors, such as `2.0000000000000004`, which prints as `2`.

---

### Examples to check against

Your program should give these results. Use them as tests.

| Input | Output |
|---|---|
| `2 + 3 * 4` | `14` |
| `(2 + 3) * 4` | `20` |
| `10 - 4 - 3` | `3` |
| `8 / 4 / 2` | `1` |
| `-3 + 5` | `2` |
| `2 * -3` | `-6` |
| `10 / 4` | `2.5` |
| `1.5 * 4` | `6` |

---

### Bonus items

Each bonus builds on the core. Try them in order, since each one uses ideas from the one before.

**Bonus 1: exponents with `^`.** `2^3` is 8. Exponents bind tighter than `*` and `/`, so `2 * 3^2` is 18. They're right-associative, so `2^3^2` is `2^(3^2)`, which is 512, not `(2^3)^2`, which is 64. A minus sign applies after the power, so `-2^2` is -4. The right side of `^` can be a negative number, so `2^-1` is 0.5.

**Bonus 2: square roots with `sqrt(...)`.** `sqrt(16)` is 4, and `sqrt(2) * sqrt(2)` prints as `2`. A square root of a negative number is an error, `sqrt of a negative number at column N`. Any other name followed by brackets is an error, `unknown function 'name' at column N`. A cube root can be written as `8^(1/3)`, which prints as `2`. Decide how you'll handle the rounding, and explain your choice in a comment.

**Bonus 3: square and curly brackets.** `[ ]` and `{ }` group in the same way as `( )`. A closing bracket must match its opening one, so `(2 + 3]` is an error: `expected ')', found ']' at column 7`.

---

### What to submit

- A project that builds, and runs the REPL when it's started with no arguments.
- A `demo` mode: `program demo` runs a fixed list of expressions, prints each one with its result or error, and exits. Include the examples from the table above, and the error cases.
- A `selftest` mode: `program selftest` checks the examples and the error messages, prints `PASS` or `FAIL` for each, and exits with a non-zero code if any check fails.
- A short comment at the top of `main.c` that lists which bonus items you completed.

---

*This project is not from the book. It uses ideas from Chapters 1 to 25.*
