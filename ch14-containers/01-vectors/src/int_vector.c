#include "int_vector.h"

#include <stdlib.h>
#include <string.h>

void int_vector_init(IntVector *vector) {
    vector->items = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

void int_vector_free(IntVector *vector) {
    free(vector->items);
    vector->items = NULL;
    vector->size = 0;
    vector->capacity = 0;
}

/* Doubles the capacity, so the copies made by realloc happen rarely. */
static int grow(IntVector *vector) {
    size_t new_capacity = vector->capacity == 0 ? 4 : vector->capacity * 2;
    int *items = realloc(vector->items, new_capacity * sizeof *items);
    if (items == NULL) {
        return -1;
    }
    vector->items = items;
    vector->capacity = new_capacity;
    return 0;
}

int int_vector_push(IntVector *vector, int value) {
    if (vector->size == vector->capacity && grow(vector) != 0) {
        return -1;
    }
    vector->items[vector->size] = value;
    vector->size++;
    return 0;
}

int int_vector_pop(IntVector *vector) {
    if (vector->size == 0) {
        return -1;
    }
    vector->size--;
    return 0;
}

int int_vector_at(const IntVector *vector, size_t index, int *out) {
    if (index >= vector->size) {
        return -1;
    }
    *out = vector->items[index];
    return 0;
}

int int_vector_insert(IntVector *vector, size_t position, int value) {
    if (position > vector->size) {
        return -1;
    }
    if (vector->size == vector->capacity && grow(vector) != 0) {
        return -1;
    }
    memmove(&vector->items[position + 1], &vector->items[position],
            (vector->size - position) * sizeof *vector->items);
    vector->items[position] = value;
    vector->size++;
    return 0;
}

int int_vector_erase(IntVector *vector, size_t position) {
    if (position >= vector->size) {
        return -1;
    }
    memmove(&vector->items[position], &vector->items[position + 1],
            (vector->size - position - 1) * sizeof *vector->items);
    vector->size--;
    return 0;
}
