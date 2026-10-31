## User input

A program that only prints is a one-way conversation. Real programs ask the user for values and use what comes back. In C, the standard input functions read from the keyboard, and the program in `src/main.c` asks for a name and an age, then uses both.

Press **Run**. When the program asks for your name, type a name in the input box under the Output pane, and press Enter. Then type an age the same way. For example, enter `Ada`, then `36`. The output is:

```
What is your name? Ada
How old are you? 36
Hello, Ada. In ten years you will be 46.
```

The runner shows the text you typed in the Output pane, and the program's own lines follow. The first question is on the same line as its answer, since you typed it there.

### Reading a line with fgets

`fgets` reads one line, including the newline at its end, into an array:

```c
char name[64];
fgets(name, sizeof name, stdin);
name[strcspn(name, "\n")] = '\0';
```

It stops at the size of the array, so a long line can't overflow it. The second line of code removes the newline: `strcspn` finds the first newline, and that position becomes the zero byte that ends the string.

`fgets` returns `NULL` when there's nothing more to read, such as when the input is closed. The `if` checks for that, and the program stops rather than using an array that was never filled.

### Converting text to a number

The age arrives as text, such as `"36\n"`. `strtol` converts the text to a `long`, starting at the beginning of the line. The last argument, `10`, is the base, which is decimal. If the text isn't a number, `strtol` returns 0 rather than reporting an error, so the program would treat `thirty` as age 0. Checking the result properly takes one more step, which the chapter on error handling covers.

### Why flush before a prompt

Output sent to a pipe is buffered, which means the text is held back until a newline or until the buffer fills. The runner talks to your program through a pipe, so the prompt `What is your name? ` could stay hidden while the program waits for input. `fflush(stdout)` sends the prompt out right away, so you can see it before you type.

### Scanf is a trap

`scanf("%d", &age)` also reads input, but it leaves the newline behind in the input. The next read then sees that newline and takes it as an empty line. Many C programs go wrong because of this, and the safer habit is to read whole lines with `fgets` and convert them, as this program does.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the program call fflush(stdout) before each prompt?
○ To clear the screen.
→ Not quite. fflush sends buffered output out. It doesn't clear anything.
◉ So the prompt appears before the program waits for input.
→ Yes. Output to a pipe is buffered, so the prompt could stay hidden until after the input.
○ To make the program faster.
→ Not quite. Flushing usually slows output slightly, and it's done here for correctness.
````

---

### Try it in the runner

Enter `Ada` as the name, then `10` as the age, and predict the last line before you press **Run**. It's `Hello, Ada. In ten years you will be 20.`, since the age is 10 and the program adds ten.

---

Reading whole lines and converting them is the safe way to take input in C. The next step is command-line arguments, which give a program its values before it starts.
