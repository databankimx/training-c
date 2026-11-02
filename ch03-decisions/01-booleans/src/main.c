#include <stdbool.h>
#include <stdio.h>

int main(void) {
    bool is_coding_fun = true;
    bool is_fish_tasty = false;

    printf("Without words:\n");
    printf("is_coding_fun: %d\n", is_coding_fun);
    printf("is_fish_tasty: %d\n", is_fish_tasty);

    printf("With words:\n");
    printf("is_coding_fun: %s\n", is_coding_fun ? "true" : "false");
    printf("is_fish_tasty: %s\n", is_fish_tasty ? "true" : "false");

    int x = 10;
    int y = 9;
    printf("x == 10: %s\n", x == 10 ? "true" : "false");
    printf("x != y: %s\n", x != y ? "true" : "false");
    printf("x > y: %s\n", x > y ? "true" : "false");
    printf("x < y: %s\n", x < y ? "true" : "false");
    printf("x >= 10: %s\n", x >= 10 ? "true" : "false");
    printf("y <= 8: %s\n", y <= 8 ? "true" : "false");

    double ratio = 9.5;
    printf("ratio > 9: %s\n", ratio > 9 ? "true" : "false");

    // Try: change y to 10, and predict x == y and x < y before you press Run.
    return 0;
}
