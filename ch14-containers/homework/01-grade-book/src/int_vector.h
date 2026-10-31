#ifndef INT_VECTOR_H
#define INT_VECTOR_H

#include <stddef.h>

/* A growable list of ints. The items live in one block of memory, and capacity is how many fit before the next growth. */
typedef struct {
    int *items;
    size_t size;
    size_t capacity;
} IntVector;

void int_vector_init(IntVector *vector);
void int_vector_free(IntVector *vector);

/* Returns 0 when the value is added, or -1 when memory runs out. */
int int_vector_push(IntVector *vector, int value);

/* Stores the element at index in *out. Returns 0, or -1 when the index is out of range. */
int int_vector_at(const IntVector *vector, size_t index, int *out);

#endif /* INT_VECTOR_H */
