## Homework: Vowel tests

Write a function that counts the vowels in a word, and a set of checks that test it. Only the lowercase vowels a, e, i, o, and u count in this exercise.

The program should:

* write `count_vowels(const char *word)`, which counts the characters that are a, e, i, o, or u
* write a `check` function that prints `PASS` or `FAIL` with a name, and counts the failures through a pointer
* run at least four checks, using these cases: "hello" has 2 vowels, "" has 0, "rhythm" has 0, and "education" has 5
* print `Failures: ` and the count
* return 0 when every check passes, and 1 otherwise
* register the program with `add_test`, so the Test button runs it

### What to check

The output should be:

```
PASS hello has 2 vowels
PASS an empty word has no vowels
PASS rhythm has no vowels
PASS education has 5 vowels
Failures: 0
```

Then press **Test** to run the checks through CTest.

### Extensions

* Add a check that uses an uppercase vowel, such as "HELLO". Decide what the answer should be, and whether the function is right to give it, before you run the check.
* Write one more check of your own for a word you choose. Work out its vowel count by hand first, and explain why that matters.

---

*This exercise is not from the book. It practices the ideas in Chapter 21, with the strings from Chapter 2.*
