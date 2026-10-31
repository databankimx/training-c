## errno

The return-code step showed a function reporting that something failed. It didn't say why. The standard library goes further: when a library call fails, it stores a reason in a global variable called `errno`, declared in `<errno.h>`. The reason is a number, and `strerror` turns that number into a message.

Here's the program for this step, in `src/main.c`. It tries to open a file that doesn't exist:

```c
errno = 0;
FILE *file = fopen("data/missing.txt", "r");
if (file == NULL) {
    switch (errno) {
        case ENOENT:
            printf("The file doesn't exist.\n");
            break;
        case EACCES:
            printf("Permission denied.\n");
            break;
        default:
            printf("Could not open the file: %s\n", strerror(errno));
            break;
    }
    printf("Error code: %d\n", errno);
    return 1;
}
```

Press **Run**. The output is:

```
The file doesn't exist.
Error code: 2
```

`fopen` returned `NULL`, which is the signal that it failed. Then `errno` holds the reason, which is `ENOENT`, the code for "no such file or directory". `ENOENT` and `EACCES` are names defined in `<errno.h>`, and they're the values the `switch` compares against. The `switch` is the one from the decisions chapter, choosing a message for each case.

### Reading errno

Three rules make `errno` reliable:

* **Set it to 0 before the call.** The library sets `errno` only when something fails, and it doesn't clear it when a call succeeds. A value left over from an earlier failure would look like the reason for a new one. The program sets `errno = 0` first, so the value it reads comes from this call.
* **Read it straight after the failed call.** Another library call can change `errno`, so the check should come before anything else runs.
* **Check the return value first.** `errno` only says why a call failed, so it means nothing unless the return value has already shown a failure. `fopen` returning `NULL` is the test, and `errno` is the explanation.

### Turning errno into a message

`strerror` returns a text description of an error number. The `default` case uses it for any error the program doesn't handle itself:

```c
printf("Could not open the file: %s\n", strerror(errno));
```

The message depends on the C library, so the wording may differ between systems. The number is the same everywhere the library uses the same error code, and that makes `switch` on `errno` a more reliable test than comparing message text.

### Limits

`errno` is a single global value, and it's only meaningful right after a failure. A program that calls several library functions in a row has to read it between them, if the reason matters. That's the main difference from the error codes of the last step, which came back with each call and stayed with it.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does the program set `errno = 0` before calling `fopen`?
○ Because fopen needs errno to be 0 before it can open a file.
→ Not quite. fopen doesn't read errno before it opens anything.
◉ Because errno keeps its old value on success, so a leftover value could be mistaken for the reason for this failure.
→ Yes. The library sets errno only on failure, so clearing it first makes the value trustworthy.
○ Because errno is a pointer that has to be set to NULL.
→ Not quite. errno is an int, and clearing it sets it to zero.
````

````quiz
Which value tells the program that `fopen` failed?
○ errno being nonzero.
→ Not quite. errno can keep an old value, so it isn't the test. The return value is.
◉ fopen returning NULL.
→ Yes. The return value shows the failure, and errno explains it.
○ errno being equal to ENOENT.
→ Not quite. That explains one kind of failure, but other failures have other errno values.
````

---

### Try it in the runner

Change the path from `data/missing.txt` to `data`, which is the name of a folder, and predict the output before you press **Run**. On Windows, `fopen` refuses to open a folder for reading, and the reason is `EACCES`, so the program prints `Permission denied.` and then `Error code: 13`.

Then change the path to `data/missing.txt` again, and remove the `errno = 0;` line. The output is the same, because this call also fails with the same reason. The line matters only when a call might succeed, and then `errno` would still hold the old value. Put the line back before you continue.

---

`errno` tells you why a library call failed, once the return value has told you that it did. The next step uses that idea across a function that opens several resources, and it releases each one on every way out.
