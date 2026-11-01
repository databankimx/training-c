## Summary: Function pointers with context

This chapter covered passing behavior and state to code that will call them later. C has no lambdas or captures, so each one is written out: a named function passed by its address for the rule, and a context structure passed by pointer for the state.

* **A rule is a function pointer.** The caller passes the address of a named function, and the code it's given to calls it.
* **A comparison for sorting must be consistent.** A rule that returns negative, zero, or positive, and never contradicts itself, gives a well-defined order.
* **The rule's parameters are typed by the caller.** `qsort` passes `void *` pointers, and each rule casts them to the element type it was written for.
* **A context holds the state a rule needs.** It's a structure, passed by pointer, with a member for each value the function uses.
* **A context may hold a copy.** A copy is made when the context is created, and later changes to the original don't reach it.
* **A context may hold a pointer.** The function then sees and changes the current value of the original.
* **A context must not outlive what it points to.** Using it after the target is gone is undefined behavior.
* **Name every member.** Each value a function needs is listed in its context, so the dependencies are visible.

### Check your understanding

*These questions are written for this course.*

````quiz
What does a context holding a pointer to a variable let its function do?
○ Use a copy of the variable, made when the context was created.
→ Not quite. A copy is what a context holds when it stores a value, not a pointer.
◉ See and change the current value of the variable, for as long as the variable is alive.
→ Yes. The pointer refers to the original, so every use sees its current value.
○ Run after the variable has been removed from the program.
→ Not quite. Using the variable after it's gone is undefined behavior, not a feature.
````

````quiz
Which comparison function is valid for sorting in descending order?
○ One that returns 0 when a is less than or equal to b.
→ Not quite. A comparison that treats unequal values as equal can misbehave.
◉ One that returns a positive number when a is less than b, so that the larger values come first.
→ Yes. A consistent comparison, with the larger values first, gives the descending order.
○ One that returns the difference between a and b, whatever their sign.
→ Not quite. The sign must say which value comes first, and a fixed rule for the sign is required.
````

````quiz
Why does the course name every member of a context, rather than using a shortcut?
○ Because the compiler requires a name for each member.
→ Not quite. The compiler doesn't require it. The reason is the reader.
◉ Because a reader can see every value the function depends on, in one place.
→ Yes. An explicit list shows the dependencies, which a shortcut hides.
○ Because a shortcut makes the context larger.
→ Not quite. The shortcut is a C++ capture form, and the context is the same size either way.
````
