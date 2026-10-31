## Walkthrough: Area functions

The two functions take `double` parameters and return `double` results. Each one does one calculation, and `main` only reads the inputs, calls the functions, and prints the results. Because both functions are defined above `main`, the calls compile without any declarations.

The circle's pi is a local `const double` inside `circle_area`. A named constant says what the number means, so a reader doesn't have to know that 3.14159 is pi. Changing the precision later means changing one line.

With the inputs in the first check, the rectangle gives 3 × 4 = 12, printed as `12.00`. The circle gives 3.14159 × 2 × 2 = 12.56636, which rounds to `12.57`. The `%.2f` in the output does that rounding.

The zero case works because both functions multiply, and multiplying by zero gives zero. That's a check of the arithmetic, not a special case in the code.

The extension about a triangle follows the same pattern: a function with two `double` parameters that returns half their product. The formula is `base * height / 2`, and writing it with `0.5` or `2.0` keeps the division in decimals.
