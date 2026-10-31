## Arithmetic

C has the four basic operators, `+`, `-`, `*`, and `/`, and one more, `%`, which gives the remainder of a division. The program in `src/main.c` applies each one to two `int` values, and then divides again with a `double`:

```c
printf("a + b = %d\n", a + b);
printf("a / b = %d\n", a / b);
printf("a %% b = %d\n", a % b);
printf("a / b as double = %.2f\n", (double)a / b);
```

Press **Run**. The output is:

```
a + b = 9
a - b = 5
a * b = 14
a / b = 3
a % b = 1
a / b as double = 3.50
```

### Integer division

When both operands are `int`, `/` throws away the fraction. 7 divided by 2 is 3, not 3.5. The fraction is discarded rather than rounded, so `-7 / 2` is -3. This surprises most people the first time, and it's behind many wrong answers in real programs.

`%` gives the remainder that integer division leaves behind. 7 divided by 2 leaves 1, so `7 % 2` is 1. It's useful for checking whether a number is even (`n % 2 == 0`) and for wrapping a value around a fixed range.

`%` only works on integers. `7.5 % 2` is an error, and the compiler reports it.

### Converting with a cast

To get a fractional answer from two `int` values, one operand has to be a `double` before the division happens. `(double)a / b` does that: the cast `(double)` turns `a` into a `double`, and the division is then done on `double` values, giving 3.5. Casting only the result does not help, since the division has already thrown away the fraction by then.

### Precedence and parentheses

`*` and `/` bind more tightly than `+` and `-`, as they do in arithmetic. `2 + 3 * 4` is 14. Parentheses change the order, so `(2 + 3) * 4` is 20. When in doubt, use parentheses, since they make the intent clear to the next reader too.

---

### Quiz

*These questions are written for this course.*

````quiz
What is the value of 7 / 2 when both operands are int?
○ 3.5
→ Not quite. Integer division doesn't keep the fraction, so the result is an int.
◉ 3
→ Yes. Integer division discards the fraction.
○ 4
→ Not quite. Integer division rounds toward zero, which gives 3 here.
````

---

### Try it in the runner

Change `a` to 9 and `b` to 4, and predict each line before you press **Run**. The remainder line is `a % b = 1`, since 9 divided by 4 leaves 1. The double division line is `2.25`.

---

Arithmetic in C depends on the types of its operands, and integer division is the first place that matters. The next step is strings, which are arrays of characters.
