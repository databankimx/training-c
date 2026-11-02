## Walkthrough: Temperature utilities

The header declares both functions, and the source file defines them. `main.c` includes the header, so the compiler knows the parameter and return types when it compiles each call. Without the include, the call `celsius_to_fahrenheit(0.0)` would be an implicit declaration, and recent gcc versions refuse to build it, as the headers step of the first chapters showed.

The formula for Celsius to Fahrenheit is `celsius * 9.0 / 5.0 + 32.0`. The reverse is `(fahrenheit - 32.0) * 5.0 / 9.0`, and the subtraction comes first, which is why the parentheses are there.

The -40 line works because -40 times 9 over 5 is -72, plus 32 gives -40. The reverse conversion of -40 gives -40 too, so both formulas agree at that point.

For the extension about Kelvin, the declaration goes in the header, the definition goes in the source file, and the call goes in `main.c`, following the same pattern as the other two functions.
