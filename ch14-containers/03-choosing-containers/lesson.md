## Choosing a container

The last three steps introduced containers that look similar on the surface: arrays, vectors, and hash tables. Each one suits a different job. This step puts them side by side, and shows how a program often uses more than one. C's standard library has none of these containers, so the chapter's own vector and hash table are used throughout. The sorted map from the C++ chapter has no C counterpart here, and the lesson shows how sorting covers its one job.

Here's the program for this step, in `src/main.c`. It keeps the names in an array, in the order they were given, and builds a table from each name to its length:

```c
const char *names[] = {"Ada", "Grace", "Alan"};
size_t name_count = sizeof names / sizeof names[0];

HashTable lengths;
hash_table_init(&lengths, 16);
for (size_t i = 0; i < name_count; i++) {
    hash_table_set(&lengths, names[i], (int)strlen(names[i]));
}
```

Press **Run**. The output is:

```
Names: 3
Ada: 3
Alan: 4
Grace: 5
```

The array holds the names in the order they were given. The table holds the lengths, looked up by name. The printed list is sorted, and the sorting is written out in the program: a copy of the names is passed to `qsort` with `compare_names`, which uses `strcmp`. A C++ `std::map` does that sorting on every insertion. In C, the program decides when sorting happens, and only pays for it when the output needs it.

### A comparison

| Container | Size | Finds a value by | Keeps order | Use it when |
|---|---|---|---|---|
| Array | Fixed when declared | Index | The order it was written in | The size is known and never changes |
| Vector (`IntVector`) | Grows with `push` | Index | The order it was added in | You have a list, and its size isn't known in advance |
| Hash table (`HashTable`) | Grows with insertion | Key | No order is guaranteed | Lookups by key dominate, and the order doesn't matter |
| Sorted array with `qsort` and `bsearch` | Fixed after sorting | Key, by search | Sorted by key | Lookups by key, when the data is sorted once and then read |

The last row is the C counterpart of the C++ map. `bsearch` finds a key in a sorted array in a number of comparisons that grows with the logarithm of the size. The C++ map does that work on every insertion, while the sorted array does it once, which suits data that's read far more than it's written.

### What each one costs

The table says what each container is for. Its cost is the other half of the choice, and the efficiency chapter measures these figures with operation counts.

* **An array** lives in one fixed block, so reading by index is immediate and nothing is allocated after it's declared.
* **A vector** also lives in one block, so reading by index is just as fast. Adding to the end is cheap on average, as the vectors step explained. Inserting or removing in the middle means moving the elements after that point.
* **A hash table** allocates each entry separately, so the entries are spread through memory. A lookup usually goes straight to one bucket, so the average cost stays about the same as the table grows, as long as there are enough buckets. Many keys in the same bucket make a lookup slower.
* **A sorted array** costs the most to build, since it must be sorted first, and it's cheap to search afterwards.

The default is a vector. It's the simplest container that grows, and the one most code reaches for first. Move to a hash table when the main question is "what is the value for this key?", and use an array when the size is fixed and small. If the data is built once and read many times, sort it and search it.

### Several containers together

Real programs often combine containers, as this one does. The array keeps the names in input order, and the table answers questions about them. Each container does the job it's best at, and the program is clearer than one that forces a single container to do both.

### Memory across containers

Each container owns its memory, and each has a free function that the program must call. The array owns nothing, since it lives on the stack, and the table owns every key and entry it allocated. The dynamic-memory step applies to each: the table is freed once, on every exit path, and the program doesn't use it after that.

---

### Quiz

*These questions are written for this course.*

````quiz
Which container would you choose to store a list of exam scores, whose count is not known until the program runs?
○ An array, since it's the simplest.
→ Not quite. An array's size is fixed when it's declared, and this count isn't known in advance.
◉ A vector, since it grows as values are added.
→ Yes. A vector keeps the order and grows to fit the data.
○ A hash table, since it stores more information.
→ Not quite. A hash table is for lookups by key, and a list of scores doesn't need keys.
````

````quiz
Which container would you choose to find a student's grade from the student's name, when the names are added once and then looked up many times?
○ An array of names, searched from the start for each lookup.
→ Not quite. That works, but each lookup then scans the whole list.
◉ A hash table from name to grade, since lookups by key are its job.
→ Yes. The table goes straight to the right bucket for each name.
○ An array of names, with the grade at the same index.
→ Not quite. That relies on keeping two lists in step, which is easy to get wrong.
````

---

### Try it in the runner

Add `"Ada"` a second time to the names array, and change the array's size so it can hold four names. Predict the `lengths.size` value before you press **Run**. It's still 3, since the table is keyed by name, and the second `Ada` writes to the same entry. The array keeps all four names, and the table keeps three.

Then change `qsort` to sort `names` in place, instead of the copy, and predict whether the array's order is still the one it was given. It isn't, since the sort reorders the array. That's why the program sorts a copy, so the array keeps the input order the lesson describes.

---

A vector keeps a list in order, a hash table finds values by key, and an array is for a fixed set. Choosing one is a question about the main job the data has to do. Chapter 14 covers the containers, and the homework applies them to two small programs.
