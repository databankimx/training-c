## Homework: Numbered copy

Write a program that reads a text file, and writes a copy of it with each line numbered.

The file `data/input.txt` is already in the step's `data` folder. The program should:

* open `data/input.txt` for reading, and check that it opened
* open `data/numbered.txt` for writing, and check that it opened
* read each line with `fgets`, and write it to the new file with its number and a full stop before it, such as `1. apples`
* print `Wrote 3 lines to data/numbered.txt` when it's done, with the correct count

Close both files before the program finishes. Remove the newline that `fgets` keeps, so the numbered lines don't have a blank line between them.

### What to check

Press **Run**. The View button should appear over the Output pane, and opening it should show:

```
1. apples
2. bananas
3. cherries
```

The count in the last line should match the number of lines in the input. If the numbers are off by one, check where the counter increases in the loop.

### Extensions

* Skip empty lines in the input, but still count only the lines that are written. Think about where the check goes, so that an empty line isn't numbered.
* Print a message and return early when either file fails to open. Test it by changing the input file's name to one that doesn't exist.

---

*This exercise is not from the book. It practices the ideas in Chapter 8.*
