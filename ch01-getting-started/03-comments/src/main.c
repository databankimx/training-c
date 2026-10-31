#include <stdio.h>

/* A block comment can run over
   several lines. The compiler skips all of it. */
int main(void) {
    // A line comment runs to the end of the line.
    printf("Comments are not part of the program.\n"); /* A comment can sit after code. */
    return 0;
}
