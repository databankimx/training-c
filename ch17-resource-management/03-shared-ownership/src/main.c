#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A resource with a count of its owners. Every owner holds the same pointer, and the count says how many there are. */
typedef struct {
    char name[32];
    int owners;
} SharedResource;

/* Creates a resource with one owner: the caller. Returns NULL when memory runs out. */
static SharedResource *shared_create(const char *name) {
    SharedResource *resource = malloc(sizeof *resource);
    if (resource == NULL) {
        return NULL;
    }
    /* UNSAFE PATH: strcpy does not check sizes. name must be at most 31 characters. */
    strcpy(resource->name, name);
    resource->owners = 1;
    printf("Acquire %s\n", resource->name);
    return resource;
}

/* Adds an owner. Each owner must call shared_release exactly once. */
static SharedResource *shared_retain(SharedResource *resource) {
    resource->owners++;
    return resource;
}

/* Removes one owner. The last owner to release frees the resource, and it must not be used afterwards. */
static void shared_release(SharedResource *resource) {
    resource->owners--;
    if (resource->owners == 0) {
        printf("Release %s\n", resource->name);
        free(resource);
    }
}

static int shared_owner_count(const SharedResource *resource) {
    return resource->owners;
}

int main(void) {
    SharedResource *first = shared_create("file D");
    if (first == NULL) {
        printf("Out of memory.\n");
        return 1;
    }
    printf("Owners: %d\n", shared_owner_count(first));

    {
        SharedResource *second = shared_retain(first);
        printf("Owners: %d\n", shared_owner_count(second));
        shared_release(second);
        second = NULL;
    }

    printf("Owners: %d\n", shared_owner_count(first));
    printf("End\n");
    shared_release(first);
    first = NULL;

    /* Try: delete the line first = NULL;, call shared_release(first) a second time after the first, and predict the result before you press Run.
       The count is already zero when the second call runs, so the block is released twice: a double free. */
    return 0;
}
