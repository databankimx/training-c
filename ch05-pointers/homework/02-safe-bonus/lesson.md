## Homework: Safe bonus

Add a bonus to a score, but only when there's a score to add it to. A pointer that might be `NULL` has to be checked before it's used.

The program should:

* declare `int points = 50;`, and a pointer `score` that holds the address of `points`
* declare a second pointer, `missing`, and set it to `NULL`
* add 10 to the score through `score`, but only when `score` isn't `NULL`, then print `Points: 60`
* when `missing` is `NULL`, print `No score to update.` and change nothing. When it isn't `NULL`, add 5 through it
* print `Points: 60` again, to show that the second bonus changed nothing

The order of the check matters. The pointer must be checked before it's dereferenced, since reading through a null pointer is undefined.

### What to check

Run the program and compare the output with these lines:

```
Points: 60
No score to update.
Points: 60
```

The last line should show 60 again, since the second bonus changed nothing. If it shows 65 or any other value, check the branch for `missing`.

### Extensions

* Put the bonus in a function that takes an `int` pointer and an `int` bonus, and do the `NULL` check inside it. The functions chapter shows how to write and call such a function. Once you've written it, check that the output is the same.
* Add a second score, `int rank = 3;`, with its own pointer, and check that only that score changes when you add a bonus to it.

---

*This exercise is not from the book. It practices the ideas in Chapter 5.*
