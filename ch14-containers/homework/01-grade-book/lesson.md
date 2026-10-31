## Homework: Grade book

Write a program that keeps a list of scores in a vector, and reports the count, the highest, the lowest, and the average.

The program should:

* create an `IntVector` holding the scores 72, 88, 95, and 60, using `int_vector_push` for each one
* print `Count: 4`
* use a loop to find the highest score, and print `Highest: 95`
* use a loop to find the lowest score, and print `Lowest: 60`
* use a loop to add the scores, and print the average with two decimal places, as `Average: 78.75`

Use `%.2f` for the average. The loops should use an index, since C has no range-based `for`, and the loop bound should come from `scores.size`.

### What to check

The output should be:

```
Count: 4
Highest: 95
Lowest: 60
Average: 78.75
```

The average is the total, 315, divided by the count. Dividing two integers would drop the fraction, so convert the total to a `double` before dividing.

### Extensions

* Add a fifth score, and check that every line updates. Does the program need any other change?
* Print the scores above the average, one per line. Think about whether you need the average before the loop that prints them.

---

*This exercise is not from the book. It practices the ideas in Chapter 14.*
