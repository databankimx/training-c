## Bonus items: walkthrough of the example

The bonus grammar changes three rules, and the core's structure stays as it was:

```text
expr    := term (('+' | '-') term)*
term    := factor (('*' | '/') factor)*
factor  := '-' factor | power
power   := primary ('^' factor)?
primary := number | '(' expr ')' | '[' expr ']' | '{' expr '}' | 'sqrt' '(' expr ')'
```

### Exponents

`^` binds tighter than `*` and `/`, so `2 * 3^2` is `2 * (3^2)`, which is 18. That's why `power` sits below `term` and above `factor`.

The right side of `^` is a `factor`, not a `primary`. That choice gives three of the lesson's results. `2^3^2` is right-associative, since the right side of the first `^` is another power: `2^(3^2)`, which is 512. `2^-1` works, since a `factor` can start with a minus: `2^(-1)`, which is 0.5. `-2^2` is `-(2^2)`, which is -4, since the minus is handled by `factor` before the power is reached.

### Square roots and unknown names

In `parse_primary`, a name token is read first. `sqrt` followed by a bracket is a function call, and any other name is an error:

```c
if (strcmp(token.text, "sqrt") != 0 || peek(c).kind != TOK_LEFT_PAREN) {
    fail(c, token.column, "unknown function '%s'", token.text);
    return 0.0;
}
```

The argument is parsed first. A negative value gives `sqrt of a negative number at column N`, with the column of `sqrt`. The library's `sqrt` is called only on a value that is zero or more.

`sqrt(2) * sqrt(2)` gives 2.0000000000000004 internally, and the 15-digit output prints it as `2`. The cube root `8^(1/3)` is written as a power, and the same rounding makes it print as `2`. The rounding decision is the output format: 15 significant digits hide the small error that floating-point arithmetic leaves, and a comment in the code should say so.

### Square and curly brackets

`[` and `{` are handled in the same branch of `parse_primary` as `(`. The branch remembers which bracket was opened, and then checks for the matching closer:

```c
if (token.kind == TOK_LEFT_PAREN) {
    expect_close(c, TOK_RIGHT_PAREN, ")");
} else if (token.kind == TOK_LEFT_SQUARE) {
    expect_close(c, TOK_RIGHT_SQUARE, "]");
} else {
    expect_close(c, TOK_RIGHT_CURLY, "}");
}
```

`expect_close` is the one place where the check happens, so every kind of bracket uses it. A closer that doesn't match is reported with the closer it expected: `(2 + 3]` gives `expected ')', found ']' at column 7`.

### The math library

`^` calls `pow`, and `sqrt` comes from `<math.h>`. The CMake file links the math library with `target_link_libraries(program PRIVATE m)`. Without that link, the build fails with an undefined reference to `pow` or `sqrt`.

### Selftest

The bonus `selftest` runs the core checks and the bonus checks together. The bonus checks cover exponents, right-associativity, the minus in `-2^2`, a negative exponent, both square roots, the cube root, both kinds of bracket, the mismatched bracket, a negative square root, and an unknown function.
