#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* Takes ownership of the resource, which the caller has given up. The function releases it before it returns,
   and sets the caller's pointer to NULL, so the caller can't use or release it again. */
static void consume(Resource **owner) {
    if (*owner == NULL) {
        printf("Nothing to receive.\n");
        return;
    }
    Resource *resource = *owner;
    *owner = NULL;
    printf("Received %s\n", resource->name);
    resource_destroy(resource);
}

int main(void) {
    Resource *handoff = resource_create("handoff");
    if (handoff == NULL) {
        printf("Out of memory.\n");
        return 1;
    }

    consume(&handoff);
    printf("Back in main\n");
    printf("End\n");

    /* Try: add a second consume(&handoff); after the first, and predict the output. The pointer is NULL by then, so the check in consume prints a message instead of releasing anything. */
    return 0;
}
