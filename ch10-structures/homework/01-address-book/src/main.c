#include <stdio.h>
#include <string.h>

typedef struct {
    char name[16];
    char phone[16];
} Contact;

int main(void) {
    Contact contacts[3] = {
        {"Ada", "555-0101"},
        {"Grace", "555-0102"},
        {"Alan", "555-0103"}
    };
    size_t count = sizeof contacts / sizeof contacts[0];

    char query[32];
    printf("Enter a name: ");
    fflush(stdout);
    if (fgets(query, sizeof query, stdin) == NULL) {
        return 1;
    }
    query[strcspn(query, "\n")] = '\0';

    int found = 0;
    for (size_t i = 0; i < count; i++) {
        if (_stricmp(contacts[i].name, query) == 0) {
            printf("%s: %s\n", contacts[i].name, contacts[i].phone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No contact named %s.\n", query);
    }
    return 0;
}
