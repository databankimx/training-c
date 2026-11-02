## User input

So far, every value in our programs was decided before the program ran. That's fine for learning, but most real programs need to ask something of the person using them. C reads input with the standard input functions, the counterpart of `printf` for output. `stdin` is the stream that receives what the user types, and the functions that read from it are `fgets`, `scanf`, and their relatives.

Here's the program for this step. Press **Run**, and type into the input box at the bottom of the Output pane when it asks you to. Press Enter after each answer.

```
Enter some text: I like C
You entered: I like C
Enter a number: 4
You entered: 4
Enter another number: 9
You entered: 9
4 + 9 = 13
```

Your answers will be different, of course. The shape of the output is what matters.

### Reading a whole line

For the first question, the program uses `fgets`:

```c
char text[128];
fgets(text, sizeof text, stdin);
text[strcspn(text, "\n")] = '\0';
```

`fgets` reads everything the user types up to the Enter key, including spaces. That's what you want for a name, a sentence, or anything else where the spaces matter. It stops at the size of the array, so a line that's too long can't overflow it.

`fgets` keeps the newline at the end of the line, so the program removes it. `strcspn` finds the first newline, and the line of code puts the zero byte there, which ends the string before the newline.

### Reading a number

For the numbers, the program reads a line and converts it with `strtol`:

```c
char line[32];
fgets(line, sizeof line, stdin);
int x = (int)strtol(line, NULL, 10);
```

`strtol` reads whole-number text from the start of the line, and returns its value. The `10` says the number is written in decimal. It skips any spaces before the number, and it stops at the first character that isn't part of it.

C also has `scanf`, which reads a number straight into a variable, as in `scanf("%d", &x)`. It works, but it has a catch. `scanf` doesn't read the Enter key, so the newline stays in the input. If you then read a line with `fgets`, that newline is read as an empty line. The program avoids the problem by reading every answer as a whole line, and then converting it. That's the safer habit, and it's why this lesson doesn't use `scanf`.

`strtol` gives a further warning. If the text isn't a number, it returns 0, and it doesn't report an error. The Try section shows what that looks like.

### Why the prompts use flush

Look at the first prompt in the program:

```c
printf("Enter some text: ");
fflush(stdout);
```

The prompt has no newline at the end, so the output could wait in a buffer before it appears. `fflush(stdout)` pushes the text out at once, so the user sees the question before they're asked to answer it. Without it, a program can sit silently with no prompt on the screen, which is confusing.

---

### Quiz

*These questions are written for this course.*

````quiz
Which function reads a whole line of text from the user, including spaces?
○ scanf("%s", text)
→ Not quite. %s stops at the first space, so it would only read one word.
○ printf(text)
→ Not quite. printf writes to the output. It doesn't read anything.
◉ fgets(text, sizeof text, stdin)
→ Yes. fgets reads up to the Enter key, spaces included, and stops at the size of the array.
````

---

### Try it in the runner

At the second prompt, type a word such as `hello` instead of a number. Press **Run** again, and type `hello` at the second prompt.

The program can't turn `hello` into a number, so `strtol` returns 0 for `x`, which is the value you'd get from text it can't read. The program doesn't report an error, and the later lines still run. The sum prints as 0 plus the second number. A real program should check the conversion, and the error handling chapter shows how.

---

Being able to ask the user for something is the first step toward programs that respond to their input. The summary and the homework come next, and they'll put the whole chapter to work.
