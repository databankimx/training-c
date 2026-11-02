## Homework: Word count

Write a program that counts the lines and words in a text file.

The file `data/essay.txt` is already in the step's `data` folder. The program should:

* open `data/essay.txt`, check that it opened, and count its lines with `fgets`
* open the file again, and count its words with `fscanf` and the `%s` format, which reads one whitespace-separated word at a time
* print the two counts, as `Lines: 3` and then `Words: 11`

The file has to be opened twice, since the first pass reads it to the end. Reopening it is simpler than moving back to the start with `fseek`.

### What to check

For the sample file, the output should be:

```
Lines: 3
Words: 11
```

Count the words yourself before you run the program. A word is a run of characters between spaces, so `dog.` counts as one word, and `The` at the start of the last line counts too.

### Extensions

* Count the characters as well, using `fgetc` to read one character at a time. Decide whether the newlines should be counted, and say why.
* Print the number of words on each line, beside the line number. This needs the two counts to be made in the same pass, so think about how you'd split the line into words. The strings chapter's techniques are the place to start.

---

*This exercise is not from the book. It practices the ideas in Chapter 8.*
