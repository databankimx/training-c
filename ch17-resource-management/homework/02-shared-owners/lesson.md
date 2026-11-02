## Homework: Shared owners

In this exercise, several owners share one resource, and you watch the owner count change as they're added and removed.

The program should:

* define a `Resource` structure with a name and an owner count, a `resource_create` function that prints `Acquire <name>`, a `resource_retain` function that adds an owner, and a `resource_release` function that removes one and prints `Release <name>` when the count reaches zero
* in `main`, create a resource called `shared` as `original`
* keep an array of up to four holders, each a pointer to the resource, with a count of how many are in use
* retain the resource into the holders array, and print `Owners: ` followed by the owner count
* retain it a second time, and print the owner count again
* release every holder, the way clearing a vector would, and print the owner count again
* print `End`, then release `original`

### What to check

The output should be:

```
Acquire shared
Owners: 2
Owners: 3
Owners: 1
End
Release shared
```

The first owner count is 2, not 1, because `original` and the first holder both own the resource. Explain why `Release shared` comes after `End`, not before. Then explain what would change if `original` were released before the holders were cleared, and what the count would show.

### Extensions

* Create a second resource, and show that its owner count is independent of the first.
* Explain why a reference count that isn't protected can give wrong answers in a program that has threads.

---

*This exercise is not from the book. It practices the ideas in Chapter 17.*
