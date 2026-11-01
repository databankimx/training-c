#include "greeting.h"

#include <stdio.h>

int make_greeting(const char *name, char *out, size_t size) {
    int written = snprintf(out, size, "Hello, %s!", name);
    if (written < 0 || (size_t)written >= size) {
        return -1;
    }
    return 0;
}
