#include <stdbool.h>
#include <stdio.h>

int main(void) {
    bool x = true;
    bool y = false;

    printf("x && y: %s\n", (x && y) ? "true" : "false");
    printf("x || y: %s\n", (x || y) ? "true" : "false");
    printf("!x: %s\n", !x ? "true" : "false");

    int age = 25;
    bool has_ticket = false;
    printf("Adult and has ticket: %s\n", (age >= 18 && has_ticket) ? "true" : "false");
    printf("Adult or has ticket: %s\n", (age >= 18 || has_ticket) ? "true" : "false");

    int count = 0;
    bool ok = (count != 0) && (10 / count > 1);
    printf("Safe check: %s\n", ok ? "true" : "false");

    bool p = true;
    bool q = false;

    bool my_xor = (p || q) && !(p && q); // example explaining the logic
    printf("(p || q) && !(p && q): %s\n", my_xor ? "true" : "false");

    my_xor = p != q; // simple example with less obvious logic
    printf("p != q: %s\n", my_xor ? "true" : "false");

    // Try: change p and q to both be true, and predict both XOR lines before you press Run.
    return 0;
}
