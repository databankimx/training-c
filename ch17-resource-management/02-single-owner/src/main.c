#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
} Resource;

/* Creates a resource on the heap. The caller becomes its single owner, and must release it with resource_destroy.
   Returns NULL when memory runs out. */
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

static void resource_describe(const Resource *resource) {
    printf("Holding %s\n", resource->name);
}

/* Releases the resource. After this call the pointer must not be used, so the caller should set it to NULL. */
static void resource_destroy(Resource *resource) {
    printf("Release %s\n", resource->name);
    free(resource);
}

int main(void) {
    printf("Start\n");
    {
        Resource *owner = resource_create("file C");
        if (owner == NULL) {
            printf("Out of memory.\n");
            return 1;
        }
        resource_describe(owner);
        printf("Using file C\n");
        resource_destroy(owner);
        owner = NULL;
    }
    printf("After the block\n");

    /* Try: delete the line owner = NULL;, add a second resource_destroy(owner); after the first, and predict the result before you press Run.
       That is a double free: the block was already released, so the program may crash or corrupt its heap. */
    return 0;
}
