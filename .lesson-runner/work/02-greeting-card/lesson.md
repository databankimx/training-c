## Homework: Greeting card

Write a program that asks who the card is for, reads the name, and prints a birthday greeting with a count of the letters in the name.

The program should:

* ask `Who is the card for? ` and flush the output so the question appears before the program waits
* read the name as a whole line with `fgets`, and remove the newline at its end
* print `Happy birthday, ` followed by the name and an exclamation mark
* print `That's ` followed by the number of letters, then ` letters.`

### What to check

Press **Run**. When the program asks the question, type `Grace` in the input box, and press Enter. The output should be:

```
Happy birthday, Grace!
That's 5 letters.
```

Then run it again with a longer name, such as `Margaret`, and check the count by hand.

### Extensions

* Print an error and return a non-zero value if the name is empty. Decide what counts as empty, since a line with only spaces is also empty to a reader.
* Count the letters only, and skip spaces, so `Ada Lovelace` gives 11 rather than 12. Explain which function you would use to do the counting.

---

*This exercise is not from the book. It practices the ideas in Chapter 2.*
