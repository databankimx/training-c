#include <stdio.h>

int print_file(const char *name) {
    FILE *file = fopen(name, "r");
    if (file == NULL) {
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof line, file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
    return 0;
}

int main(void) {
    const char *name = "data/settings.txt";
    if (print_file(name) != 0) {
        printf("could not open %s\n", name);
        return 1;
    }
    return 0;
}
