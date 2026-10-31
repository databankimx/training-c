#include <stdio.h>

int main(void) {
    int x = 20;
    int y = 10;

    if (x == y) {
        printf("x is equal to y\n");
    }
    if (x > y) {
        printf("x is greater than y\n");
    }
    if (x < y) {
        printf("x is less than y\n");
    }

    int age = 16;
    int voting_age = 18;
    if (age >= voting_age) {
        printf("You can vote!\n");
    } else {
        int wait = voting_age - age;
        printf("You will be able to vote in %d years.\n", wait);
    }

    int driver_age = 20;
    if (driver_age >= 21) {
        printf("You drive, vote, and rent a car.\n");
    } else if (driver_age >= 18) {
        printf("You can drive and vote, but you can't rent a car.\n");
    } else if (driver_age >= 16) {
        printf("You can drive, but you can't vote or rent a car.\n");
    } else {
        printf("You can't drive, vote, or rent a car.\n");
    }

    int score = 75;
    if (score >= 90) {
        printf("Excellent\n");
    } else if (score >= 70) {
        printf("Good\n");
    }

    int items = 12;
    if (items > 10) {
        printf("Chained: bulk discount\n");
    } else if (items > 5) {
        printf("Chained: free shipping\n");
    }
    if (items > 10) {
        printf("Independent: bulk discount\n");
    }
    if (items > 5) {
        printf("Independent: free shipping\n");
    }

    const char *size = (x > y) ? "large" : "small";
    printf("Size: %s\n", size);

    // Try: change driver_age to 17, and predict which message prints before you press Run.
    return 0;
}
