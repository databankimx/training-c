#include <stdio.h>

int main(void) {
    FILE *in = fopen("data/essay.txt", "r");
    if (in == NULL) {
        printf("Could not open data/essay.txt\n");
        return 1;
    }

    char line[256];
    int lines = 0;
    while (fgets(line, sizeof line, in) != NULL) {
        lines++;
    }
    fclose(in);

    in = fopen("data/essay.txt", "r");
    if (in == NULL) {
        printf("Could not open data/essay.txt\n");
        return 1;
    }

    char word[256];
    int words = 0;
    while (fscanf(in, "%255s", word) == 1) {
        words++;
    }
    fclose(in);

    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    return 0;
}
