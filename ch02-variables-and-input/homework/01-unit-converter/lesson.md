## Homework: Unit converter

Write a program that converts three temperatures from Celsius to Fahrenheit. The formula is F = C × 9 / 5 + 32, and the output should be exactly:

```
100.0 C is 212.0 F
25.0 C is 77.0 F
0.0 C is 32.0 F
```

Use a `double` variable for each temperature and each result. Print each line with `printf`, and format the numbers with one digit after the point.

### What to check

Press **Run**. The Output pane should show the three lines above, followed by `Finished with exit code 0`. Then change one temperature, such as 37, and check the result by hand before you run the program again.

### Extensions

* Store each result in an `int` instead of a `double`, and describe what happens to 37 Celsius, which is 98.6 Fahrenheit. Explain why the fraction is lost.
* Make the program convert a temperature in Fahrenheit back to Celsius, with a second `printf` that shows the working.

---

*This exercise is not from the book. It practices the ideas in Chapter 2.*
