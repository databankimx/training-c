#include "book.h"

#include <stdio.h>
#include <string.h>

void book_init(Book *book, const char *title) {
    /* UNSAFE PATH: strcpy does not check sizes. title must be at most 31 characters. */
    strcpy(book->title, title);
    book->checked_out = 0;
}

void book_check_out(Book *book) {
    book->checked_out = 1;
}

void book_print(const Book *book) {
    printf("%s - %s\n", book->title, book->checked_out ? "checked out" : "available");
}
