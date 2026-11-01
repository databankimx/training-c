## Homework: Safe division

Division by zero has no answer, so a function that divides should say so, rather than crash or return a magic value. In this exercise, you write a division that returns a result which may be missing, and print each result, handling the empty case.

The program should:

* write `safe_divide(int a, int b)`, which returns a `MaybeQuotient` structure. Its `found` flag is true with the quotient when `b` isn't zero, and false when it is
* write `print_division`, which calls `safe_divide`, checks `found` before using the quotient, and prints `<a> / <b> = <quotient>`
* when `found` is false, print `<a> / <b> = no answer` instead, without reading the quotient
* in `main`, print the division of 10 by 2, then 1 by 0, then 9 by 3

### What to check

The output should be:

```
10 / 2 = 5
1 / 0 = no answer
9 / 3 = 3
```

The check on `found` comes before any use of the quotient. A division by zero would otherwise happen inside the caller, so the structure keeps the division itself safe.

### Extensions

* Change the empty case to print a fallback quotient of -1 instead of the words "no answer". Explain why that version is less clear for a reader, and why the flag still matters even when a fallback is printed.
* Write the same function with an error code returned from the function, and a result passed back through a pointer, instead of the structure. Explain which version a caller would find easier to get right.

---

*This exercise is not from the book. It practices the ideas in Chapter 25, with the structures from Chapter 10 and the error codes from Chapter 9.*
