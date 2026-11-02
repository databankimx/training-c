#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // argc counts every word on the command line, including the program's own name. argv[0] is that name,
    // so the first real argument is argv[1].
    printf("Arguments received: %d\n", argc - 1);
    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    // Two numbers, given on the command line, are added. The text is converted with strtol.
    if (argc == 3) {
        int first = (int)strtol(argv[1], NULL, 10);
        int second = (int)strtol(argv[2], NULL, 10);
        printf("%d + %d = %d\n", first, second, first + second);
    } else {
        printf("Give two numbers, for example: program 4 9\n");
    }

    // Try: run with the arguments 4 nine, and predict the last line. Then run with no arguments at all.
    return 0;
}
