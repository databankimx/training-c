#include <stdio.h>
#include <string.h>

int main(void) {
    char name[64];

    printf("Who is the card for? ");
    fflush(stdout);
    if (fgets(name, sizeof name, stdin) == NULL) {
        return 1;
    }
    name[strcspn(name, "\n")] = '\0';

    printf("Happy birthday, %s!\n", name);
    printf("That's %zu letters.\n", strlen(name));
    return 0;
}
