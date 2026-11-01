#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOLDERS 4

typedef struct {
    char name[32];
} Resource;

static Resource *resource_create(const char *name) {
    Resource *resource = malloc(sizeof *resource);
    if (resource == NULL) {
        return NULL;
    }
    /* UNSAFE PATH: strcpy does not check sizes. name must be at most 31 characters. */
    strcpy(resource->name, name);
    printf("Acquire %s\n", resource->name);
    return resource;
}

static void resource_destroy(Resource *resource) {
    printf("Release %s\n", resource->name);
    free(resource);
}

/* Transfers ownership from source to destination, and clears the source. */
static void transfer(Resource **destination, Resource **source) {
    *destination = *source;
    *source = NULL;
}

int main(void) {
    Resource *p = resource_create("vessel");
    if (p == NULL) {
        printf("Out of memory.\n");
        return 1;
    }

    /* holders is a fixed array of owning pointers, with a count of the slots in use. */
    Resource *holders[MAX_HOLDERS] = {NULL};
    size_t holder_count = 0;

    transfer(&holders[holder_count++], &p);
    printf("Size after push: %zu\n", holder_count);
    printf("p owns nothing: %s\n", p == NULL ? "yes" : "no");

    Resource *back = NULL;
    transfer(&back, &holders[0]);
    holder_count--;
    printf("Got back: %s\n", back != NULL ? "yes" : "no");

    printf("End\n");
    resource_destroy(back);
    back = NULL;

    // Try: move two resources into holders, and predict the release order before you press Run. Release only the slots you still own.
    return 0;
}
