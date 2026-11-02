## Walkthrough: Unit converter

The example reads one line of input and converts it with `strtod`, which reads a decimal number from the start of the text. Reading a decimal rather than a whole number is what the exercise asks for, since a temperature such as 36.6 has a fraction.

The formula is written `celsius * 9.0 / 5.0 + 32.0`. The constants have a decimal point, so the arithmetic is done on `double` values. If they were written `9 / 5`, the division would be whole-number division and give 1, not 1.8, which is the mistake the arithmetic chapter warned about.

The result is stored in a `const double`, because it's calculated once and never changes. The output line uses `%g`, which prints a number compactly. That's why 212 prints as `212` and not `212.0`, and why `-40` prints as `-40`. The extension asks you to switch to `%.1f`, which always shows one digit after the point.

`strtod` returns 0 for text it can't read, the same way `strtol` does, so a typo such as `abc` prints `0 C is 32 F` without any error. The error handling chapter shows how to check for that.
