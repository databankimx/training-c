## Shared ownership

Sometimes no single owner can say when a block is no longer needed. A node in a tree may be pointed to by its parent and by a cache, and either one might be the last to let go. The C++ course uses `std::shared_ptr` for this, where each copy of the pointer is an owner, and the object is released when the last owner goes away. C has no such type, so this step writes the count by hand.

Here's the structure for this step, in `src/main.c`:

```c
typedef struct {
    char name[32];
    int owners;
} SharedResource;
```

The `owners` member is the count. Each owner holds the same pointer, and the count says how many owners there are. Two functions change the count. `shared_retain` adds an owner, and `shared_release` removes one:

```c
static void shared_release(SharedResource *resource) {
    resource->owners--;
    if (resource->owners == 0) {
        printf("Release %s\n", resource->name);
        free(resource);
    }
}
```

The last owner to release frees the block. Every earlier release only lowers the count. The program follows the same steps as the C++ version:

```c
SharedResource *first = shared_create("file D");
printf("Owners: %d\n", shared_owner_count(first));

{
    SharedResource *second = shared_retain(first);
    printf("Owners: %d\n", shared_owner_count(second));
    shared_release(second);
    second = NULL;
}

printf("Owners: %d\n", shared_owner_count(first));
printf("End\n");
shared_release(first);
first = NULL;
```

Press **Run**. The output is:

```
Acquire file D
Owners: 1
Owners: 2
Owners: 1
End
Release file D
```

The retain adds an owner, so the count goes to 2. Releasing the inner owner lowers it back to 1, and the block stays alive, since `first` still owns it. Only the final release, after `End`, frees the block and prints `Release file D`.

### The count is the whole rule

Each owner must call `shared_release` exactly once, and the count is the only thing that decides when the block is freed. Get the count wrong, and the program either frees the block while an owner still holds it, or never frees it at all. A retain without a matching release is a leak. A release without a matching retain frees too early. The count has to match the owners exactly, which is the same discipline as the single-owner step, applied to every holder.

The count is also not protected against other threads. A program with threads needs the count changed atomically, which the threads chapter covers. The single-threaded programs in this course need only the plain count.

### Choosing between single and shared ownership

Use a single owner whenever one place can say when the block is finished. It's simpler, and it can't be released twice by accident, since only one owner exists. Use a shared count only when the lifetime really depends on several owners. A count that's used where a single owner would do hides who is responsible, which is the same problem the C++ lesson warns about.

### Cycles

Two objects that each hold a shared pointer to the other keep each other's count above zero, so neither is ever freed. That's a cycle, and it's a leak in C as well as in C++. The C++ course fixes it with a weak pointer, and C needs the same care: a structure that can refer back to its owner should not hold a counted reference to it.

---

### Quiz

*These questions are written for this course.*

````quiz
What decides when a shared block is freed?
○ The first owner to release it.
→ Not quite. The first release only lowers the count, and other owners may still hold the block.
◉ The last owner to release it, when the count reaches zero.
→ Yes. Each release lowers the count, and the block is freed only at zero.
○ The end of the program, always.
→ Not quite. The block is freed when its count reaches zero, which can happen earlier.
````

````quiz
What is the result of a retain that is never matched by a release?
○ The block is freed early.
→ Not quite. An extra owner keeps the count above zero, so the block is not freed early.
◉ A leak, since the count never reaches zero.
→ Yes. The block stays allocated for as long as the count is above zero.
○ Nothing, since retains are optional.
→ Not quite. Each retain must match exactly one release.
````

---

### Try it in the runner

Delete the line `first = NULL;`, and add a second `shared_release(first);` after the first one. Predict the result before you press **Run**. The count is already zero when the second call runs, so the block is released twice, which is a double free. The count protects against releasing too early, but it can't protect against a release that happens after the count is already zero. Restore the program before you continue.

---

Shared ownership uses a count to decide when a block is freed, and each owner must release exactly once. The next step is the chapter summary, and then two homework exercises that use all three kinds of ownership.
