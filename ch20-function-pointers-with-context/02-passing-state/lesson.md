## Passing state

A lambda often needs a value from the code around it, and the capture list says how it gets that value. `[factor]` holds a copy, made when the lambda is created, and `[&total]` refers to the original. C has no capture list. The state a function needs has to be passed in, and the caller decides what it contains. The usual way is a context: a structure that holds the state, and a pointer to it that is passed along with the function.

Here are two contexts, one for each kind of capture, in `src/main.c`. The first holds a copy:

```c
typedef struct {
    int factor;
} ScaleContext;

static ScaleContext make_scale_context(int factor) {
    ScaleContext context = {factor};
    return context;
}
```

The context stores the value passed to `make_scale_context`. The structure is a copy, so later changes to the caller's `factor` don't reach it. The second holds a pointer to the original:

```c
typedef struct {
    int *total;
} AccumulatorContext;

static void add_to(AccumulatorContext *context, int x) {
    *context->total += x;
}
```

The pointer refers to the caller's `total`, so each call changes it, the way `[&total]` did in the lesson.

Press **Run**. The output is:

```
Scaled by copy: 15
Total by reference: 10
```

The copy is made when the context is created, so the later change to `factor` doesn't affect the result: the context still multiplies by 3. The total is changed through the pointer, so after both calls it's 10.

### Copy or pointer

The choice is the same one the C++ lesson made. Store a copy when the function should see the value as it was, and store a pointer when it should see or change the current value of the original. A copy is always safe to keep. A pointer is safe only while the object it refers to is alive.

### The lifetime rule

A context that holds a pointer to a local variable must not outlive that variable. If the context is stored and used after the function that owns the variable has returned, the pointer refers to memory that no longer exists. Calling the function then reads or writes memory the program no longer owns, which is undefined behavior, and the mistake can look correct for a while. The C++ lesson gave the same warning for a lambda that captured by reference, and the rule is the same here: a pointer in a context is a promise that the target outlives the context.

The safe pattern is to keep the context in the same scope as the variable it points to, or to keep the variable alive for as long as the context is used. The dynamic-memory step applies when the value must live longer than the function.

### Every value is named

A context lists each value a function needs, and nothing is captured implicitly. The C form of `[=]` and `[&]` would hide that list, so the course always names each member, as the capture list does. A reader can see every dependency by looking at the structure.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does `scale_by_copy` still multiply by 3 after the caller changes `factor` to 10?
○ Because the function was compiled before the change.
→ Not quite. The timing of compilation doesn't matter here.
◉ Because the context holds a copy of the value, made when the context was created.
→ Yes. The copy is independent of the caller's variable, which the change doesn't reach.
○ Because a structure can't hold an int.
→ Not quite. A structure holds an int without any trouble.
````

````quiz
What is the danger in keeping a context that points to a local variable?
○ The context becomes slower to use.
→ Not quite. Speed is not the issue.
◉ If the context is used after the variable has gone out of scope, it refers to memory the program no longer owns.
→ Yes. Using it then is undefined behavior.
○ The context cannot be passed to a function.
→ Not quite. It can be passed, but the target must still be alive.
````

---

### Try it in the runner

Change `make_scale_context` so the context stores a pointer to `factor` instead of a copy, and predict the value it prints before you press **Run**. The pointer refers to `factor`, which is 10 when the call happens, so the output is `Scaled by copy: 50`. The name still says "copy", so it should change too. The lesson's point is that the stored form decides the behavior, not the name.

---

A context passes captured state explicitly, as a copy or as a pointer, and the choice decides what the function sees. The next step is the chapter summary, and then two homework exercises that use these functions.
