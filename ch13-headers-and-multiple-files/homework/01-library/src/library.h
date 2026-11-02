#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"

#define LIBRARY_CAPACITY 3

typedef struct {
    Book books[LIBRARY_CAPACITY];
    int count;
} Library;

void library_init(Library *library);

/* Stores a copy of the book if there's room. Returns 0 when stored, or -1 when the library is full. */
int library_add(Library *library, const Book *book);

void library_print_all(const Library *library);

#endif /* LIBRARY_H */
