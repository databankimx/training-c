#include <stdio.h>

int main(void) {
    int total = 0;
    for (int number = 1; number <= 4; number++) {
        total += number;
#ifdef SHOW_STEPS_ON
        printf("Adding %d: total %d\n", number, total);
#endif
    }
    printf("Sum: %d\n", total);
    return 0;
}
