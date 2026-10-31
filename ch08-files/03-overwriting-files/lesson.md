## Overwriting files

The last two steps wrote a file and read one back, and they seemed to work. This step shows a mistake that's easy to make, and that gives wrong results without any error message.

Here's the program for this step, in `src/main.c`. It writes a long line, then writes a short line over it:

```c
FILE *out = fopen("data/test.txt", "w");
fprintf(out, "This first version of the text is quite long.");
fclose(out);

FILE *file = fopen("data/test.txt", "r+");
fprintf(file, "Short text.");
fclose(file);
```

Before you press **Run**, predict the output. The program then reads the file back and prints it. Press **Run** and check your prediction. The output is:

```
Short text.version of the text is quite long.
```

Only the first eleven characters were replaced, and the rest of the original line survived. Nothing reported an error, because nothing went wrong in the sense the library checks for. The file did exactly what it was asked to: it wrote the new text at the start of the file, and it didn't clear what came after.

### Why it happens

The mode `"r+"` opens an existing file for both reading and writing, and it leaves the existing contents in place. Writes start at the beginning of the file, and they overwrite whatever bytes are there. If the new text is shorter than the old, the leftover bytes remain at the end.

The fix is to say, when you open the file, that its old contents should be discarded. The mode `"w"` does this. It creates the file, or empties it if it already exists, and then the file is open for writing only. `"w+"` does the same and also allows reading. Whichever you use, the rule is the same: open a file in a mode that clears it when you intend to replace the whole file.

### Modes in fopen

The second argument to `fopen` is the mode, and the modes are easy to confuse:

| Mode | Opens for | Existing contents |
|---|---|---|
| `"r"` | reading | kept; the file must exist |
| `"w"` | writing | cleared, or created |
| `"a"` | appending | kept; new text goes at the end |
| `"r+"` | reading and writing | kept; writes start at the beginning |
| `"w+"` | reading and writing | cleared, or created |

The `"r+"` mode in this step is the one that leaves old text behind. Choose the mode that matches what you intend, and check it when a file's contents come out wrong.

### The block and closing

The first part of the program writes the long line, then calls `fclose` before the program opens the file again. That matters. Until `fclose` runs, the text may still be waiting in the file's buffer, and the second `fopen` could read the file before the long line has been fully written. Closing each file when you're done with it keeps the order of reads and writes clear.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `"r+"` leave the rest of the old text in place?
○ Because `"r+"` always appends to the end of the file.
→ Not quite. Appending is the mode "a". `"r+"` writes from the start of the file.
◉ Because it opens the existing file without clearing it, so only the bytes written are replaced.
→ Yes. Writes overwrite from the start, and anything beyond the new text stays.
○ Because the file is locked while it's open.
→ Not quite. Locking has nothing to do with the leftover text.
````

````quiz
Which mode replaces the whole contents of a file?
○ "r+", which reads and writes the file.
→ Not quite. It keeps the existing contents, so leftover text survives.
◉ "w", which clears the file when it opens.
→ Yes. "w" empties the file, or creates it, before any text is written.
○ "r", which reads the file first.
→ Not quite. "r" only reads, and can't write at all.
````

---

### Try it in the runner

Change `"r+"` to `"w+"`, and predict the output before you press **Run**. The new text replaces the whole file, since `"w+"` clears it when it opens. The output is `Short text.` and nothing more.

Then change the `"w+"` back to `"a"`, and predict the output. Now the short text is added after the long line, so the output is the long line followed by `Short text.` on the same line.

---

Writing, reading, and overwriting cover the basics of file access. The summary and homework put them together, and the next chapter adds exceptions, which is the other standard way to report a file that won't open.
