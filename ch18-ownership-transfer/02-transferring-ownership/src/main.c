#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
} Resource;

/* Creates a resource. The caller owns it, and must release it with resource_destroy. Returns NULL when memory runs out. */
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

/* Transfers ownership. The destination takes the pointer, and the source is set to NULL so it owns nothing.
   Only one of the two can release the resource afterwards. */
static void transfer_ownership(Resource **destination, Resource **source) {
    *destination = *source;
    *source = NULL;
}

int main(void) {
    printf("Start\n");
    {
        Resource *a = resource_create("file E");
        if (a == NULL) {
            printf("Out of memory.\n");
            return 1;
        }

        Resource *b = NULL;
        transfer_ownership(&b, &a);

        printf("a owns nothing: %s\n", a == NULL ? "yes" : "no");
        printf("b owns the resource: %s\n", b != NULL ? "yes" : "no");
        printf("End\n");

        resource_destroy(b);
        b = NULL;
    }

    // Try: replace transfer_ownership(&b, &a); with b = a;, and predict whether a still owns the resource. Then add resource_destroy(a); before the block ends, and predict the result. That releases the same block twice, a double free.
    return 0;
}
