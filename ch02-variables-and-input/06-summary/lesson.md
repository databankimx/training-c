## Summary: Variables and input

This chapter covered how a program keeps values, and how it gets them from the person using it.

* **A variable is a named place for a value.** You declare it with a type, such as `int`, `double`, `char`, or `bool`, and assign to it afterwards. The type stays the same for the life of the variable.
* **Naming matters.** Names are case sensitive, can't start with a digit, and can't be a keyword. Pick names that say what the value means.
* **`const` protects a value.** A constant can be declared and read, but any attempt to change it is a compile error.
* **`fgets` reads a whole line.** It includes spaces, stops at the Enter key, and can't overflow the array it fills.
* **`strtol` converts text to a number.** It reads whole-number text from the start of the line, and returns 0 for text it can't read, without an error.
* **Mixing the two needs care.** Reading every answer as a line and converting it avoids the leftover newline that `scanf` leaves behind.
* **Command-line arguments arrive before the program starts.** `main(int argc, char *argv[])` receives them, with `argv[0]` holding the program's name and `argv[1]` the first argument. Every argument is text, and `strtol` converts it when you ask.
* **Flush prompts.** `fflush(stdout)` sends the prompt to the screen before the program waits for an answer.
* **Strings are arrays of characters.** They're written in double quotes, and they end with a zero byte. `strlen` gives the length, and positions start at 0.
* **Strings are joined with `snprintf` and `strcat`.** C doesn't allow `+` or `+=` on strings. `snprintf` builds a string from pieces, and `strcat` adds to the end of one.
* **Numeric types differ in precision.** `double` keeps about fifteen significant digits, and `float` about six or seven. `char` holds a small number, its ASCII code, and prints as a letter.
* **Math functions are in `<math.h>`.** `sqrt`, `pow`, `round`, `floor`, and `ceil` work on decimals, and the build links the math library for them. C has no standard `max` or `min`, so a conditional chooses between two values.
* **Arithmetic uses `+`, `-`, `*`, `/`, and `%`.** `%` gives the remainder.
* **Integer division drops the fraction.** When both sides are `int`, `7 / 2` is 3. Use a decimal, such as `2.0`, or a cast such as `(double)a`, to keep the fraction.
* **Precedence decides the order.** Parentheses come first, then `*`, `/`, and `%`, then `+` and `-`. Operators at the same level go from left to right. When in doubt, add parentheses.
* **`++` and `+=` change a variable in place.** `count++` adds one, and `count += 5` adds five.
* **`%.2f` controls decimal output.** It prints a `double` with a fixed number of places after the point.

### Check your understanding

*These questions are written for this course.*

````quiz
Which type should you use to hold a price such as 5.99?
○ int
→ Not quite. int holds whole numbers, so the decimal part would be lost.
◉ double
→ Yes. double holds numbers with a decimal part.
○ char
→ Not quite. char holds one character, not a number.
````

````quiz
What happens if you try to change a `const` variable after it's declared?
○ The new value replaces the old one, with a warning.
→ Not quite. A const variable can't be changed, and the compiler is strict about it.
◉ The build fails with a compile error.
→ Yes. The compiler refuses the assignment, and the program doesn't run.
○ The program runs, but the old value is kept.
→ Not quite. The program doesn't run at all if the build fails.
````

````quiz
Which line reads a whole line of text, including spaces, into `text`?
○ scanf("%s", text)
→ Not quite. %s stops at the first space, so it reads only one word.
◉ fgets(text, sizeof text, stdin)
→ Yes. fgets reads everything up to the Enter key, and stops at the size of the array.
○ printf("%s", text)
→ Not quite. That line writes the text out. It doesn't read anything in.
````
