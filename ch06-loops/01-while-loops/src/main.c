#include <stdio.h>

int main(void) {
    printf("while loop:\n");
    int i = 0;
    while (i < 3) {
        printf("%d\n", ++i);
    }

    printf("do-while loop:\n");
    int j = 10;
    do {
        printf("j is %d\n", j);
        j++;
    } while (j < 10);

    // Try: change the do-while condition to j < 12, and predict the output before you press Run.
    return 0;
}
