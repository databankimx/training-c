#ifndef GREETING_H
#define GREETING_H

#include <stddef.h>

/* Writes "Hello, <name>!" into out, which must have room for size bytes. Returns 0, or -1 when the text does not fit. */
int make_greeting(const char *name, char *out, size_t size);

#endif /* GREETING_H */
