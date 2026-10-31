## Polymorphism with function pointers

Polymorphism means "many forms". In C++, one call through a base-class reference runs the right version for the object passed in, because the base marks the function `virtual`. C has no `virtual`, but it has a direct way to get the same result: a structure holds a pointer to the function that acts on it. Each object carries its own pointer, so a call through that pointer runs the version for that object.

Here's the program for this step, in `src/main.c`. The structure holds one function pointer:

```c
typedef struct Animal Animal;

struct Animal {
    void (*sound)(const Animal *self);
};
```

The member `sound` is a pointer to a function that takes a `const Animal *`, and returns nothing. Each kind of animal is an ordinary function with that signature:

```c
void pig_sound(const Animal *self) {
    (void)self;
    printf("The pig says: oink oink!\n");
}
```

A function takes a pointer to the base type, and calls through the member:

```c
void make_sound(const Animal *animal) {
    animal->sound(animal);
}
```

Each object is set up with the function for its kind:

```c
Animal pig = {pig_sound};
Animal dog = {dog_sound};
```

Press **Run**. The output is:

```
The animal makes a sound...
The pig says: oink oink!
The dog says: bow wow!
```

The three calls all have the same form, `make_sound(something)`, and `make_sound` calls `sound` on whatever it was given. The object decides which function runs, because each object holds its own pointer.

### What virtual does here

The pointer in each object plays the role of C++'s `virtual` lookup. The caller holds a pointer to an `Animal`, and the call looks up the function through the object itself, at run time. The choice is made from the object's contents, not from the type the caller declared, so one call does different work for each object.

The `(void)self;` lines say the parameter isn't used. The function still has to take it, because the pointer type is shared by every animal.

### The compiler checks the match

C++ has `override` to check that a function replaces a `virtual` one. C has no such keyword, but the compiler checks the pointer type when a function is stored in the member. A function whose parameters or return type don't match the member's type is refused, as an error in recent gcc versions. That's the check `override` gives in C++, and it catches the same kind of mistake: a function that looks right but doesn't fit the table.

### Why the structure has no methods

In C++, the derived class holds the replacement. In C, the object holds a pointer, and the pointer is set when the object is built. Changing the pointer changes that object's behavior, which C++ doesn't allow for a class's virtual functions. That flexibility is why this approach is useful, and it's also why the pointer should be set carefully, in one place, when the object is created.

---

### Quiz

*These questions are written for this course.*

````quiz
What does `animal->sound(animal)` do when `animal` points to a pig?
○ It calls base_sound, since the pointer's type is Animal.
→ Not quite. The pointer's type doesn't decide the call. The object's own member does.
◉ It calls the function that the pig's sound member points to, pig_sound.
→ Yes. The call goes through the object's own pointer, so the pig's function runs.
○ It doesn't compile, since a function can't be called through a pointer.
→ Not quite. Calling through a function pointer is valid C.
````

````quiz
What happens if a function with the wrong parameter type is stored in the sound member?
○ The program runs, and the function is called with the wrong values.
→ Not quite. A mismatched pointer type is refused before the program runs.
◉ The compiler reports an error, since the function's type doesn't match the member.
→ Yes. The type check is the C counterpart of override.
○ The member is ignored, and the base function runs instead.
→ Not quite. Nothing falls back to another function.
````

---

### Try it in the runner

Set `pig` to `{base_sound}`, and predict the second line of output before you press **Run**. It prints `The animal makes a sound...`, since the pig now holds the base function's pointer. That's the same trap that C++ avoids by making the call `virtual`, and it shows that the pointer, not the caller, chooses the behavior. Restore `pig_sound` before you continue.

Then change `pig_sound` so it takes a `Pig *` instead of a `const Animal *`, and predict the result. The build fails, since the pointer type no longer matches the member. Restore the original parameter before you continue.

---

A structure holding a function pointer gives each object its own behavior, and a call through the pointer runs that behavior. The summary covers the chapter, and the homework applies the three techniques together.
