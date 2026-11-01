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

    // Try: change the default of USE_LOUD in CMakeLists.txt from OFF to ON, and predict the output before you press Run.
    return 0;
}
