## Homework: Swap with pointers

Swapping two values is a classic use of pointers. In this exercise you'll swap two integers through pointers, so you can see how the pointers connect to the values they refer to.

The program should:

* ask for two integers, `a` and `b`, with the prompts `Enter a: ` and `Enter b: `, and read each one as a whole line
* create a pointer to `a` and a pointer to `b`
* swap the values through the pointers, using a third `int` as temporary storage
* print the values as `a = 8, b = 3`, after the swap

Flush the output after each prompt, with `fflush(stdout)`. Make the swap itself go through the pointers, reading and writing `a` and `b` by way of `*pa` and `*pb`, so that the values really are exchanged through the addresses.

### What to check

Try these inputs, and compare the output with the answers:

* `3` and `8` should print `a = 8, b = 3`
* `5` and `5` should print `a = 5, b = 5`
* `-2` and `7` should print `a = 7, b = -2`

Check the second case as well. A swap of two equal values changes nothing, and that's correct.

### Extensions

* Put the swap in a function that takes two `int` pointers, and call it from `main`, passing the addresses of `a` and `b`. The functions chapter shows how to write and call such a function. Once you've done it, check that the output is the same.
* Add a check that stops the swap when either pointer is `NULL`. Explain why the check has to come before the swap.

---

*This exercise is not from the book. It practices the ideas in Chapter 5.*
