#include <stdio.h>
#include <string.h>

int main(void) {
    const char *food = "Pizza";
    printf("%s\n", food);
    printf("First: %c\n", *food);
    printf("Third: %c\n", food[2]);
    printf("Length: %zu\n", strlen(food));

    char name[] = "Ada";
    char *copy = name;
    copy[0] = 'E';
    printf("%s\n", name);

    const char *colors[3] = {"red", "green", "blue"};
    for (size_t i = 0; i < 3; i++) {
        printf("%s\n", colors[i]);
    }

    // Try: change food to point at "Salad", and predict the Third line before you press Run.
    return 0;
}
