## Homework: Banner

Print a banner: the text `C is fun` inside a box made of asterisks. The output should be exactly:

```
************
* C is fun *
************
```

Print each line with its own `printf`. The box's top and bottom are twelve asterisks wide, and the middle line has a space and an asterisk on each side of the text.

### What to check

Press **Run**. The output should show the three lines above, followed by `Finished with exit code 0`. Count the asterisks in the top line: there should be twelve, and the middle line should be exactly as wide.

### Extensions

* Change the text to a different phrase. The box must grow to fit it. How many asterisks does the top line need for `Learning C is great`?
* Print the same banner with `printf` calls that take the text as a format argument, such as `printf("* %s *\n", text);`. Explain what `%s` does.

---

*This exercise is not from the book. It practices the ideas in Chapter 1.*
