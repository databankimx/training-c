## Walkthrough: Operator menu

The example asks three questions, each printed and flushed, and reads each answer as a line. The operator is the first character of its line, so `line[0]` is the `+` or `/` the user typed. The numbers are read with `strtod`, which reads decimals, since the exercise asks for `double` values.

The `switch` chooses the calculation. Each case ends with `break`, so only one calculation runs. Without the breaks, `'+'` would calculate and print, then fall through into the next case and print again.

The division case is the one that needs an `if`. Dividing a `double` by zero doesn't stop the program, but it produces infinity, so the `if` checks the second number first and prints the message instead. This is the only case where the value of an operand changes what the case does.

The `default` label handles every other character, including `%`, so an operator the program doesn't know gets a message rather than silence.

The output uses `%g`, which prints `5` for 5 and `10` for 10, as the expected answers show. The extension asks you to use `%.2f` instead, which always shows two places after the point.
