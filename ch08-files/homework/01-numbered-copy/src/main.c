#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *in = fopen("data/input.txt", "r");
    if (in == NULL) {
        printf("Could not open data/input.txt\n");
        return 1;
    }

    FILE *out = fopen("data/numbered.txt", "w");
    if (out == NULL) {
        printf("Could not open data/numbered.txt\n");
        fclose(in);
        return 1;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof line, in) != NULL) {
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        count++;
        fprintf(out, "%d. %s\n", count, line);
    }

    fclose(in);
    fclose(out);
    printf("Wrote %d lines to data/numbered.txt\n", count);
    return 0;
}
