## Walkthrough: Ownership handoff

`consume` receives the address of the caller's pointer, which lets it take the resource and clear the caller's copy in one step. Once the function has the resource, the caller's pointer is `NULL`, so the caller can't release it again. The function is now the only owner, and it releases the resource before it returns, which is why `Release handoff` prints before `Back in main`.

The `NULL` check at the top of `consume` makes a second call safe. The check runs before any use, and it finds that nothing is left to receive. Without it, the second call would read a `NULL` pointer, which is undefined behavior.

For the extension that only reads the resource, the caller still owns it, so the caller must release it after the read. The function that releases a block is the one that owns it at that moment, and the comment on each function says which that is.
