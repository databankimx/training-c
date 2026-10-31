## Summary: Variables and input

This chapter covered the types C provides, the arithmetic they support, how text is stored, and how a program takes values from the user and from the command line.

* **Every variable has a type.** `int` holds whole numbers, `double` holds fractions, and `char` holds one character.
* **Initialize every variable.** A variable declared without a value holds whatever was in memory before.
* **`const` fixes a value.** The compiler reports an error if the program tries to change it.
* **Integer division discards the fraction.** Convert one operand to `double` first when you need one.
* **`%` gives the remainder.** It works only on integers.
* **A string is an array of characters ending in a zero byte.** `strlen` counts the characters, and `sizeof` counts the bytes.
* **Compare strings with `strcmp`, not `==`.** The `==` operator compares addresses.
* **Read input as whole lines.** `fgets` stops at the size of the array, and `strtol` converts the text to a number.
* **Command-line arguments arrive as strings.** `argv[0]` is the program's name, and `argc` counts every word.

### Check your understanding

*These questions are written for this course.*

````quiz
What does `7 % 3` give?
○ 2.33
→ Not quite. % gives the remainder of an integer division, which is a whole number.
◉ 1
→ Yes. 7 divided by 3 is 2 with 1 left over.
○ 2
→ Not quite. That's the quotient, not the remainder.
````

````quiz
What is `sizeof` of the array `char name[] = "Ada";`?
○ 3
→ Not quite. The zero byte at the end of the string takes a place too.
◉ 4
→ Yes. Three letters and the zero byte make four bytes.
○ 1
→ Not quite. sizeof counts every byte in the array, not just one.
````

````quiz
Why does `strtol` on the text "nine" return 0 without stopping the program?
○ Because nine is written as a word, and strtol only reads digits in other languages.
→ Not quite. The reason is in what strtol does when it finds no digits, not in the language.
◉ Because strtol gives 0 for text it can't convert, and doesn't report an error unless the program checks.
→ Yes. Checking the result, or using the end pointer, is the program's job.
○ Because strtol is a function that always returns 0.
→ Not quite. It returns the number it reads, and 0 only when it reads none.
````
