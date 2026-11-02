#include <stdio.h>

#include "book.h"
#include "library.h"

int main(void) {
    Library library;
    library_init(&library);

    Book dune;
    book_init(&dune, "Dune");

    Book emma;
    book_init(&emma, "Emma");
    book_check_out(&emma);

    library_add(&library, &dune);
    library_add(&library, &emma);
    library_print_all(&library);

    return 0;
}
