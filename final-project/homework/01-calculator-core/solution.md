## Core calculator: walkthrough of the example

The program has three stages, kept apart the way the project overview asks. `tokenize` turns the text into an array of tokens, and each token records its column. The END token is placed one column past the input, so the "end of input" messages get the right column. `parse_expr`, `parse_term`, and `parse_factor` are the three grammar rules, and each one calls the rule below it. Precedence follows from that structure: `parse_term` handles `*` and `/` before `parse_expr` sees a `+`.

Errors work differently from the C++ version. C has no exceptions, so each error is recorded in the `Calc` structure, with its message and column. The first error sets `failed`, and every rule returns at once when `failed` is set. That keeps the first message, which is the one the user needs, and it stops the parser without any jump.

The values are printed with `%.15g`. That matches the C++ default of 15 significant digits: whole numbers print without a point, and a value like 2.0000000000000004 prints as 2.

The left-to-right order for `-` and `/` comes from the loops in `parse_expr` and `parse_term`. Each loop reads one operator and one operand at a time, and combines them in order, so `10 - 4 - 3` is `(10 - 4) - 3`, which is 3.

The unary minus is handled by `parse_factor`, which calls itself after reading a `-`. That's why `2 * -3` works: the right operand of `*` is a factor, and a factor can start with a minus.
