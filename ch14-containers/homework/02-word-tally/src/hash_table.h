#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

/* Entries whose keys hash to the same bucket are chained together in a list. */
typedef struct {
    Entry **buckets;
    size_t bucket_count;
    size_t size;
} HashTable;

int hash_table_init(HashTable *table, size_t bucket_count);
void hash_table_free(HashTable *table);

/* Adds one to the value for key, creating the entry with 0 first if it's missing. Returns 0, or -1 when memory runs out. */
int hash_table_increment(HashTable *table, const char *key);

/* Stores the value for key in *out. Returns 0 when found, or -1 when the key is missing. Never adds an entry. */
int hash_table_get(const HashTable *table, const char *key, int *out);

#endif /* HASH_TABLE_H */
