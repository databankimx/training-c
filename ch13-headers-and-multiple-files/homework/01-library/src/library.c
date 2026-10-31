#include "library.h"

#include <stdio.h>

void library_init(Library *library) {
    library->count = 0;
}

int library_add(Library *library, const Book *book) {
    if (library->count >= LIBRARY_CAPACITY) {
        return -1;
    }
    library->books[library->count] = *book;
    library->count++;
    return 0;
}

void library_print_all(const Library *library) {
    for (int i = 0; i < library->count; i++) {
        book_print(&library->books[i]);
    }
}
