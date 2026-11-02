## Homework: Move through holders

In this exercise, you transfer one resource into an array of owning pointers, and then transfer it back out. The array plays the role of the C++ vector of `unique_ptr` values.

The program should:

* define a `Resource` structure with a name, a `resource_create` function that prints `Acquire <name>`, and a `resource_destroy` function that prints `Release <name>`
* in `main`, create a resource named `vessel` as `p`
* create an array `holders` of four owning pointers, all set to `NULL`, with a count of the slots in use
* transfer `p` into `holders` at the next free slot, and print `Size after push: ` followed by the count
* print `p owns nothing: yes` if `p` is `NULL`, and `p owns nothing: no` otherwise
* transfer the first slot back out into a new pointer named `back`, and reduce the count by one, since the removed slot is empty
* print `Got back: yes` if `back` holds the resource, and `Got back: no` otherwise
* print `End`, then release `back`

### What to check

The output should be:

```
Acquire vessel
Size after push: 1
p owns nothing: yes
Got back: yes
End
Release vessel
```

Notice that reducing the count prints nothing. The slot it removes is empty, so there's no resource to release, and the release happens only when `back` is released after `End`.

### Extensions

* Transfer two resources into the array, and check the count. Explain why the order of their release is not something to depend on in this exercise.
* Without transferring `p`, copy its pointer into `holders`, and explain what the copy does to the single-owner rule.

---

*This exercise is not from the book. It practices the ideas in Chapter 18, with the arrays from Chapter 4.*
