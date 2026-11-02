## Walkthrough: Library

Each module has one header and one source file. The headers declare the types and functions, and the sources define them. `main.c` includes both headers, and the build links the three source files into one program.

`library_add` copies the book with a plain structure assignment, `library->books[library->count] = *book;`. The library's copy is separate from the book in `main`, so checking out `Emma` after adding it would not change the library's copy. In this exercise `Emma` is checked out before it's added, so the library holds it as checked out.

The library's array has room for three books, and `library_add` returns -1 when it's full. Putting the message in `main` keeps the library free of printing decisions, which is the reason the function returns a code.

The headers have guards, and they include `book.h` only where the library's declarations need the `Book` type. Each `.c` file includes its own header, so the compiler checks each definition against its declaration.
