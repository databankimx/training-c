#include <stdio.h>

int main(void) {
    int speeds[4] = {60, 75, 80, 90};
    int nums[3] = {10, 20, 30};

    printf("%d\n", speeds[0]);
    printf("%d\n", nums[2]);

    speeds[0] = 55;
    nums[2] += 5;
    printf("%d\n", speeds[0]);
    printf("%d\n", nums[2]);

    // Try: set int index = 4, print speeds[index], and predict the result before you press Run.
    return 0;
}
