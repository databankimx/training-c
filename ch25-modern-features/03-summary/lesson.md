## Summary: Modern features

This chapter covered two ways modern code removes repetition and makes missing results explicit, in C23 and in the C style that predates it. C has no structured bindings or `std::optional`, so each one has a C form.

* **C23 `auto` takes the type from the initializer.** The type is still fixed at compile time, so it doesn't make C looser.
* **Named members replace structured bindings.** A record's parts are read by name, through a pointer to avoid a copy.
* **A pointer to a record avoids a copy.** `const Score *entry = &scores[i];` reads the record without copying it, and `const` says it won't change.
* **An optional result needs a flag.** A structure holding `found` and a value shows whether there is an answer.
* **Check the flag before reading the value.** The C structure does not stop a read of an empty result, so the convention is the protection.
* **A flag can't be confused with a valid value.** A magic value such as 0 or -1 can equal a real answer, and the flag cannot.
* **Array order is the programmer's job.** Without a sorting map, the order is whatever the program writes or sorts.

### Check your understanding

*These questions are written for this course.*

````quiz
Which statement about C23 `auto` is true?
○ It lets a variable change type while the program runs.
→ Not quite. The type is fixed at compile time.
◉ It takes the type from the initializer, and the type never changes afterward.
→ Yes. auto saves writing the type, and keeps it fixed.
○ It works in any C standard, including C11.
→ Not quite. It needs C23, which the chapter's CMake file selects.
````

````quiz
A function returns a `MaybeIndex` with `found` set to false. What must the caller do before reading `index`?
○ Nothing, since index is always valid.
→ Not quite. index holds 0 when nothing was found, and that looks like a real answer.
◉ Check `found`, and read index only when it's true.
→ Yes. The flag is the answer to the question the caller must ask first.
○ Multiply index by zero first.
→ Not quite. That doesn't make an empty result safe to read.
````

````quiz
Why is a flag better than returning 0 for "not found" from a function that returns an index?
○ Because 0 is slower to test.
→ Not quite. Speed isn't the difference.
◉ Because 0 is a real index, and a caller can't tell "not found" from a match at position 0.
→ Yes. The flag keeps the missing case separate from every valid value.
○ Because the flag takes less memory than an int.
→ Not quite. The flag adds memory, and its purpose is clarity, not size.
````
