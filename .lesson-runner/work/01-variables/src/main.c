#include <stdio.h>

int main(void) {
    int students = 24;
    double average = 87.5;
    char grade = 'B';
    const int maximum = 100;

    printf("Students: %d\n", students);
    printf("Average: %.1f\n", average);
    printf("Grade: %c\n", grade);
    printf("Out of: %d\n", maximum);

    // Try: change grade to 'A', and predict the output before you press Run.
    return 0;
}
