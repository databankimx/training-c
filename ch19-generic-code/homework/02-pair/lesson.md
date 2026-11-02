## Homework: Pair

A pair holds two values, which may be of different types. In C++, a class template with two type parameters writes the pair once for every combination. C has no class templates, so this exercise shows what that costs.

The program should:

* define a structure for a pair of an `int` and a string, with a `make` function that fills it in, and a `print` function that prints `Pair: ` followed by the first value, a space, and the second value
* define a second structure, for a pair of a string and a `double`, with its own `make` and `print` functions
* in `main`, create the pair 3 and "three", and print it
* create the pair "pi" and 3.14, and print it in the same form

### What to check

The output should be:

```
Pair: 3 three
Pair: pi 3.14
```

Each structure has its own members, and each print function reads the types it was written for. The compiler checks each one, since the types are named in the code.

### Extensions

* Write a `swapped` function for the first pair, which returns a pair of a string and an `int`. Decide whether it needs a new structure, and count how many structures a program needs for four types of pair.
* Explain why a single `void *` pair would need to be printed with a function that knows both types, and what the compiler would not check in that case.

---

*This exercise is not from the book. It practices the ideas in Chapter 19, and it shows the cost of having no templates.*
