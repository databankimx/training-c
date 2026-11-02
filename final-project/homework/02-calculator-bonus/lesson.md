## Bonus items

Add these to the core calculator. Try them in order, since each one uses the one before it. The requirements are in the project overview, and the error messages must match the forms given there.

**Exponents with `^`.** Add `^` as a token and a rule for it between the factor and the primary value. `2^3` is 8, and `2 * 3^2` is 18, since exponents bind tighter than `*` and `/`. The exponent is right-associative, so `2^3^2` is 512. A minus sign applies after the power, so `-2^2` is -4, and the exponent can be negative, so `2^-1` is 0.5.

**Square roots with `sqrt(...)`.** Add names to the tokenizer, and a rule that reads a name followed by a bracketed argument. `sqrt(16)` is 4, and `sqrt(2) * sqrt(2)` prints as 2. A negative argument is an error, `sqrt of a negative number at column N`, and any other name is an error, `unknown function 'name' at column N`. A cube root can be written as `8^(1/3)`, which prints as 2. Decide how your program handles the rounding, and explain your choice in a comment.

**Square and curly brackets.** Allow `[ ]` and `{ }` to group in the same way as `( )`. A closing bracket must match its opening one, so `(2 + 3]` is an error, `expected ')', found ']' at column 7`. Put the matching check in one place, so every kind of bracket uses it.

### What to check

Press **Test** in the runner. When the bonus items are correct, the output ends with:

```
Failures: 0
```

The checks include the bonus examples, and the error messages for each one.

### Hints

- Exponents need a rule of their own, because `^` binds tighter than `*`. Put it between the rules for the factor and the primary value, and make the right side a factor, not a primary value.
- The `sqrt` rule has to see the name, then the bracket, then the argument. Check the name before anything else, so an unknown function is reported at its own column.
- Negative values can reach `sqrt` through a minus sign, so check the argument's sign inside the function, not in the tokenizer.
- C has no exceptions, so each new error is recorded in the `Calc` structure, the same way as in the core.

### Extensions

- Add a `cbrt(...)` function for cube roots, and decide whether it accepts negative values.
- Add a `%` operator that gives the remainder, and decide where it fits in the precedence rules.

---

*The example is in `src/main.c`. It's the complete calculator, with the core and all three bonus items.*
