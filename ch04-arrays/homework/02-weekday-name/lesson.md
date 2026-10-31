## Homework: Weekday name

Write a program that looks up the name of a day, given its number from 1 to 7, where 1 is Monday.

The program should:

* declare an array of seven names holding the day names, from `Monday` to `Sunday`
* ask for a number, with the prompt `Enter a day number (1-7): `, and read it as an `int`
* print the name for that day, such as `Day 3 is Wednesday`
* print `That isn't a valid day number.` if the number is outside 1 to 7, and not print a name

Remember that indexes start at zero, so day 1 is at index 0. Subtract 1 from the number before you use it as an index, and make sure the index is always valid before you read the array.

Flush the output after the prompt, with `fflush(stdout)`.

### What to check

Try these inputs:

* `1` should give `Monday`
* `7` should give `Sunday`
* `0` should give the invalid message, not a name
* `8` should give the invalid message

The last two are the cases that matter. Reading `days[-1]` or `days[7]` is undefined, and the program might print garbage or crash, which is exactly the kind of bug the arrays lesson warned about.

### Extensions

* Print the number of days in the array with `sizeof`, rather than typing 7 into your check. Does the check still work if you add an eighth name? Think about what changes in the array's declaration as well.
* Print the name of the next day as well, wrapping from Sunday back to Monday. The `%` operator from the arithmetic lesson makes the wrap a single calculation.

---

*This exercise is not from the book. It practices the ideas in Chapter 4.*
