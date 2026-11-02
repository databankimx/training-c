#include <stdio.h>

int main(void) {
    int day = 3;
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        default:
            printf("Not a workday\n");
            break;
    }

    char grade = 'B';
    switch (grade) {
        case 'A':
            printf("Excellent\n");
            break;
        case 'B':
        case 'C':
            printf("Good\n");
            break;
        default:
            printf("Keep going\n");
            break;
    }

    int level = 1;
    switch (level) {
        case 1:
            printf("Level 1 tasks\n");
            /* fall through */
        case 2:
            printf("Level 2 tasks\n");
            break;
    }

    // Try: change level to 2, and predict how many lines the last switch prints before you press Run.
    return 0;
}
