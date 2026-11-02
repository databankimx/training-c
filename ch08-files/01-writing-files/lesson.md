## Writing files

Every program so far has written to the screen and read from the keyboard. A file is a third place for data, and it's the one that outlives the program. The standard library handles files with the `FILE` type from `<stdio.h>`, and writing to one looks a lot like writing to the screen with `printf`.

Here's the program for this step, in `src/main.c`:

```c
FILE *out = fopen("data/greetings.txt", "w");
if (out == NULL) {
    printf("Could not create the file.\n");
    return 1;
}

fprintf(out, "Hello, file!\n");
fprintf(out, "Writing to a file works like printf.\n");
fclose(out);
```

Press **Run**. The program prints one line, `Wrote data/greetings.txt`. The program doesn't print the file's contents. A **View** button appears over the bottom right of the Output pane, named for the file. Press it to open the file in the default application for text files.

### The file pointer

`FILE *out` declares a pointer to a `FILE`, which is the C library's record of an open file. The pointer is what every file function takes, so the functions know which file to use. `fopen` returns that pointer, or `NULL` if it fails.

`fopen`'s second argument is the mode. `"w"` means write, and it creates the file, or replaces an existing one, as the overwriting step explains. The first argument is the path, which is relative to the folder the program runs from. The runner runs each step in a copy of its folder, so `data/greetings.txt` refers to the `data` folder inside that copy.

### The data folder

The path names a folder called `data`. A file can only be created inside a folder that already exists, and a fresh copy of the step doesn't contain one, because the course doesn't store empty folders in version control. So the program creates it first:

```c
CreateDirectoryA("data", NULL);
```

`CreateDirectoryA` is a Windows function, from `<windows.h>`, and it does nothing harmful if the folder is already there. Calling it on every run keeps the program working from a clean copy.

### Checking that the file opened

Opening a file can fail. The folder might not exist, the file might be locked, or you might not have permission to write it. The `if (out == NULL)` check tests whether `fopen` succeeded, and returns early if it didn't. Skipping the check means the program calls `fprintf` with a `NULL` pointer, which is undefined behavior, and the program may crash instead of reporting the problem.

### Closing the file

The program calls `fclose(out)` when it's finished writing. Closing flushes any text still waiting in the file's buffer, and releases the file so other programs can use it. A file that isn't closed may not contain all of its text, and that's a bug that's hard to see.

C also closes open files when the program ends, so `fclose` isn't needed for the program to finish correctly. Write it anyway. The point where a file is finished becomes visible in the code, and a long program might open many files before it returns from `main`.

---

### Quiz

*These questions are written for this course.*

````quiz
Which header provides the file functions `fopen`, `fprintf`, and `fclose`?
○ <iostream>
→ Not quite. <iostream> is a C++ header. C's file functions come from <stdio.h>.
◉ <stdio.h>
→ Yes. <stdio.h> declares fopen, fprintf, and fclose, along with printf.
○ <filesystem>
→ Not quite. That's a C++ header. C uses <stdio.h> for files.
````

````quiz
Why does the program check `if (out == NULL)` after calling `fopen`?
○ Because out has to be checked before any text can be written.
→ Not quite. The check is about whether the file opened, not about the text.
◉ Because the file might not open, and the program can't write to a file it doesn't have.
→ Yes. fopen returns NULL when it fails, so the check reports the problem before any write.
○ Because FILE pointers are always empty.
→ Not quite. A FILE pointer is empty only when fopen fails.
````

---

### Try it in the runner

Change the path to `data/missing/greetings.txt`, where `missing` is a folder that doesn't exist, and predict what the program prints, before you press **Run**. It prints `Could not create the file.`, since `fopen` returns `NULL` when the folder inside it is missing. Change the path back before you continue.

Then remove the `fclose(out);` line, and run again. The program still writes the file, because C closes open files when `main` returns. Put the line back, since closing explicitly makes the point where the file is finished easy to see.

---

Writing a file is an ordinary output operation with a path attached. The next step reads one back, and shows how the same file pointer works in the other direction.
