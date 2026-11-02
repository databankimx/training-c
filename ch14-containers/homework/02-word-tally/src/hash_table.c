#include "hash_table.h"

#include <stdlib.h>
#include <string.h>

/* The djb2 hash: a simple function that turns a string into a number. */
static unsigned long hash_string(const char *text) {
    unsigned long hash = 5381;
    for (const char *p = text; *p != '\0'; p++) {
        hash = hash * 33 + (unsigned char)*p;
    }
    return hash;
}

int hash_table_init(HashTable *table, size_t bucket_count) {
    table->buckets = calloc(bucket_count, sizeof *table->buckets);
    if (table->buckets == NULL) {
        return -1;
    }
    table->bucket_count = bucket_count;
    table->size = 0;
    return 0;
}

void hash_table_free(HashTable *table) {
    for (size_t i = 0; i < table->bucket_count; i++) {
        Entry *entry = table->buckets[i];
        while (entry != NULL) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(table->buckets);
    table->buckets = NULL;
    table->bucket_count = 0;
    table->size = 0;
}

static Entry *find_entry(const HashTable *table, const char *key) {
    size_t index = hash_string(key) % table->bucket_count;
    for (Entry *entry = table->buckets[index]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            return entry;
        }
    }
    return NULL;
}

int hash_table_increment(HashTable *table, const char *key) {
    Entry *entry = find_entry(table, key);
    if (entry != NULL) {
        entry->value++;
        return 0;
    }

    entry = malloc(sizeof *entry);
    if (entry == NULL) {
        return -1;
    }
    size_t length = strlen(key);
    entry->key = malloc(length + 1);
    if (entry->key == NULL) {
        free(entry);
        return -1;
    }
    memcpy(entry->key, key, length + 1);
    entry->value = 1;

    size_t index = hash_string(key) % table->bucket_count;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->size++;
    return 0;
}

int hash_table_get(const HashTable *table, const char *key, int *out) {
    Entry *entry = find_entry(table, key);
    if (entry == NULL) {
        return -1;
    }
    *out = entry->value;
    return 0;
}
