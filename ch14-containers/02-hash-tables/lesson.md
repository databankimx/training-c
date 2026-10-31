## Hash tables

A vector finds a value by its position. Often a program needs to find a value by a name instead: a word's count, a student's grade, or a price for an item. C's standard library has no map, so this step builds the most common kind, a hash table, from `malloc`. A hash table stores pairs, where each value is found through its key. It's the C form of the unordered map in the C++ lesson.

Here's the program for this step, in `src/main.c`. It counts the words in a list:

```c
HashTable counts;
hash_table_init(&counts, 16);

for (size_t i = 0; i < word_count; i++) {
    hash_table_increment(&counts, words[i]);
}
```

`hash_table_increment` adds one to the value for a word. When the word is new, the function creates its entry first, with the count set to one. The C++ `counts[word]++` does the same job, but C has no operator that creates entries as a side effect, so the function is written out.

Press **Run**. The output is:

```
Distinct words: 3
apple: 3
pear: 2
fig: 1
kiwi is not in the map
```

### How a lookup works

A hash table turns each key into a number with a hash function, and the number chooses a bucket. `hash_string` is the function in this program, and `hash % bucket_count` picks the bucket. Each bucket holds a linked list of entries whose keys landed there. A lookup computes the hash, goes to one bucket, and compares the key with the few entries stored there:

```c
size_t index = hash_string(key) % table->bucket_count;
for (Entry *entry = table->buckets[index]; entry != NULL; entry = entry->next) {
    if (strcmp(entry->key, key) == 0) {
        return entry;
    }
}
```

On average, the number of comparisons stays small, however many entries the table holds, as long as there are enough buckets. That's the speed the C++ lesson describes as constant time on average.

### Lookups without adding

`hash_table_get` returns the value for a key, and returns -1 if the key is missing. It never adds an entry. The program uses it for `apple`, `pear`, `fig`, and `kiwi`, so the missing key is reported without being created. This is the C form of the difference between `counts[key]`, which inserts, and `count(key)`, which doesn't.

### Memory and ownership

The table owns everything it allocates. Each entry is one `malloc`, and each key is a second `malloc`, a copy of the word, since the program's word list must not be relied on to keep its text. `hash_table_free` walks every bucket, frees each key and entry, and then frees the bucket array. The program calls it once, when it's finished with the table.

Each entry's memory follows the rules of the dynamic-memory step. The result of every `malloc` is checked, and the table is freed on every exit path. Forgetting `hash_table_free` is a leak, and freeing a key twice would be a double free, which the dynamic-memory step described as a security problem.

### What the table gives up

A hash table has no order. Its entries are visited bucket by bucket, in an order that depends on the hash function and the number of buckets. The C++ lesson warned that the order is not guaranteed, and the same holds here: the program prints the three words in a fixed order because it asks for them by name, not because the table keeps them in order. A program that needs its entries sorted has to sort them first, or keep them in a structure that stays sorted, which the next step describes.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `hash_table_get` do when the key is missing?
○ It adds the key with the value zero.
→ Not quite. That's the insert-on-read behavior of the C++ map, and this function never adds entries.
◉ It returns -1 and leaves the table unchanged.
→ Yes. The missing key is reported, and no entry is added.
○ It returns the value of the last entry in the table.
→ Not quite. A missing key is not replaced with another entry's value.
````

````quiz
What is the purpose of the bucket index in a hash table?
○ It counts how many entries are in the table.
→ Not quite. The size field does that job.
◉ It chooses which bucket to look in, so a lookup compares only a few entries.
→ Yes. The hash turns the key into a bucket number, and the search stays within one bucket.
○ It sorts the keys alphabetically.
→ Not quite. A hash table doesn't sort its keys.
````

---

### Try it in the runner

Change the bucket count from `16` to `1`, and predict whether the output changes before you press **Run**. It doesn't: every word lands in the one bucket, so the lookups compare every entry, but the output is the same. The table still works, only more slowly. A bucket count that's too small is the usual reason a hash table slows down, and the choosing step covers how to size one.

Then change `hash_table_get(&counts, "kiwi", &missing)` to `hash_table_increment(&counts, "kiwi")`, and predict whether the message still prints. It doesn't: the increment succeeds and returns 0, so the `if` is false, and the table has gained a `kiwi` entry with the value 1. Restore the `get` call before you continue.

---

A hash table finds values by key without an order, and every entry it holds must be freed. The next step compares it with the other containers, and shows how to choose.
