## Homework: A banner

Write a program that prints a box around a greeting, like this:

```
**********
* Hello! *
**********
```

The box has three lines. The top and bottom lines are the same length as the middle line, and the middle line has the greeting with a space on each side, inside the stars.

Use one `printf` for each line. Don't print the box with a single long string, because the point of the exercise is to see how the lines fit together.

### What to check

Count the characters on each line. All three should be the same length. If the top line is longer or shorter than the middle line, the box won't look like a box.

### Extensions

* Change the greeting to something longer, and work out how many stars the top and bottom lines need. Can you write the program so the stars come from a count, rather than being typed out? Loops are the tool for that, and the loops chapter covers them.
* Print the same box with `fflush(stdout);` after each line. The output shouldn't change.

---

*This exercise is not from the book. It practices the ideas in Chapter 1.*
