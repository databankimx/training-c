## Cleanup on every exit

A function that holds a resource has to give it back, whichever way the function leaves. The resource might be a block of heap memory, an open file, or a lock. In C++, an object's destructor runs when the object goes out of scope, so the release happens automatically on every exit. That pattern is called RAII, for resource acquisition is initialization. C has no destructors, so the release has to be written in the function, and the error-handling chapter introduced the way to do it: a cleanup block at the end of the function, reached by `goto`.

Here's the function for this step, in `src/main.c`. It allocates two blocks, and it can leave by three routes:

```c
static int run_task(int fail_at, int *released) {
    int result = -1;
    char *first = NULL;
    char *second = NULL;

    first = malloc(16);
    if (first == NULL) {
        goto done;
    }
    if (fail_at == 1) {
        goto cleanup_first;
    }

    second = malloc(32);
    if (second == NULL) {
        goto cleanup_first;
    }
    if (fail_at == 2) {
        goto cleanup_second;
    }

    result = 0;

cleanup_second:
    free(second);
    (*released)++;
cleanup_first:
    free(first);
    (*released)++;
done:
    return result;
}
```

Press **Run**. The output is:

```
fail_at 0: result 0, blocks released 2
fail_at 1: result -1, blocks released 1
fail_at 2: result -1, blocks released 2
```

The success route sets `result` to 0 and falls through both cleanup steps. The route that fails after the first allocation jumps to `cleanup_first`, and frees only the block that exists. The route that fails after the second allocation jumps to `cleanup_second`, and frees the second block and then falls through to free the first.

### Why the labels go in reverse order

The cleanup labels are in the reverse order of the allocations. The block allocated last is released first, and each label releases what the labels below it still need. A route that stops partway jumps to the label for the last thing it got, and the code falls through to release everything earlier. That's the same structure as the copy function in the error-handling chapter, and it's the reason no route releases a block that was never allocated.

### What the count shows

Every route releases each block exactly once. The `released` counter goes up once for each `free`, so the printed counts show the cleanup working. A block that's released twice would push the count over, and a block that's never released would leave it short. Adding a counter like this to a function is a simple way to check that every route cleans up.

### What RAII adds

In C++, a destructor makes the release happen when the object's scope ends, so no route can forget it. The C version relies on the programmer to write every route into the cleanup block. The labels make that manageable, but the discipline is the same: each allocation needs one matching release, on every path. The next steps show how to decide who that release belongs to.

---

### Quiz

*These questions are written for this course.*

````quiz
Why do the cleanup labels go in the reverse order of the allocations?
○ Because free must be called in the same order as malloc.
→ Not quite. The order isn't a rule of free, and the labels are arranged so that each route falls through the right releases.
◉ Because each route jumps to the label for the last block it got, and falls through to release the earlier blocks.
→ Yes. The labels form a chain, so a route that stops early releases only what it holds.
○ Because the labels must be in alphabetical order for goto to work.
→ Not quite. goto jumps to any label in the function, and the order matters for the fall-through, not for the names.
````

````quiz
On the route that fails after the first allocation, which block is released?
○ The first block, only.
→ Yes. The second block was never allocated, so it isn't freed, and the route jumps past its release.
○ The second block, only.
→ Not quite. The second block was never allocated on this route.
○ Both blocks.
→ Not quite. Releasing the second block on this route would free a block that doesn't exist.
````

---

### Try it in the runner

Move the `free(first);` line above the `cleanup_second` label, so it sits just before the label. Predict the `fail_at 2` output before you press **Run**. The route that fails after the second allocation now jumps to `cleanup_second`, which is below the release of `first`, so it skips that release. The output is `blocks released 1`, and the first block is leaked. The move shows why the labels must stay in the order they are: a route that jumps into the middle of the chain misses every release above the label it jumps to. Restore the original order before you continue.

---

A cleanup block gives each route a place to release what it holds. The next step asks who owns a block, since a clear owner is what decides who releases it.
