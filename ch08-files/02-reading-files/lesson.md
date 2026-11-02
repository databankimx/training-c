## Reading files

Reading a file mirrors writing one. You open the file with `fopen` in read mode, `"r"`, and read from it with functions such as `fgets`, which reads a line, much as you read from the keyboard. The main difference is that a file has an end, and the loop that reads it has to notice when it reaches that end.

Here's the program for this step, in `src/main.c`:

```c
FILE *in = fopen("data/notes.txt", "r");
if (in == NULL) {
    printf("Could not open data/notes.txt\n");
    return 1;
}

char line[256];
int count = 0;
while (fgets(line, sizeof line, in) != NULL) {
    /* strip the newline, then count and print the line */
}
```

Press **Run**. The output is:

```
1: First note: buy bread.
2: Second note: call the dentist.
3: Third note: finish the report.
Lines read: 3
```

The file has three lines, and the loop reads each one into `line`. `fgets` reads up to the end of a line, or until its buffer is full. It returns `NULL` when there's no line left to read, and the loop stops. That's the same pattern as the `while` loops from the loops chapter: the loop runs while the condition is true, and the condition here is "a line was read".

### The newline

`fgets` keeps the newline at the end of each line, so the program removes it before printing. The code finds the last character with `strlen`, and if it's `\n`, replaces it with the zero byte that ends the string. The user-input step used the same idea.

The buffer is 256 characters. A line longer than that comes back in pieces, with the rest read on the next call to `fgets`. For these notes, every line fits, and the loop prints each one whole.

### Why the check matters

The `if (in == NULL)` test works just as the write-side check did. A missing file, or one you aren't allowed to read, makes `fopen` return `NULL`. Reading from a `NULL` pointer is undefined behavior, and the program may crash. Without the check, the program would print `Lines read: 0` if it didn't crash, which looks like an empty file rather than a missing one.

### Reading words instead of lines

`fgets` reads whole lines. To read a file one whitespace-separated word at a time, use `fscanf` with a `%s` format, which is the file version of the `scanf` you saw in the user-input step:

```c
char word[256];
while (fscanf(in, "%255s", word) == 1) {
    /* word holds one word at a time */
}
```

`fscanf` skips spaces and newlines, reads one word, and returns the number of items it read. It returns 1 while a word is found, and something else at the end of the file, so the loop stops there. The `255` in the format limits the word to 255 characters, which protects `word` from overflow, just as the buffer size did for `fgets`. Use `fgets` when the line structure matters, and `fscanf` when it doesn't.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `fgets` return when the file has no more lines?
○ An empty string.
→ Not quite. It returns a value that tells the loop there's nothing left to read.
◉ NULL, so the while loop stops.
→ Yes. fgets returns NULL when it reaches the end of the file, which ends the loop.
○ A newline character.
→ Not quite. There's nothing left to return, so the answer is NULL.
````

````quiz
Why does the program check `if (in == NULL)` before reading?
○ Because reading from a file always fails the first time.
→ Not quite. Reading works when the file opens.
◉ Because a file that didn't open can't be read, and reading through the NULL pointer is undefined behavior.
→ Yes. The check reports the missing file before the program tries to read it.
○ Because the check moves the reading position to the start.
→ Not quite. Checking the pointer doesn't move anything in the file.
````

---

### Try it in the runner

Change the file name to `data/missing.txt`, and press **Run**. The program reports that it couldn't open the file, and stops. Change the name back before you continue.

Then replace the `fgets` loop with the `fscanf` word loop from the lesson, counting words instead of lines. Predict the count for the three notes before you run it. The notes contain 4, 5, and 5 words, so the total is 14. Each word is counted with its punctuation attached, so `note:` is one word.

---

Reading and writing use the same file ideas in opposite directions. The next step puts them together with a problem that catches many programmers out: what happens when a file is written over, and the new text is shorter than the old.
