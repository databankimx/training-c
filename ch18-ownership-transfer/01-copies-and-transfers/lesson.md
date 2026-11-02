## Copies and transfers

Copying a value makes a second, independent value, and for a large value that can be expensive. A buffer of a million bytes has to be duplicated. Often the source is about to be thrown away anyway, so the copy is wasted work. Transferring is the alternative: the new owner takes over the contents, and the source is left empty, so no two objects claim the same data.

C++ has a copy constructor and a move constructor for this, and `std::move` makes a move possible. C has neither. It has plain assignment, which copies a structure, and a convention for transfer, which the program follows by hand. The class in the C++ version prints a message from each of its operations, and the C version does the same with functions, so the output can be compared line by line.

Here's the buffer for this step, in `src/main.c`:

```c
typedef struct {
    char text[32];
} Buffer;
```

The copy function makes a second buffer, and the source keeps its text:

```c
static void buffer_copy(Buffer *destination, const Buffer *source) {
    strcpy(destination->text, source->text);
    printf("Copy %s\n", destination->text);
}
```

The move function hands the contents over, and clears the source:

```c
static void buffer_move(Buffer *destination, Buffer *source) {
    memcpy(destination, source, sizeof *destination);
    printf("Move %s\n", destination->text);
    source->text[0] = '\0';
}
```

Press **Run**. The output is:

```
Construct alpha
Copy alpha
Move alpha
All three objects are still valid to use.
Destroy alpha
Destroy alpha
Destroy
```

The copy `b` gets its own text, so `a` keeps `alpha`. The move `c` takes the text from `a`, so `a` is left empty. The last line is `a`, destroyed with no text, since its contents have been moved away. That's the moved-from state: valid to destroy and to assign to, but holding nothing in particular.

### Destruction is written out

C++ runs each object's destructor automatically, in reverse order of creation. C has no destructors, so the program calls `buffer_destroy` on each buffer itself, in the same reverse order: `c`, then `b`, then `a`. The order is the program's responsibility, and the output matches the C++ version because the calls are in that order.

### A moved-from buffer is still a buffer

After the move, `a` still exists and can be used, but its text is empty. The C++ standard calls this a valid but unspecified state. In C the rule is simpler, because the program clears the source itself and the clearing is part of the design. A program should use a moved-from buffer only to assign a new value to it, or to destroy it. Reading its old text, as if the move hadn't happened, is a bug.

### Cost

Copying a structure with a large array copies every byte of it, and the copy function above copies the text again. A move copies the structure once, and then clears the source. For a buffer that holds a pointer to heap memory, rather than the text itself, the move copies only the pointer, which is far cheaper. The next step uses that form.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `buffer_move` leave in its source?
○ A copy of the text, so the source still works.
→ Not quite. That would be a copy, and the move gives the text away.
◉ An empty text, since the contents were handed to the destination.
→ Yes. The source is cleared so that no two buffers claim the same text.
○ The text, but marked as moved.
→ Not quite. C has no such marking. The text is cleared.
````

````quiz
Why does the program call `buffer_destroy` in the order c, b, a?
○ Because the compiler requires that order.
→ Not quite. C doesn't check the order of the calls.
◉ Because it matches the reverse order of creation, as C++ destructors would run.
→ Yes. The program follows the order by hand, since C runs no destructors.
○ Because a must be destroyed last to free the memory.
→ Not quite. The buffers are structures on the stack, so none of them needs freeing.
````

---

### Try it in the runner

Add a new `Buffer d;` and call `buffer_move(&d, &c);` before the message, then predict the output before you press **Run**. It prints `Move alpha`, since `c` gives its text to `d`. Then add `buffer_destroy(&d);` before the other destroys. The output shows `Destroy alpha` for `d`, then `Destroy` for `c` with no text, then `Destroy alpha` for `b`, and `Destroy` for `a`. Restore the program before you continue.

---

A transfer gives the contents to a new owner and leaves the source empty. The next step applies the same idea to ownership of heap memory, where the transfer is the only way to pass a block to someone else.
