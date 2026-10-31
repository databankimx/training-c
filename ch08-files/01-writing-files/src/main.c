#include <stdio.h>
#include <windows.h>

int main(void) {
    CreateDirectoryA("data", NULL);

    FILE *out = fopen("data/greetings.txt", "w");
    if (out == NULL) {
        printf("Could not create the file.\n");
        return 1;
    }

    fprintf(out, "Hello, file!\n");
    fprintf(out, "Writing to a file works like printf.\n");
    fclose(out);

    printf("Wrote data/greetings.txt\n");

    // Try: change the path to data/missing/greetings.txt, and predict what the program prints before you press Run.
    return 0;
}
