## Homework: Greeting card

Write a program that asks for a person's name and age, and then prints a short greeting.

The program should:

* ask for the name first, with the prompt `What is your name? `, and read the whole line with `fgets`
* ask for the age second, with the prompt `How old are you? `, and read it as an `int`
* print a greeting with the name, and a sentence saying how old the person will be next year, like this:

```
Hello, Ada.
Next year you will be 37.
```

Flush the output after both prompts, with `fflush(stdout)`. Give the age variable a name that says what it holds, such as `age`.

### What to check

Try a name with a space in it, such as `Grace Hopper`. The whole name should appear in the greeting. If only `Grace` appears, you've read the name with `scanf("%s", ...)`, which stops at the first space, instead of `fgets`.

Also try an age of `36`, and check that the sentence says `37`.

### Extensions

* Ask for the person's favorite color as well, and add it to the greeting.
* Check that the age is positive before you print the greeting. The lesson hasn't covered `if` yet, so you can leave this for later.

---

*This exercise is not from the book. It practices the ideas in Chapter 2.*
