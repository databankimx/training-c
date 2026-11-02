#ifndef BOOK_H
#define BOOK_H

typedef struct {
    char title[32];
    int checked_out;
} Book;

void book_init(Book *book, const char *title);
void book_check_out(Book *book);
void book_print(const Book *book);

#endif /* BOOK_H */
