## Dynamic memory

Every variable so far has a size fixed at the time the program is written. An `int numbers[3]` holds three values, and that's the end of it. Many programs need memory whose size is decided while the program runs: a list read from a file, a string whose length is unknown, a structure that grows as the user adds to it. That memory comes from the heap, and the program asks for it with `malloc`.

Here's the program for this step, in `src/main.c`:

```c
int *numbers = malloc(3 * sizeof *numbers);
if (numbers == NULL) {
    printf("Out of memory.\n");
    return 1;
}
numbers[0] = 10;
numbers[1] = 20;
numbers[2] = 30;
```

`malloc` takes a number of bytes, and returns a pointer to a block of that size, or `NULL` if the block can't be provided. The size here is `3 * sizeof *numbers`: three `int` values, with the size worked out from the pointer's type rather than typed as a number. Writing `sizeof *numbers` means the size stays right if the type changes later.

Press **Run**. The output is:

```
10 20 30
40 50
0 0
```

### Always check the result

The `if (numbers == NULL)` test is the first rule of dynamic memory. `malloc` returns `NULL` when it can't get the memory, and writing through a `NULL` pointer is undefined behavior, so the check comes before any use. The program stops with a message rather than continuing with nothing to write to. Every allocation in the course is checked in this way, and the cases that skip the check are the first thing to look for when a program crashes.

### Growing and zeroing

`realloc` changes the size of a block:

```c
int *grown = realloc(numbers, 5 * sizeof *grown);
if (grown == NULL) {
    free(numbers);
    return 1;
}
numbers = grown;
```

`realloc` may move the block to a new address, and it may return `NULL` if it can't grow the block. The program keeps the result in `grown`, and only replaces `numbers` once the call has succeeded. If `realloc` fails, the old block is still valid, so the program can free it. Writing `numbers = realloc(numbers, ...)` loses the old pointer on failure, which is a leak, and the vector in the containers chapter is built on this pattern.

`calloc` allocates a block and sets every byte to zero. Its two arguments are the count and the size of one element, so `calloc(2, sizeof *zeros)` gives two zeroed `int` values, which print as `0 0`.

### Freeing memory

Memory from the heap stays allocated until the program calls `free`:

```c
free(zeros);
free(numbers);
numbers = NULL;
```

Each block is freed once, when the program no longer needs it. The pointer is then set to `NULL`, so a later check can tell that the block has gone. Local variables are different: they're released automatically when their function returns, but heap memory is released only by `free`.

### Three common errors

Dynamic memory has three errors that the compiler can't catch, and each one causes a different kind of failure:

* **A leak** happens when a block is never freed. The program keeps running, but its memory use grows, and nothing reports the loss. Each `malloc` needs a matching `free`, on every path through the function, including the error paths.
* **A double free** happens when `free` is called on a block that was already freed. The result is undefined, and it often crashes or corrupts the heap later.
* **Use after free** happens when a program reads or writes a block after freeing it. The memory may still look valid for a while, which makes the bug hard to find.

Setting the pointer to `NULL` after `free` protects against the second and third errors when the pointer is checked, since `free(NULL)` does nothing and a `NULL` check catches the read.

### Why double free and use after free are security problems

A leak wastes memory, but the program keeps behaving as the code says. A double free or a use after free can let an attacker change what the program does, and that's why both are counted as serious security flaws, not only as bugs.

The heap keeps bookkeeping for each block it hands out and takes back, such as the block's size and whether it's free. A double free corrupts that bookkeeping, because `free` puts the same block on the free list twice. Later, two calls to `malloc` can be given the same block, so two parts of the program believe they own the same memory. Whatever one part writes, the other reads.

A use after free is more direct. The block has been returned to the heap, and another allocation may now reuse it for different data. A pointer that still refers to the block reads or writes whatever now lives there. If that data includes something the program trusts, such as a function pointer, a length, or a permission, a value an attacker can influence can take its place. This pattern, where freed memory is reused for attacker-controlled data, is one of the classic routes to running an attacker's code.

These errors are hard to find for the same reason they're dangerous: the program often runs normally until the memory is reused. The defenses are the rules from this step, applied every time:

* Set each pointer to `NULL` immediately after `free`, so a later check catches the use.
* Free each block once, in the function that owns it, and write the owner down at the allocation.
* Use a memory checker while developing. The debugging and sanitizers chapter covers AddressSanitizer, which reports both errors at the point they happen.

The same reasoning applies to the buffer overflows described in the strings and structures chapters. Writing past the end of a buffer can overwrite the same kind of data, which is why this course treats unchecked sizes as a security issue, and why each `strcpy` into a fixed buffer carries a comment that names the limit.

### Finding these errors with tools

The rules above prevent most memory errors, but a tool finds the ones that slip through. A memory checker runs the program and watches every allocation, free, and read. It reports a leak when a block is still allocated at exit, a double free when a block is freed twice, and a use after free when a freed block is read or written. Each report names the line where the block was allocated, which is what you need to fix it.

Two checkers are used in this course:

* **Dr. Memory** for Windows. Fetch it once with `resources\vendor\drmemory\fetch-drmemory.ps1`, which installs it into `resources\vendor\drmemory\install`, and prints the full path to `drmemory.exe` when it finishes. Then run a built program through it, from the step's folder, using the path the script printed:

```pwsh
<path printed by the script> -- .\build\program.exe
```

The report is written to the console and to a log folder that Dr. Memory names in its output. The `--` separates the tool's options from the program and its arguments.

* **Valgrind** for Linux. It's the usual checker on Linux and macOS, and it isn't available on Windows, so readers on those systems can skip it. To run a program through it:

```sh
valgrind --leak-check=full ./program
```

Both tools slow a program down, often by a factor of ten or more, so use them on test inputs, not on large data.

A clean report doesn't prove a program is safe. It shows the paths the test runs exercised. Run every path you can, including the error paths, and check that each one reports nothing.

### Ownership

Every block has one owner, the code responsible for freeing it. In this program, `main` owns `numbers` and `zeros`, and frees them. When a function returns a block it allocated, the caller becomes the owner. Writing down who frees each block, in a comment at the point of allocation, prevents most leaks in a program of any size. The containers chapter applies the rule to the vector.

---

### Quiz

*These questions are written for this course.*

````quiz
What should be checked immediately after `malloc`?
○ That the number of bytes is even.
→ Not quite. The size isn't what needs checking first.
◉ That the returned pointer is not NULL, since malloc returns NULL when it can't provide the memory.
→ Yes. Using a NULL pointer is undefined behavior, so the check comes before any use.
○ That the block is zeroed.
→ Not quite. malloc doesn't zero the block. calloc does.
````

````quiz
Why does `realloc` get its result stored in a new variable?
○ Because realloc can't be used on an int pointer.
→ Not quite. It can be used on any pointer to heap memory.
◉ Because realloc may return NULL, and the old block must still be freed if it fails.
→ Yes. Keeping the old pointer until the call succeeds avoids losing the block.
○ Because realloc always returns a larger block with the same address.
→ Not quite. The block may move to a new address.
````

---

### Try it in the runner

Delete the line `numbers = NULL;`, and add a second `free(numbers);` after the first. Predict the result before you press **Run**. The result is undefined: the block has been freed twice, and the program may crash, print a warning on some systems, or appear to finish. That's the double-free error, and it's why the pointer is set to `NULL` after each free. Restore the program before you continue.

Then remove the `free(zeros);` line, and predict whether the program still prints the same output. It does, since the leak doesn't affect the output, but the block is never returned. This is the most common kind of memory error, and it's invisible without a tool that counts allocations, which the debugging chapter covers.

---

Heap memory lives until it's freed, and the program owns it from the moment it's allocated. The containers chapter builds a growable list on these rules, and the summary below covers the chapter.
