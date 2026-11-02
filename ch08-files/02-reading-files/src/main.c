#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *in = fopen("data/notes.txt", "r");
    if (in == NULL) {
        printf("Could not open data/notes.txt\n");
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
        printf("%d: %s\n", count, line);
    }
    fclose(in);

    printf("Lines read: %d\n", count);

    // Try: count words instead of lines, using fscanf with "%255s", and predict the count for the three notes first.
    return 0;
}
