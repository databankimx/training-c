## Summary: Ownership transfer

This chapter covered handing a value or a block from one owner to another, the C form of moving. C has no move constructors or `std::move`, so each transfer is written by the program, and the source is cleared by convention.

* **A copy makes an independent value.** Assignment copies a structure, and the copy keeps its own contents.
* **A transfer takes the contents from another object.** The source is cleared, so no two objects claim the same data.
* **A cleared source is valid to destroy and to assign to.** Reading its old contents is a bug.
* **A pointer transfer leaves one owner.** The destination takes the pointer, and the source is set to NULL.
* **Test before use.** A cleared pointer owns nothing, and the `NULL` test turns a possible crash into a condition the code can see.
* **Copying a single-owner pointer creates a second owner.** That's a double free waiting to happen, so a single-owner block is transferred, never copied.
* **Destruction is written out.** C runs no destructors, so the program calls each release in reverse order of creation.
* **Transfer when the source is finished with.** Copy when both objects need their own value.

### Check your understanding

*These questions are written for this course.*

````quiz
What does a transfer of a pointer leave in the source?
○ A copy of the pointer, so the source still works.
→ Not quite. That would be a second owner, which the transfer avoids.
◉ NULL, so the source owns nothing.
→ Yes. The destination now holds the only pointer to the block.
○ The old pointer, marked as moved.
→ Not quite. C has no such marking, so the source is set to NULL.
````

````quiz
Why is a single-owner block transferred rather than copied?
○ Because copies are slower than transfers.
→ Not quite. The reason is correctness, not speed.
◉ Because a copy would make two owners, and both would try to release the block.
→ Yes. A transfer keeps exactly one owner at each moment.
○ Because the compiler refuses to copy pointers.
→ Not quite. C allows the copy, and the program must avoid it.
````

````quiz
What does a program need to do before using a pointer after a transfer?
○ Nothing, since the pointer is always valid.
→ Not quite. After a transfer the source may hold NULL, and using it is undefined behavior.
◉ Test it against NULL, and use it only when it holds a resource.
→ Yes. The test is the safe check on a cleared pointer.
○ Copy it back from the destination.
→ Not quite. Copying back would create a second owner.
````
