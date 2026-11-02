#include <stdio.h>
#include <string.h>
#include <windows.h>

#define PATH_BUFFER 1024

void list_folder(const char *folder, int depth) {
    char pattern[PATH_BUFFER];
    if (strlen(folder) + 3 > sizeof pattern) {
        printf("Path too long: %s\n", folder);
        return;
    }
    strcpy(pattern, folder);
    strcat(pattern, "\\*");

    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA(pattern, &data);
    if (find == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) {
            continue;
        }
        printf("%*s%s\n", depth * 2, "", data.cFileName);

        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            char child[PATH_BUFFER];
            if (strlen(folder) + strlen(data.cFileName) + 2 > sizeof child) {
                printf("Path too long: %s\\%s\n", folder, data.cFileName);
                continue;
            }
            strcpy(child, folder);
            strcat(child, "\\");
            strcat(child, data.cFileName);
            list_folder(child, depth + 1);
        }
    } while (FindNextFileA(find, &data));

    FindClose(find);
}

int main(void) {
    list_folder("sample", 0);

    // Try: rename notes.txt to trip.txt in the sample folder, and predict where it appears in the listing.
    return 0;
}
