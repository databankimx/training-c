#include "greeting.h"

#include <ctype.h>
#include <stdio.h>

int make_greeting(const char *name, char *out, size_t size) {
    int written = snprintf(out, size, "Hello, %s!", name);
    if (written < 0 || (size_t)written >= size) {
        return -1;
    }

#ifdef LOUD_GREETINGS
    /* Compiled only when the build defines LOUD_GREETINGS, so the normal build leaves this loop out. */
    for (char *p = out; *p != '\0'; p++) {
        *p = (char)toupper((unsigned char)*p);
    }
#endif

    return 0;
}
