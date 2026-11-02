## Homework: Library

Write a small library program split across files: a `Book` structure in its own header and source, a `Library` structure in its own header and source, and a `main.c` that uses them.

The program should:

* in `book.h` and `book.c`, define a `Book` structure with a title and a checked-out flag, a `book_init` function that sets the title, a `book_check_out` function that marks the book as checked out, and a `book_print` function that prints `Dune - available` or `Dune - checked out`
* in `library.h` and `library.c`, define a `Library` structure that holds up to three books in an array, with a `library_add` function that stores a copy of a `Book` if there's room, and a `library_print_all` function that prints every book it holds
* use include guards in both headers, and don't define any functions in a header
* in `main.c`, create a library, create the books `Dune` and `Emma`, check out `Emma` before adding it to the library, and call `library_print_all`. `library_add` stores a copy, so a checkout made after adding doesn't reach the library's copy.

### What to check

The output should be:

```
Dune - available
Emma - checked out
```

Check the file list in the step's CMake file. Every `.c` file the program uses must appear in `add_executable`, or the link fails.

### Extensions

* Make `library_add` refuse a fourth book, and print a message when the library is full. Decide whether the message belongs in `library_add` or in `main`, and say why.
* Add a `library_count` function that returns the number of books, and print it after the books are added.

---

*This exercise is not from the book. It practices the ideas in Chapter 13.*
