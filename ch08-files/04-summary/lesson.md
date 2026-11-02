## Summary: Files

This chapter covered reading and writing files with the standard file functions.

* **`<stdio.h>` provides the file functions.** `fopen` opens a file and returns a `FILE *`, `fprintf` and `fgets` work on it, and `fclose` closes it.
* **File functions work like `printf` and `fgets` on the keyboard.** `fprintf` writes to a file the way `printf` writes to the screen, and `fgets` reads a line the way it reads from the keyboard.
* **Always check that a file opened.** `fopen` returns `NULL` on failure, and reading or writing through `NULL` is undefined behavior.
* **A read loop stops at the end of the file.** `while (fgets(line, sizeof line, in) != NULL)` runs while lines remain.
* **Remove the newline by hand.** `fgets` keeps it, so the program replaces it with the zero byte when it isn't wanted.
* **Closing flushes and releases the file.** `fclose` writes out any buffered text, and it frees the file for other programs.
* **`"r+"` keeps existing contents.** Writing a shorter text over a longer file leaves the leftover text behind. Use `"w"` or `"w+"` to replace the whole file.
* **The mode decides what happens to the file.** `"r"`, `"w"`, `"a"`, `"r+"`, and `"w+"` each read, clear, append, or keep the existing text, so check the mode when the contents are wrong.

### Check your understanding

*These questions are written for this course.*

````quiz
Which mode should you use to replace the entire contents of a file?
○ "r"
→ Not quite. "r" only reads, and can't write at all.
◉ "w"
→ Yes. "w" clears the file when it opens, so the new text replaces everything.
○ "r+"
→ Not quite. It keeps the old contents, so leftover text can remain.
````

````quiz
A file read loop `while (fgets(line, sizeof line, in) != NULL)` stops when what happens?
○ The first empty line is read.
→ Not quite. An empty line is a line, and the loop continues past it.
◉ There are no more lines to read, so fgets returns NULL.
→ Yes. The loop condition is false once the end of the file is reached.
○ The file is closed by the loop.
→ Not quite. The loop reads, and the file stays open until fclose runs.
````

````quiz
Why check `if (in == NULL)` after opening a file for reading?
○ Because reading always fails the first time.
→ Not quite. Reading works when the file opens.
◉ So that a missing file is reported, rather than causing undefined behavior when it's read.
→ Yes. fopen returns NULL for a file that didn't open, and reading through NULL is undefined.
○ To move the reading position to the start.
→ Not quite. Checking the pointer doesn't change where the file reads from.
````
