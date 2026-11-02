#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[32];
    int a;
    int b;

    printf("Enter a: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    a = (int)strtol(line, NULL, 10);

    printf("Enter b: ");
    fflush(stdout);
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 1;
    }
    b = (int)strtol(line, NULL, 10);

    int *pa = &a;
    int *pb = &b;

    int temp = *pa;
    *pa = *pb;
    *pb = temp;

    printf("a = %d, b = %d\n", a, b);
    return 0;
}
