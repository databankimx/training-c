## Homework: Ownership handoff

In this exercise, you hand a resource to a function by transferring it, and watch the function become its owner until it returns.

The program should:

* define a `Resource` structure with a name, a `resource_create` function that prints `Acquire <name>`, and a `resource_destroy` function that prints `Release <name>`
* define `consume(Resource **owner)`, which takes the caller's pointer by address. It takes the resource, sets the caller's pointer to `NULL`, prints `Received <name>`, and releases the resource before it returns. If the pointer is already `NULL`, it prints `Nothing to receive.` and returns
* in `main`, create a resource named `handoff`, pass it to `consume`, and then print `Back in main`
* print `End` before `main` returns

### What to check

The output should be:

```
Acquire handoff
Received handoff
Release handoff
Back in main
End
```

The `Release` line comes before `Back in main`. The function owned the resource while it ran, and it released it before returning, since nothing kept the resource alive after that. Predict the output before you run it, and explain why `Release handoff` appears where it does.

### Extensions

* Change `consume` so it only reads the resource, and does not take ownership. Predict whether the release still happens inside `consume`, and check your prediction. Then explain which of the two functions must release the block in the program.
* Call `consume` twice in a row, and check that the second call prints `Nothing to receive.` instead of releasing anything. Explain why the check on `NULL` is what makes the second call safe.

---

*This exercise is not from the book. It practices the ideas in Chapter 18, with the single-owner convention from Chapter 17.*
