## Homework: Second library

Add a second library, `mathutil`, to a program. The library provides one function, and the program uses it. The exercise is about the build: the program and the library must each be a target, and the program must link the library.

The program should:

* write `mathutil.h` and `mathutil.c` in `src`, declaring and defining `int square(int value)`, which returns the value times itself
* declare `mathutil` as a static library target in `CMakeLists.txt`, with its include folder shared publicly
* in `main.c`, print `Square of 7: ` followed by `square(7)`, and `Square of 12: ` followed by `square(12)`
* link `mathutil` to the `program` target

### What to check

The output should be:

```
Square of 7: 49
Square of 12: 144
```

If the link fails with an undefined reference to `square`, the library isn't linked to the program, or its source isn't in the library's `add_library` line. Check both lines in `CMakeLists.txt`.

### Extensions

* Add a function `cube` to the same library. Explain why no change to `CMakeLists.txt` is needed.
* Make the library's target `PRIVATE` for its include folder, and predict whether `main.c` still compiles. Then explain why it fails, and what that tells you about PUBLIC.

---

*This exercise is not from the book. It practices the ideas in Chapter 23.*
