#include <stdio.h>
#include <string.h>

int main(void) {
    char name[] = "Ada Lovelace";
    printf("Name: %s\n", name);
    printf("Length: %zu\n", strlen(name));
    printf("Bytes stored: %zu\n", sizeof name);
    printf("First letter: %c\n", name[0]);
    printf("Same as \"Ada\"? %s\n", strcmp(name, "Ada") == 0 ? "yes" : "no");

    char greeting[64];
    snprintf(greeting, sizeof greeting, "%s, %s!", "Hello", "C");
    printf("%s\n", greeting);
    printf("Length: %zu\n", strlen(greeting));
    printf("First letter: %c\n", greeting[0]);

    strcat(greeting, " Welcome.");
    printf("%s\n", greeting);

    printf("Tab:\tBackslash:\\ Quote:\"\n");

    // Try: change name to "Grace Hopper", and predict the length and the bytes stored before you press Run.
    return 0;
}
