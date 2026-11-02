## Homework: Guarded section

A guard is a small value whose leave function undoes something when a section ends. In C there are no destructors, so the leave call has to be on every route out of the function. In this exercise, you'll write a guard and check that its leave runs when the work fails early.

The program should:

* define a `Guard` structure with a name, and a `guard_enter` function that stores the name and prints `Enter <name>`
* define a `guard_leave` function that prints `Leave <name>`
* define `process(int fail)`, which enters a guard named `section`, prints `Working`, and returns -1 without finishing when `fail` is nonzero. When `fail` is zero, it prints `Finished working` and returns 0. Both routes must reach the leave call through a cleanup label
* in `main`, call `process(0)`, then `process(1)`, and print `Caught: work failed` when the second call returns a failure
* print `End` at the end of `main`

### What to check

The output should be:

```
Enter section
Working
Finished working
Leave section
Enter section
Working
Leave section
Caught: work failed
End
```

The line `Leave section` in the second call comes before `Caught`. That's the point of the exercise: the guard is left inside `process`, before the caller sees the failure and reports it.

### Extensions

* Add a second guard named `inner` inside `process`, and predict the order of the two `Leave` messages when `fail` is 1. Check your prediction. Then think about where the labels must go so that the inner guard is left first.
* Remove the check on the return value in `main`, and describe what the program prints. Note whether the leave still runs before the program continues.

---

*This exercise is not from the book. It practices the ideas in Chapter 17, with the cleanup blocks from Chapter 9.*
