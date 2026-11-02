## Homework: Shared list

Two threads add values to one shared list. The list is protected by a critical section, so the threads never change it at the same moment. The order in which the values arrive depends on the threads, so the program prints only results that don't depend on that order.

The program should:

* write `add_values`, which adds each number from `first` up to, but not including, `last` to the shared list. Each change happens between an enter and a leave of the list's critical section
* in `main`, create an empty list and initialize its lock, start one thread that adds 1 through 5, and a second that adds 6 through 10
* wait for both threads, then print `Size: ` followed by the list's size, and `Sum: ` followed by the sum of its values
* delete the critical section before the program ends

The list is a fixed array of ten slots with a size count, which holds exactly the ten values the exercise adds.

### What to check

The output should be:

```
Size: 10
Sum: 55
```

The order of the values in the list can differ from one run to the next, and the program doesn't print them. The size and the sum are the same every time, which is what the lock guarantees.

### Extensions

* Print the list in sorted order, using the quick sort from Chapter 16 after both threads have finished. Explain why the sort is safe to run without the lock at that point.
* Remove the lock, and explain why the size might come out wrong. Then explain why the program could still appear to work most of the time.

---

*This exercise is not from the book. It practices the ideas in Chapter 22, with the arrays from Chapter 4.*
