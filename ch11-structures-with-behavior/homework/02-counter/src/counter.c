#include "counter.h"

#include <stdlib.h>

struct Counter {
    int count;
    int start;
};

Counter *counter_create(int start) {
    Counter *counter = malloc(sizeof *counter);
    if (counter == NULL) {
        return NULL;
    }
    counter->start = start;
    counter->count = start;
    return counter;
}

void counter_destroy(Counter *counter) {
    free(counter);
}

void counter_increment(Counter *counter) {
    counter->count++;
}

void counter_reset(Counter *counter) {
    counter->count = 0;
}

int counter_value(const Counter *counter) {
    return counter->count;
}
