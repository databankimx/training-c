#ifndef COUNTER_H
#define COUNTER_H

typedef struct Counter Counter;

Counter *counter_create(int start);
void counter_destroy(Counter *counter);

void counter_increment(Counter *counter);
void counter_reset(Counter *counter);
int counter_value(const Counter *counter);

#endif /* COUNTER_H */
