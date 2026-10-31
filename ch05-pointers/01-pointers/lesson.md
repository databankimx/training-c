## Pointers

A pointer is a variable that holds the address of another variable, as a value of its own. Because it's a value, a pointer can be changed to point somewhere else, and it can hold no address at all. C has no other way to refer to a variable without copying it, so pointers do the job that references do in C++.

Here's the program for this step, in `src/main.c`:

```c
int servings = 4;
int *ptr = &servings;   // ptr holds the address of servings

printf("%d\n", servings);
printf("%d\n", *ptr);
```

Press **Run**. The output is:

```
4
4
```

The declaration `int *ptr` says that `ptr` is a pointer to an `int`. The star belongs to the pointer's type here, so it reads as "pointer to int". The `&` on the right is the address-of operator. It gives the address of `servings`, and that address is stored in `ptr`. The line doesn't print the address, because the number changes on every run, and nothing depends on knowing it.

The `*` in `*ptr` is the dereference operator. In an expression, it means "the value at the address this pointer holds", so `*ptr` is `servings`. Reading through the pointer gives the same number as reading `servings` directly.

The same star means two different things, depending on where it stands. In `int *ptr`, it declares a pointer. In `*ptr`, it reads through one. Most of the confusion around pointers comes from that double use, so read each star by its position.

### Changing through a pointer

Assigning through a pointer changes the variable it points to:

```c
*ptr = 6;
printf("%d\n", servings);
```

The output is `6`. The pointer didn't change, and neither did its address. The value stored at that address did, and `servings` is the value at that address.

### Pointers can be empty

A pointer that points at nothing is set to `NULL`:

```c
int *empty = NULL;
if (empty == NULL) {
    printf("The pointer is empty.\n");
}
```

The output is `The pointer is empty.` Dereferencing a null pointer, as in `*empty`, is undefined behavior, and usually crashes. Before you read through a pointer that might be empty, check it, as this `if` does.

`NULL` comes from `<stdio.h>`, as well as several other headers. It's a constant for the null pointer, and comparing a pointer with it is the normal way to ask whether the pointer holds an address.

### Pointers and references

C++ has a second way to refer to another variable, called a reference, and C doesn't have one. A reference is fixed to its variable, can't be empty, and can't be changed to refer to something else. A pointer can be empty, can be reassigned to another address, and needs `*` to read the value it points to. C uses pointers for every case where C++ would use either. A function that changes a caller's variable takes a pointer to it, and the functions chapter shows that pattern.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `*ptr` mean, when `ptr` holds the address of `servings`?
○ The address of servings.
→ Not quite. The address is what ptr holds. The star gives the value at that address.
◉ The value stored in servings.
→ Yes. The dereference operator reads the value at the address the pointer holds.
○ A new copy of servings.
→ Not quite. Dereferencing reads or changes the original variable.
````

````quiz
Which statement is true of a pointer that is `NULL`?
○ It points to the first variable in the program.
→ Not quite. A null pointer points to nothing.
◉ It must be checked before it is dereferenced.
→ Yes. Dereferencing a null pointer is undefined behavior.
○ It can't be changed later.
→ Not quite. A pointer can be given a new address at any time.
````

---

### Try it in the runner

Set `*ptr` to `9`, and predict what `servings` shows before you press **Run**. It shows `9`, since the pointer's target is `servings`.

Then remove the `if` check around `empty`, and add a line that reads `*empty`. Predict what happens. The program may crash or print garbage, since there's no value at a null address. That's why the check is needed. Remove the line before you continue.

---

A pointer holds an address, and `*` reads or changes the value at that address. The next step uses pointers with arrays, where an array's name turns out to be a pointer.
