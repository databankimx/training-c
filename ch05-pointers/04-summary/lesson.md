## Summary: Pointers

This chapter covered how a pointer refers to a variable without copying it, and how pointers connect to arrays.

* **A pointer holds an address.** It's declared with `*` after the type, and it can be reassigned or set to `NULL`.
* **`&` takes an address, and `*` reads through it.** In an expression, `&x` is the address of `x`, and `*ptr` is the value at the address `ptr` holds.
* **The star means two things.** In a declaration, `int *ptr` declares a pointer. In an expression, `*ptr` reads or changes the value it points to.
* **Check a pointer before reading through it.** A null pointer has no value, and dereferencing it is undefined behavior.
* **An array's name is a pointer to its first element.** `numbers[i]` is the same as `*(numbers + i)`.
* **Adding to a pointer moves it by elements.** `first + 2` is two elements along, whatever the size of the element.
* **A function that receives an array gets a pointer.** Inside the function, `sizeof` gives the size of the pointer, so the length must be passed in.
* **A string is a pointer to its first character.** `const char *` is the usual form for text the program only reads. An array of strings is an array of `const char *`.

### Check your understanding

*These questions are written for this course.*

````quiz
Which declaration gives `ptr` the ability to point at nothing?
○ int ptr = NULL;
→ Not quite. An int can't hold an address, so it can't be a pointer. The star is needed in the declaration.
◉ int *ptr = NULL;
→ Yes. A pointer can hold NULL when it points at nothing.
○ int *ptr = &x;
→ Not quite. That gives the pointer an address. It can't point at nothing, so it doesn't meet the requirement.
````

````quiz
After `int numbers[4] = {1, 2, 3, 4};` and `int *p = numbers;`, what is `*(p + 3)`?
○ 1
→ Not quite. That's *p, the first element.
◉ 4
→ Yes. Adding 3 moves the pointer three elements along, to the fourth element.
○ 3
→ Not quite. That's the third element, at p + 2.
````

````quiz
What does the `&` mean in `int *p = &n;`?
○ It divides n by p.
→ Not quite. Division uses /. Here & takes the address of n.
◉ It takes the address of n, and stores it in p.
→ Yes. The address-of operator gives the location of n, which p then holds.
○ It makes p another name for n.
→ Not quite. That describes a reference, which C doesn't have.
````
