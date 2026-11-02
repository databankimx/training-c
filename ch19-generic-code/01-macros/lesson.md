## Macros

A function that returns the larger of two values works the same way for integers and decimals. In C++ a function template writes it once, and the compiler makes a version for each type. C has no templates, so the first option is a macro. A macro is text that the preprocessor substitutes before the compiler runs, so the same definition works for any type that supports `>` and the conditional operator.

Here's the macro for this step, in `src/main.c`:

```c
#define LARGER_OF(a, b) ((a) > (b) ? (a) : (b))
```

The parentheses around each parameter protect the expansion. Without them, `LARGER_OF(x + 1, y)` would expand to a comparison that binds in the wrong order. The outer parentheses keep the whole expansion together when it's used inside a larger expression.

The macro works for any numeric type:

```c
printf("LARGER_OF(3, 7) = %d\n", LARGER_OF(3, 7));
printf("LARGER_OF(2.5, 1.5) = %g\n", LARGER_OF(2.5, 1.5));
```

Press **Run**. The first lines of the output are:

```
LARGER_OF(3, 7) = 7
LARGER_OF(2.5, 1.5) = 2.5
larger_int(3, 7) = 7
```

Nothing in the macro says which type it works on. The preprocessor pastes the text in, and the compiler checks the result at each use, as it would for a template.

### The double evaluation

A macro doesn't evaluate its arguments once and then use the values. It pastes the argument's text into the expansion, and the text can appear twice. Look at this line:

```c
int macro_result = LARGER_OF(next_value(), 5);
```

`next_value` counts its calls and returns a new value each time. The expansion compares `next_value()` with 5, and when the comparison is true, it returns `next_value()` again. The result is 20, and the call count is 2, which the output shows:

```
LARGER_OF(next_value(), 5) = 20 after 2 calls
larger_int(next_value(), 5) = 10 after 1 calls
```

The function version evaluates its argument once, before the call, and the result is 10. The macro's answer is different, and the difference comes from the expansion, not from the values.

### Rules for macros

The double evaluation is the main reason to prefer a function when a value has side effects. Some rules keep a macro safe:

* Use a macro only when a function can't do the job. A function is type-checked, and a macro is not.
* Parenthesize every parameter and the whole expansion, as this macro does.
* Never pass an argument that changes something, such as `i++`, `next_value()`, or a read from a file, unless the macro's text is meant to repeat it.
* Give macros names in capitals, so a reader knows they're expanded by the preprocessor and that their arguments may be repeated.

A function does the same job without these risks. The `larger_int` function in this step is the form to use for ordinary values, and the macro is shown so you can recognize it in older code.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the macro give 20 for `LARGER_OF(next_value(), 5)`, and the function give 10?
○ Because the function is faster and skips a call.
→ Not quite. The function makes one call, and the macro makes two.
◉ Because the macro's expansion names its first argument twice, so the call runs twice.
→ Yes. The expansion calls next_value again, and the second call returns 20.
○ Because the macro cannot accept a function call as an argument.
→ Not quite. A macro accepts any text, including a call, and the problem is that the call repeats.
````

````quiz
Why are the parameters in `#define LARGER_OF(a, b) ((a) > (b) ? (a) : (b))` wrapped in parentheses?
○ Because the preprocessor requires it.
→ Not quite. The preprocessor accepts the definition without them.
◉ So that an argument like `x + 1` stays together when the text is pasted into the expansion.
→ Yes. The parentheses keep each argument's operators from mixing with the surrounding code.
○ So that the macro is evaluated at run time.
→ Not quite. Macros are expanded before compilation, so they never run as code.
````

---

### Try it in the runner

Replace `LARGER_OF(next_value(), 5)` with `LARGER_OF(next_value(), 50)`, and predict the result and the call count before you press **Run**. The first value is 10, which is not more than 50, so the macro takes its second argument, 50, after one call. The output is `50 after 1 calls`. Restore the original call before you continue.

---

A macro reuses text, so it works for any type, and it repeats the argument text in its expansion. The next step gives one function that works for many types, without the repeated evaluation, using pointers and sizes.
