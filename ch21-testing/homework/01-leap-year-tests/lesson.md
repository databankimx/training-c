## Homework: Leap-year tests

A year is a leap year when it's divisible by 4, except that a year divisible by 100 is not a leap year unless it's also divisible by 400. So 2024 is a leap year, 1900 is not, and 2000 is.

In this exercise, you write the function and the checks that test it. The checks are the part that matters, since they're what would catch a mistake later.

The program should:

* write `is_leap_year(int year)`, following the rule above
* write a `check` function that prints `PASS` or `FAIL` with a name, and counts the failures through a pointer, as the checking-results step did
* run at least four checks: 2024 is a leap year, 1900 is not, 2000 is, and 2023 is not
* print `Failures: ` and the count
* return 0 when every check passes, and 1 otherwise, so CTest can read the result
* register the program with `add_test`, so the Test button runs it

### What to check

The output should be:

```
PASS 2024 is a leap year
PASS 1900 is not a leap year
PASS 2000 is a leap year
PASS 2023 is not a leap year
Failures: 0
```

Then press **Test**. The result should show the test as passed.

### Extensions

* Add a check for a year that's a multiple of 400 and of 100, such as 1600, and one that's a multiple of 4 but not 100, such as 2028. Explain which of the rule's cases each one covers.
* Change the function to get 1900 wrong, and see which checks fail. Explain why the edge cases are the ones that show it.

---

*This exercise is not from the book. It practices the ideas in Chapter 21, with the decisions from Chapter 3.*
