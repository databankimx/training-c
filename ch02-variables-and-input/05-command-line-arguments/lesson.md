## Command-line arguments

A program can also receive values when it starts, from the words typed after its name. These are command-line arguments. The runner's argument box sends whatever you type there to the program in exactly this way, so you can try them in the runner.

The program in `src/main.c` takes two numbers, adds them, and lists every argument it received.

```c
int main(int argc, char *argv[]) {
    printf("Arguments received: %d\n", argc - 1);
    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    // ...
}
```

Type `4 9` in the argument box, and press Run. The output is:

```
Arguments received: 2
Argument 1: 4
Argument 2: 9
4 + 9 = 13
```

With no arguments, the output is `Arguments received: 0`, followed by the line asking for two numbers.

### argc and argv

`main` takes two parameters for the arguments. `argc` is the number of words on the command line, and `argv` is an array of those words, each one a string. The count includes the program's own name, so `argv[0]` is the name and the first real argument is `argv[1]`. That's why the loop starts at 1.

`char *argv[]` is an array of strings, which is the same as the array-of-pointers idea from the pointers chapter. Each element points at the text of one argument.

### Arguments are text

Every argument is a string, even when it looks like a number. `strtol` converts the text to a number, and the base, 10, says the number is written in decimal. The conversion happens only when the program asks for it, so the program decides how to treat each argument.

### Bad input is not reported

Here is the trap. `strtol` returns 0 for text that isn't a number, and it doesn't stop the program. With `4 nine`, the second number becomes 0, and the program prints `4 + 0 = 4` with no error. That's the behavior you'll see in the Try section, and it's why a program that takes numbers from the command line should check them. The chapter on error handling shows how.

### Arguments and the runner

The runner's argument box splits what you type at each space, and sends each word as a separate argument. That's why `4 9` gives two arguments, and why a program that needs the whole line of text has to join the words back together.

---

### Quiz

*These questions are written for this course.*

````quiz
Which argument position holds the first real argument the user typed?
○ argv[0]
→ Not quite. argv[0] holds the program's own name.
◉ argv[1]
→ Yes. The first real argument follows the program's name, so it's at position 1.
○ argc
→ Not quite. argc is a count of the words, not one of them.
````

````quiz
For the command `program 4 9`, what is argc?
○ 2
→ Not quite. argc also counts the program's own name.
◉ 3
→ Yes. The program's name, 4, and 9 make three words.
○ 4
→ Not quite. Only the program's name and the two numbers are counted.
````

````quiz
Why does the loop in this program start at 1, not 0?
○ Because argv[0] is an empty string.
→ Not quite. argv[0] holds the program's name, which isn't empty.
◉ Because argv[0] is the program's own name, and the first argument the user typed is argv[1].
→ Yes. Starting at 1 skips the program's name.
○ Because argc is always 0.
→ Not quite. argc counts the words, and is 0 only when nothing was typed.
````

---

### Try it in the runner

Run the program with the arguments `4 nine`, and predict the last line before you press **Run**. It's `4 + 0 = 4`: `strtol` can't read `nine`, returns 0, and the program carries on without complaint.

Then run with no arguments at all, and predict the second line of the output.

---

Command-line arguments let a program take its values before it starts, which suits programs that run unattended, or are used from a script. The summary comes next, and it covers the whole chapter.
