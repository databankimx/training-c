## Homework: Safe age

Write a program that asks for an age, and keeps asking until it gets a valid one. Invalid input is reported through a return code, and the program recovers from it.

The program should:

* ask for an age with the prompt `Enter your age (0-120): `
* read each answer as a whole line with `fgets`, and convert it with `strtol`
* print `not a number` when the input isn't a number, and ask again
* print `age must be from 0 to 120` when the number is outside that range, and ask again
* when a valid age has been read, print `Age accepted: 42`, with the age that was entered, and end

Use a `while (true)` loop, with `break` once a valid age is read. Flush the output after the prompt, with `fflush(stdout)`.

Put the reading and checking in a function, `read_age`, that returns a code and stores the age through a pointer. Define the codes with `#define` names, as the return-codes step showed.

### What to check

Try these inputs, in this order:

* `abc` should print `not a number` and ask again
* `42abc` should also print `not a number`, since the whole line must be a number
* `200` should print `age must be from 0 to 120` and ask again
* `-1` should print the same range message
* `42` should print `Age accepted: 42`

The second input is the one to think about. `strtol` reads the 42 and stops at the letters, so the check must look at the character where it stopped, not only at whether any digits were read.

### Extensions

* Add a second check for an age that's valid but unlikely, such as above 100, and return a different code for it. Print a different message for that code, and keep asking.
* Replace the `#define` codes with an `enum`, and compare the two versions: which one is easier to read in `main`?

---

*This exercise is not from the book. It practices the ideas in Chapter 9.*
