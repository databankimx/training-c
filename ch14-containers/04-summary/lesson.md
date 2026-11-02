## Summary: Containers

This chapter covered how C programs store collections of values: growable lists, hash tables for lookups by key, and the choice between them. C's standard library has none of these containers, so the chapter builds them from `malloc`.

* **A vector grows as you add to it.** `int_vector_push` adds an element, the size is in the `size` field, and the vector keeps its order.
* **`int_vector_at` checks the index.** It returns -1 for a bad index, where a raw read past the end is undefined behavior.
* **A hash table finds values by key.** `hash_table_get` reads a value and never adds an entry, and `hash_table_set` and `hash_table_increment` store or count one.
* **A hash table has no order.** Its entries are visited bucket by bucket, so output that must be stable needs sorting first.
* **A sorted array trades writes for reads.** Sorting once with `qsort` lets `bsearch` find keys quickly, which suits data that's read far more than it's written.
* **Every container owns its memory.** Each `malloc` in a container needs a matching `free`, and the container's free function releases everything it allocated.
* **Choose by the main job.** Use an array for a fixed size, a vector for an ordered list, and a hash table for lookups by key.
* **Containers can be combined.** A program often keeps one container for order and another for lookups.

### Check your understanding

*These questions are written for this course.*

````quiz
Which function checks whether a key is in a hash table, without adding it?
○ hash_table_set
→ Not quite. set stores a value, adding the entry if it's missing.
◉ hash_table_get
→ Yes. get returns -1 when the key is missing, and never adds an entry.
○ hash_table_increment
→ Not quite. increment adds an entry if it's missing, so it changes the table.
````

````quiz
Why does a loop over a hash table not produce a fixed order?
○ Because the table is sorted at random.
→ Not quite. The table isn't sorted at all.
◉ Because entries are placed in buckets chosen by their hash, and the bucket order is not defined.
→ Yes. The order depends on the hash function and the number of buckets, so it isn't a promise.
○ Because the entries are freed in a random order.
→ Not quite. The order of freeing has nothing to do with the order of a loop.
````

````quiz
Why does a checked read, such as `int_vector_at`, matter when the index comes from user input?
○ Because unchecked reads are slower.
→ Not quite. The reason is safety, not speed.
◉ Because a read past the end of the block is undefined behavior, and the check turns it into an error the program can handle.
→ Yes. The check happens before the read, so a bad index never reaches the memory.
○ Because the vector refuses to hold values from users.
→ Not quite. The vector holds any value, and the check is about the index.
````
