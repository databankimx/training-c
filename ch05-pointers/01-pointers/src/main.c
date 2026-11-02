#include <stdio.h>

int main(void) {
    int servings = 4;
    int *ptr = &servings;

    printf("%d\n", servings);
    printf("%d\n", *ptr);

    *ptr = 6;
    printf("%d\n", servings);

    int *empty = NULL;
    if (empty == NULL) {
        printf("The pointer is empty.\n");
    }

    // Try: set *ptr to 9, and predict what servings shows before you press Run.
    return 0;
}
