#include <stdio.h>

void introduce(const char *fname, int age) {
    printf("%s is %d years old.\n", fname, age);
}

void add_one(int value) {
    value = value + 1;
    printf("Inside add_one: %d\n", value);
}

int main(void) {
    introduce("Scott", 53);

    int number = 10;
    add_one(number);
    printf("After the call: %d\n", number);

    // Try: call introduce with the arguments in the wrong order, and read the compiler's message before you press Run.
    return 0;
}
