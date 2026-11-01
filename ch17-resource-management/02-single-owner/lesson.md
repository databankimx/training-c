## Single owners

The last step kept every release inside one function. Often a block of heap memory has to outlive the function that creates it: it's returned to a caller, stored in a structure, or passed between parts of a program. A raw pointer can hold that memory, but it doesn't say who is responsible for releasing it. The C++ course uses `std::unique_ptr` for this, which is a class that holds the only pointer to an object and deletes it when it goes out of scope. C has no such class, so the course uses an ownership convention, and the code has to follow it.

Here's the program for this step, in `src/main.c`. The creation function returns a pointer, and the caller becomes its owner:

```c
static Resource *resource_create(const char *name) {
    Resource *resource = malloc(sizeof *resource);
    if (resource == NULL) {
        return NULL;
    }
    strcpy(resource->name, name);
    printf("Acquire %s\n", resource->name);
    return resource;
}
```

The comment above the function says what the caller takes on: the returned pointer is theirs, and they must release it with `resource_destroy`. The name says the same thing, since `create` and `destroy` are a matched pair. Then `main` takes the pointer and gives it back:

```c
Resource *owner = resource_create("file C");
if (owner == NULL) {
    printf("Out of memory.\n");
    return 1;
}
resource_describe(owner);
printf("Using file C\n");
resource_destroy(owner);
owner = NULL;
```

Press **Run**. The output is:

```
Start
Acquire file C
Holding file C
Using file C
Release file C
After the block
```

The `Release` line comes from `resource_destroy`, before the block closes. The line `owner = NULL` makes the pointer empty once the block has been released, so a later check can tell the difference between a live resource and a released one.

### Ownership by convention

Nothing in C stops a second part of the program from keeping a copy of `owner`, and calling `resource_destroy` on it. The C compiler accepts that, and the mistake shows up only at run time, as a double free. That's the difference from `std::unique_ptr`, which refuses to be copied. In C, ownership is a rule the code follows, and a good program writes it down. Three habits make it workable:

* **Name the pair.** A function that returns a new object is named `create`, `open`, or `new`, and it has a matching `destroy`, `close`, or `free`.
* **Say who owns what.** A comment at the creation function, and at any function that takes or returns ownership, says who releases the block.
* **Clear the pointer.** Setting the pointer to `NULL` after release turns a later use into a check that can fail cleanly, rather than a read of freed memory.

### Passing ownership on

A function can take ownership by convention too. For example, a function that stores a resource in a structure and promises to release it when the structure is destroyed becomes the new owner. The comment has to say so, since nothing in the code shows it. The rule is the same as before: exactly one place releases the block, and every other place borrows it without freeing.

### Checking for a resource

A creation function can fail, so the result is checked straight away, as the dynamic-memory step described. The `NULL` check in `main` is the C form of asking whether a `unique_ptr` is empty. Using a `NULL` pointer is undefined behavior, so the check comes before any use.

### Unchecked names

The `strcpy` in `resource_create` copies the name without checking its length. The comment marks it as an unchecked path. A name longer than 31 characters would overflow the structure, and the same care applies to every fixed-size copy in the course.

---

### Quiz

*These questions are written for this course.*

````quiz
What makes `resource_create` and `resource_destroy` an ownership pair?
○ They are both declared static.
→ Not quite. Being static only limits where the functions can be called.
◉ The caller of resource_create becomes the owner, and must release the block with resource_destroy.
→ Yes. The pair states the rule: one creation, one release, by the owner.
○ They both print a message.
→ Not quite. The messages don't decide who owns the block.
````

````quiz
Why does the program set owner to NULL after releasing it?
○ Because free requires a NULL pointer to work.
→ Not quite. free accepts any pointer it was given, and NULL is only a safe default afterwards.
◉ So that a later check can tell the resource is gone, rather than reading freed memory.
→ Yes. A NULL check catches the mistake, where a dangling pointer would not.
○ To make the compiler refuse a second release.
→ Not quite. The compiler doesn't track this, so the NULL is a convention the program checks.
````

---

### Try it in the runner

Delete the line `owner = NULL;`, and add a second `resource_destroy(owner);` after the first. Predict the result before you press **Run**. The program releases the same block twice, which is a double free. The output may look normal, or the program may crash or corrupt its heap. The double free is the error the dynamic-memory step described as a security problem, and this is how an ownership mistake produces it. Restore the program before you continue.

---

A single owner releases each block once, and the convention names that owner. The next step handles the case where more than one part of a program needs a block, and a count has to decide when it's released.
