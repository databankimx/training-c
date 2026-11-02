#include <stdio.h>
#include <windows.h>

int main(void) {
    CreateDirectoryA("data", NULL);

    FILE *out = fopen("data/test.txt", "w");
    fprintf(out, "This first version of the text is quite long.");
    fclose(out);

    FILE *file = fopen("data/test.txt", "r+");
    fprintf(file, "Short text.");
    fclose(file);

    FILE *in = fopen("data/test.txt", "r");
    char line[256];
    if (fgets(line, sizeof line, in) != NULL) {
        printf("%s\n", line);
    }
    fclose(in);

    // Try: change "r+" to "w+", and predict the output before you press Run.
    return 0;
}
