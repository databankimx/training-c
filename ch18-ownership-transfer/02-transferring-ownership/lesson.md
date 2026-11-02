## Transferring ownership

Some resources can't be copied at all, because two owners would release the same block twice. A heap block owned by one pointer is an example: copying the pointer would give two owners, and the double free from the dynamic-memory step would follow. The C++ course calls such a type move-only, and its `std::unique_ptr` can only be moved. C has no such rule, so the program enforces it: a transfer moves the pointer and leaves the source empty.

This step uses a resource from the single-owner step, so the ownership rule is already familiar. The only new part is the transfer.

Here's the transfer, from `src/main.c`:

```c
static void transfer_ownership(Resource **destination, Resource **source) {
    *destination = *source;
    *source = NULL;
}
```

The function takes the addresses of two pointers. The destination receives the resource pointer, and the source is set to `NULL`. Afterwards exactly one pointer holds the block, and the other owns nothing.

The call in `main` is:

```c
Resource *a = resource_create("file E");
Resource *b = NULL;
transfer_ownership(&b, &a);
```

Press **Run**. The output is:

```
Start
Acquire file E
a owns nothing: yes
b owns the resource: yes
End
Release file E
```

The resource is acquired once and released once, by `b`, before the block ends. `a` releases nothing, because it holds `NULL`. Since the transfer happened before any work was done with the resource, there's only one owner at each moment.

### Why a null test is the safe check

The `NULL` in the source is the C form of the empty `unique_ptr`. The program checks it with a test, `a == NULL`, before any use, and the output reports that check. A program that uses `a` after the transfer without that test is using a pointer to memory it no longer owns, and the result is undefined behavior. The check turns that mistake into a condition the code can see.

### Passing ownership into a function

The same transfer works for a function. If a function takes a pointer by its address, and it's the one that stores or releases the resource, it becomes the owner for as long as it holds the pointer. The comment on the function has to say so, since the code shows only the transfer. When the function hands the resource on, it sets its own pointer to `NULL`, and the next owner releases it.

### When to transfer

Transfer when the source is no longer needed, and when the object should live somewhere else. Copying a pointer is the right choice only when the shared count from the shared-ownership step records it. Copying a single-owner pointer without transferring creates a second owner, and that's the mistake the "Try" shows.

---

### Quiz

*These questions are written for this course.*

````quiz
After `transfer_ownership(&b, &a);`, what does `a` hold?
○ The same resource as b, so both can use it.
→ Not quite. A single owner can't share the block, so a is cleared.
◉ NULL, since the source was emptied and b owns the resource.
→ Yes. The transfer moves the pointer and leaves the source empty.
○ A copy of the resource.
→ Not quite. A copy would be a second owner, and the transfer doesn't make one.
````

````quiz
Why does the program test `a == NULL` before using it after a transfer?
○ Because a is always NULL after a transfer.
→ Not quite. The test is a safety check, and it has an answer that depends on the program's state.
◉ Because using a pointer that owns nothing is undefined behavior, and the test catches it before the use.
→ Yes. The test turns a possible crash into a condition the code can see.
○ Because the compiler requires a test after every assignment.
→ Not quite. The compiler doesn't require it, and the test is a choice the program makes.
````

---

### Try it in the runner

Replace the call `transfer_ownership(&b, &a);` with `b = a;`, and predict whether `a` still owns the resource afterwards. It does, since the copy leaves both pointers holding the block. Then add `resource_destroy(a);` before the closing brace of the block, and predict the result. The block is released twice, which is a double free. Restore the transfer before you continue.

---

A transfer gives a resource to one new owner and leaves the source empty, so the single-owner rule still holds. The chapter summary follows, and then two homework exercises that use transfers with ownership.
