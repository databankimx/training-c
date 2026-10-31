#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    const char *greeting = "Headers bring in declarations";
    printf("Length: %zu\n", strlen(greeting));
    printf("Absolute value of -42: %d\n", abs(-42));
    return 0;
}
