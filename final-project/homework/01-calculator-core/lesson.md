## Core calculator

Build the core of the calculator, as described in the project overview. The core is everything except the bonus items: numbers with decimals, the four operators with precedence, left-to-right order, parentheses, unary minus, clear error messages with columns, and the REPL.

Start by writing the tokenizer, and test it on `2 + 3`. Then write the parser, one function per grammar rule, and check that `2 + 3 * 4` gives 14. Then add the error messages, one at a time, and check each against the table in the overview.

### What to build

Your `src/main.c` should do these things:

- **Read an expression**, either from the arguments, such as `program 2 + 3`, or from the REPL when no arguments are given.
- **Print the result** with up to 15 significant digits, so whole numbers have no decimal point.
- **Print errors** as `error: ` followed by the message from the table in the overview.
- **Run `selftest`** when the first argument is `selftest`. It checks the eight examples and the six error messages, prints a `PASS` or `FAIL` line for each, and exits with 0 when every check passes.
- **Run `demo`** when the first argument is `demo`. It prints each expression from the examples and the error cases, with its result or error, and exits.

### What to check

Press **Test** in the runner. When the core is correct, the output ends with:

```
Failures: 0
```

Then try the REPL: press **Run** with no arguments, type `2 + 3 * 4` in the input box, and press Enter. It should print `14`. Type `quit` to end the REPL.

### Hints

- Write one function for each grammar rule. A function for `term` calls `factor`, and `factor` calls `term` when it sees a parenthesis, which is the recursion.
- Keep the position in the token array in one place, such as the `Calc` structure, so each rule moves past exactly what it reads.
- C has no exceptions, so an error is recorded in the `Calc` structure, and every rule checks `failed` before it continues. The first error is the one reported.
- The column for the end of input is one past the last character. Store it on the END token when you tokenize, so the parser can report it.
- Check for division by zero where you divide, and report the column of the `/` operator.

### Extensions

- Add a `%` operator that works like `/`, and decide what precedence it has. Explain your choice.
- Print a usage line when the REPL starts, listing the operators.

---

*The example is in `src/main.c`. Reveal it when you're stuck, and compare your design with it afterward.*
