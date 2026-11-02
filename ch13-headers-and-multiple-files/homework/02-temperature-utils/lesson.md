## Homework: Temperature utilities

Write a small utility module: two conversion functions declared in a header, defined in a source file, and used from `main`.

The program should:

* in `temperature.h`, declare two functions, `celsius_to_fahrenheit` and `fahrenheit_to_celsius`, each taking a `double` and returning a `double`, with include guards
* in `temperature.c`, define them, using `F = C * 9 / 5 + 32` and its reverse
* in `main.c`, include `temperature.h`, and print five conversions with two decimal places, in the form `100.00 C is 212.00 F`

The five lines are: 0 C, 100 C, and -40 C converted to Fahrenheit, and 212 F and 32 F converted to Celsius. Use `%.2f` for every number printed.

### What to check

The output should be:

```
0.00 C is 32.00 F
100.00 C is 212.00 F
-40.00 C is -40.00 F
212.00 F is 100.00 C
32.00 F is 0.00 C
```

The `-40` line is a useful check: the two scales meet there, so both values are the same. If a line is off, check which of the two formulas it used.

### Extensions

* Add a third function, `kelvin_from_celsius`, that adds 273.15. Decide which of the three files should hold each part of it.
* Remove the include of `temperature.h` from `main.c`, and read the compiler's error. Explain why the header is needed even though the definitions are in another file.

---

*This exercise is not from the book. It practices the ideas in Chapter 13.*
