## Summary: Resource management

This chapter covered how a C program releases what it holds on every route out of a function, and how ownership and reference counts decide who releases a shared block. C has no destructors or smart pointers, so each of these is written out by the programmer.

* **Every route releases what it holds.** A cleanup block at the end of a function, reached by goto, gives each early exit the releases it needs.
* **Labels run in reverse order of allocation.** A route that stops partway falls through the releases below its label, and skips the ones above.
* **A single owner releases each block once.** The function that creates a block names its owner, and a matching destroy function releases it.
* **Ownership is a convention in C.** Nothing stops a second copy of the pointer, so comments and naming have to say who owns what.
* **Clear the pointer after release.** Setting it to NULL turns a later use into a check that can fail cleanly.
* **A reference count shares ownership.** Each owner retains the block, and the last owner to release it frees it.
* **The count must match the owners exactly.** A missing release leaks the block, and an extra release frees it too early or twice.
* **Cycles leak shared blocks.** Two blocks that hold counted references to each other never reach zero.

### Check your understanding

*These questions are written for this course.*

````quiz
What releases a block when a function has several early returns and no destructors?
○ The compiler releases it when the function returns.
→ Not quite. C does not release heap memory automatically.
◉ A cleanup block that every route reaches, releasing what that route holds.
→ Yes. The goto labels make each route release exactly what it has.
○ The operating system releases it when the program ends.
→ Not quite. That's too late for a long-running program, and it's not a design to rely on.
````

````quiz
Why does the single-owner convention name the creation and destroy functions as a pair?
○ Because the compiler requires matching names.
→ Not quite. The compiler doesn't check names, so the pairing is for the programmer.
◉ So the caller who receives ownership can see that it must release the block, and how.
→ Yes. The names show the rule, since a create must be followed by a destroy.
○ Because only one of the two functions can be called.
→ Not quite. The caller must call both, one to create and one to release.
````

````quiz
Three owners share one block through a reference count. One of them releases. What happens?
○ The block is freed at once.
→ Not quite. Two owners still hold the block, so the count is two.
◉ The count drops to two, and the block stays allocated.
→ Yes. The block is freed only when the count reaches zero.
○ The other two owners lose their references.
→ Not quite. Releasing one owner only lowers the count, and the others keep theirs.
````
