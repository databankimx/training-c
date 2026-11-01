#include <stdio.h>
#include <string.h>

typedef struct {
    char text[32];
} Buffer;

static void buffer_create(Buffer *buffer, const char *text) {
    /* UNSAFE PATH: strcpy does not check sizes. text must be at most 31 characters. */
    strcpy(buffer->text, text);
    printf("Construct %s\n", buffer->text);
}

/* A copy makes a second, independent buffer. The source keeps its text. */
static void buffer_copy(Buffer *destination, const Buffer *source) {
    strcpy(destination->text, source->text);
    printf("Copy %s\n", destination->text);
}

/* A move hands the text over. The source is cleared, so it is valid to destroy but holds nothing. */
static void buffer_move(Buffer *destination, Buffer *source) {
    memcpy(destination, source, sizeof *destination);
    printf("Move %s\n", destination->text);
    source->text[0] = '\0';
}

/* C has no destructors, so this call is written where the C++ destructor would have run. */
static void buffer_destroy(const Buffer *buffer) {
    printf("Destroy %s\n", buffer->text);
}

int main(void) {
    Buffer a;
    buffer_create(&a, "alpha");

    Buffer b;
    buffer_copy(&b, &a);

    Buffer c;
    buffer_move(&c, &a);

    printf("All three objects are still valid to use.\n");

    /* Destroy in reverse order of creation, as the C++ objects are. */
    buffer_destroy(&c);
    buffer_destroy(&b);
    buffer_destroy(&a);

    // Try: add buffer_move(&d, &c) with a new Buffer d before the message, and predict the output before you press Run.
    return 0;
}
