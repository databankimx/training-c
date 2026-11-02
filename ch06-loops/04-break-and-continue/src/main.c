#include <stdbool.h>
#include <stdio.h>

int main(void) {
    printf("Break at 5:\n");
    int i = 0;
    while (true) {
        ++i;
        printf("%d\n", i);
        if (i == 5) {
            break;
        }
    }

    printf("Continue past 5:\n");
    for (int j = 1; j <= 10; ++j) {
        if (j <= 5) {
            continue;
        }
        printf("%d\n", j);
    }

    // Try: change the break condition from i == 5 to i == 3, and predict how many lines print before you press Run.
    return 0;
}
