#include <stdio.h>

void greet(void);

int main(void) {
    printf("Before the calls\n");
    greet();
    greet();
    printf("After the calls\n");
    return 0;
}

void greet(void) {
    printf("I just got executed!\n");
}
