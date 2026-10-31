## Cleanup with goto

A function that opens a resource has to close it, however it leaves. A file opened at the top of a function must be closed on the normal path, and on every error path after it. With several resources, the list of things to undo grows with each one, and it's easy to miss one. C programs solve this with a `goto` to a block of cleanup code at the bottom of the function, and that's the pattern this step shows.

C has no exceptions, so the standard exception classes of the C++ chapter have no counterpart here. Their job was to carry a description of a failure up through the calls, and the errno step already covered how C describes one. The cleanup problem remains, and it's what this step solves.

Here's the function for this step, in `src/main.c`. It copies one file to another:

```c
int copy_file(const char *from, const char *to) {
    int result = -1;

    FILE *in = fopen(from, "r");
    if (in == NULL) {
        goto done;
    }

    FILE *out = fopen(to, "w");
    if (out == NULL) {
        goto close_in;
    }

    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (fputc(ch, out) == EOF) {
            goto close_out;
        }
    }
    result = 0;

close_out:
    fclose(out);
close_in:
    fclose(in);
done:
    return result;
}
```

The function opens two files, and each failure must release only what's already open. Press **Run**. The output is:

```
Copy 1: ok
Copy 2: failed
```

The first copy succeeds, so `result` becomes 0. The second copy fails, because `data/missing.txt` doesn't exist, so the `goto done` skips both `fclose` calls. Nothing is open at that point, so nothing needs closing.

### Labels in reverse order

The labels sit in the reverse order of the opening. `close_out` releases the file opened second, and `close_in` releases the first. A failure after the second `fopen` jumps to `close_in`, which skips `fclose(out)`, because `out` was never opened. A failure during copying jumps to `close_out`, and the code falls through to `close_in` to release both.

The normal path also falls through both labels. `result = 0` runs first, and then both files close. So every path ends in the same place, and every open file is closed exactly once.

### Why goto is used here

`goto` has a poor reputation, because it can jump anywhere and make a program hard to follow. In this pattern it jumps only forward, to labels at the bottom of the same function. That keeps the flow easy to read, and it puts every release in one place. The alternative is to repeat the close calls at each failure point, where a later change can easily leave one out.

Use `goto` for this cleanup pattern, and nowhere else in the course. Other uses are rarely needed, and the labeled cleanup is the form C programmers recognize.

### Keeping the result

`result` starts at -1, the failure value, and only becomes 0 after the copy finishes. So each path returns the right answer without extra variables. A caller tests the return value, as the return-codes step showed.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does a failure at the second `fopen` jump to `close_in` and not to `close_out`?
○ Because close_out is only for reading.
→ Not quite. close_out is for the output file.
◉ Because the output file was never opened, so only the input file needs closing.
→ Yes. Jumping to close_in skips the fclose of a file that isn't open.
○ Because goto can only jump one label at a time.
→ Not quite. The labels are chosen by which resources are open at that point.
````

````quiz
What value does `copy_file` return when the source file doesn't exist?
○ 0
→ Not quite. 0 means success, and no copy was made here.
◉ -1
→ Yes. result starts at -1, and it changes only after a complete copy.
○ NULL
→ Not quite. copy_file returns an int, not a pointer.
````

---

### Try it in the runner

Change the destination of the first call from `data/copy.txt` to `data/nope/copy.txt`, where `nope` is a folder that doesn't exist. Predict the output before you press **Run**. The output file can't be opened, so the program jumps to `close_in`, the function returns -1, and the first line reads `Copy 1: failed`. The second line is unchanged, `Copy 2: failed`. Change the destination back before you continue.

Then add a third `copy_file` call that copies `data/source.txt` to `data/copy2.txt`, and predict its message. It prints `Copy 3: ok`, since that copy works. Remove the extra call before you continue.

---

A function that opens resources can release them on every exit path with a labeled block at its end. The summary covers the chapter, and the homework uses the same pattern on its own.
