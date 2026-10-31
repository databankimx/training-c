#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    errno = 0;
    FILE *file = fopen("data/missing.txt", "r");
    if (file == NULL) {
        switch (errno) {
            case ENOENT:
                printf("The file doesn't exist.\n");
                break;
            case EACCES:
                printf("Permission denied.\n");
                break;
            default:
                printf("Could not open the file: %s\n", strerror(errno));
                break;
        }
        printf("Error code: %d\n", errno);
        return 1;
    }

    fclose(file);
    printf("The file opened.\n");
    return 0;
}
