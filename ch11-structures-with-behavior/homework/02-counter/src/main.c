#include <stdio.h>

#include "counter.h"

int main(void) {
    Counter *c = counter_create(0);
    counter_increment(c);
    counter_increment(c);
    counter_increment(c);
    printf("Count: %d\n", counter_value(c));

    counter_reset(c);
    printf("Count: %d\n", counter_value(c));
    counter_destroy(c);

    Counter *d = counter_create(10);
    counter_increment(d);
    printf("Count: %d\n", counter_value(d));
    counter_destroy(d);

    return 0;
}
