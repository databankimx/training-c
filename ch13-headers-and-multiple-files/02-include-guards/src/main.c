#include <stdio.h>

#include "battery.h"
#include "battery.h"

int main(void) {
    Battery battery;
    battery_init(&battery, 50, 20);
    battery_print(&battery);
    printf("\n");

    battery_recharge(&battery, 30);
    battery_print(&battery);
    printf("\n");

    battery_recharge(&battery, 100);
    battery_print(&battery);
    printf("\n");

    // Try: remove the second #include "battery.h" line, and predict whether the program still builds before you press Run.
    return 0;
}
