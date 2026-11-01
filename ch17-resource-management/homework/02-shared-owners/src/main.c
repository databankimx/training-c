#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOLDERS 4

typedef struct {
    char name[32];
    int owners;
} Resource;

static Resource *resource_create(const char *name) {
    Resource *resource = malloc(sizeof *resource);
    if (resource == NULL) {
        return NULL;
    }
    /* UNSAFE PATH: strcpy does not check sizes. name must be at most 31 characters. */
    strcpy(resource->name, name);
    resource->owners = 1;
    printf("Acquire %s\n", resource->name);
    return resource;
}

static Resource *resource_retain(Resource *resource) {
    resource->owners++;
    return resource;
}

static void resource_release(Resource *resource) {
    resource->owners--;
    if (resource->owners == 0) {
        printf("Release %s\n", resource->name);
        free(resource);
    }
}

int main(void) {
    Resource *original = resource_create("shared");
    if (original == NULL) {
        printf("Out of memory.\n");
        return 1;
    }

    /* holders stores owners as well. Each entry is one retain, and clearing releases every entry. */
    Resource *holders[MAX_HOLDERS];
    size_t holder_count = 0;

    holders[holder_count++] = resource_retain(original);
    printf("Owners: %d\n", original->owners);

    holders[holder_count++] = resource_retain(original);
    printf("Owners: %d\n", original->owners);

    for (size_t i = 0; i < holder_count; i++) {
        resource_release(holders[i]);
        holders[i] = NULL;
    }
    holder_count = 0;
    printf("Owners: %d\n", original->owners);

    printf("End\n");
    resource_release(original);
    original = NULL;

    // Try: add a second Resource named "other", and show that its owner count changes separately from the first.
    return 0;
}
