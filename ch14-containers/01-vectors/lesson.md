## Vectors

Arrays have a fixed size. Once you've declared `int nums[3]`, it holds three values, and that's the end of it. Most real programs don't know how many values they'll need until they run, so C programs use a growable array. The standard library doesn't provide one, so this step builds a small one, `IntVector`, from memory the program allocates itself. It's the C form of the `std::vector` that the C++ lesson uses.

Here's the program for this step, in `src/main.c`. It starts with an empty vector and adds three scores:

```c
IntVector scores;
int_vector_init(&scores);
int_vector_push(&scores, 72);
int_vector_push(&scores, 88);
int_vector_push(&scores, 95);
```

`int_vector_push` adds a value to the end. The vector makes room for it, so the caller never states a size. The structure keeps three values: `items`, a pointer to the block of memory, `size`, the number of elements, and `capacity`, the number that fit before the next growth.

Press **Run**. The output is:

```
Count: 3
First: 72
Last: 95
Total: 255
Average: 85
After adding: 4
Index 10 is out of range.
Front: 1, back: 3
After pop_back: size 2, back 2
Elements: 99 2
```

### Reading the elements

The vector's elements are read with `int_vector_at`, which takes an index and stores the element in a variable. Index 0 is the first element, and `scores.size` gives the number of elements. `int_vector_at` checks the index first, and returns -1 when it's out of range. That's the C form of the `at` method in the C++ lesson, which throws an exception. C has no exceptions, so the check is a return value, as the error-handling chapter showed.

There's no `[]` form in this vector, since C arrays don't check their indexes. The C form of "reading past the end is undefined" is that a raw pointer into `items` can point past the block, so the program reads elements through `int_vector_at`. Use it everywhere an index comes from outside the program.

### Looping over a vector

A C vector is looped over with an index, as the arrays chapter showed, and the loop's bound is `scores.size`:

```c
for (size_t i = 0; i < scores.size; i++) {
    int value = 0;
    int_vector_at(&scores, i, &value);
    total += value;
}
```

The bound comes from the vector itself, so the loop stops at the last element, and never reads past the end. That's the same guarantee the C++ range-based `for` gives.

### Growing

`int_vector_push` grows the block when it's full. The `grow` function allocates a block twice as large with `realloc`, and copies the elements across. The program adds a fourth score after the loop, and `size` reports 4. The size is decided while the program runs, from the data it reads.

### More vector operations

The C++ lesson's last part uses `pop_back`, `insert`, and `erase`. The C functions do the same work:

```c
int_vector_pop(&stack);
int_vector_insert(&stack, 1, 99);
int_vector_erase(&stack, 0);
```

`int_vector_pop` removes the last element, which pairs with `push` to make a stack. `int_vector_insert` puts a value before a position. The elements from that position on move one place along, using `memmove`, which copies a block of memory that may overlap. `int_vector_erase` removes the element at a position and closes the gap, moving the later elements back. The positions are plain indexes, so `insert` at 1 puts 99 second, and `erase` at 0 removes the first element. The stack is `{99, 2}` at the end, as the output shows.

### What a vector costs

The elements sit side by side in one block of memory. That layout is why reading them is fast: neighboring elements are usually in the processor's cache when the program reaches them, and indexing is a single calculation.

Growing costs more. When the block is full, `grow` allocates a larger one and copies every element. That copy is expensive, but it happens rarely, because the capacity doubles each time. Over many pushes, the copies are spread across the additions, so each push is cheap on average. Insert and erase move every element after their position, so their cost grows with the number of elements after it. The efficiency chapter measures these costs with operation counts.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `int_vector_at` return -1 for an index past the end, rather than reading the element?
○ Because C can't read an element through a pointer.
→ Not quite. C reads elements through pointers all the time.
◉ Because the check stops a read outside the block, which is undefined behavior in C.
→ Yes. The function checks the index before it reads, and returns an error code to the caller.
○ Because the vector has no elements past its size.
→ Not quite. The block may have unused space after the size, so reading there is still wrong.
````

````quiz
A vector holds 1000 elements. What happens to the elements after position 10 when you call `int_vector_insert` at position 10?
○ Nothing. Only the new element is written.
→ Not quite. The elements after the position have to make room for the new one.
◉ Each of them moves one place along, so the work grows with the number of elements after the position.
→ Yes. That's the cost that the efficiency chapter measures.
○ They are all copied into a new vector.
→ Not quite. Only the elements after the position move, and the block stays in place unless it grows.
````

---

### Try it in the runner

Change the check from `int_vector_at(&scores, 10, &checked)` to `int_vector_at(&scores, 3, &checked)`, and predict whether the message prints before you press **Run**. It doesn't. Index 3 is valid after the push of 60, since the vector now holds four elements, with indexes 0 to 3.

Then remove the `int_vector_erase` line, and predict the last line of output. It prints `Elements: 1 99 2`, since the first element is no longer removed.

---

A C vector is a block of memory with a size and a capacity, grown when it's full, and read through a checked function. The next step stores values under keys rather than positions, which is the job of the map in the C++ lesson.
