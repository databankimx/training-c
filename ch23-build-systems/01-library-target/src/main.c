#include <stdio.h>

#include "greeting.h"

int main(void) {
    char text[64];

    if (make_greeting("Scott", text, sizeof text) == 0) {
        printf("%s\n", text);
    }
    if (make_greeting("Ada", text, sizeof text) == 0) {
        printf("%s\n", text);
    }

    // Try: add a third call to make_greeting for a name of your choice, and predict its output before you press Run.
    return 0;
}
