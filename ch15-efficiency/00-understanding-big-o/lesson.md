## Understanding Big O

> Measuring programming progress by lines of code is like measuring aircraft building progress by weight.
>
> ~ Bill Gates

Big O, read as "order of", is the notation programmers use to describe how the cost of an algorithm grows with the size of its input. It's a short name for a long idea, so this lesson takes it apart piece by piece before the search and sort steps use it.

---

### What is an algorithm?

An algorithm is a process that performs a specific task. Every solution to a problem has three parts:

* **Input.** The data that comes in, unprocessed. Its size can vary, and we call that size **n**.
* **Process.** How the input is turned into the output. The process is written as an algorithm: a series of defined steps that takes the input to the result. This is the part that needs analyzing, because its cost depends on n.
* **Output.** The processed result.

The search and sort steps in this chapter are all processes of this kind. Each one takes a list, which is the input, and returns an index, a sorted list, or a yes or no, which is the output.

---

### What is complexity?

Big O describes the complexity of a process. Three points matter for reading it correctly.

* **It describes growth.** Complexity is how the work grows as n grows. It doesn't give a time in seconds, because that depends on the machine, the compiler, and the data.
* **It's asymptotic.** Big O describes what happens as n becomes very large. Small inputs can behave differently, and a process that is slower for small n can still win for large n.
* **It's usually the worst case.** Unless the text says otherwise, Big O describes the worst case: the input that makes the process do the most work.

Compare two processes on the same list of n values:

* A linear search checks values one at a time. In the worst case it checks every value, so the work grows at the same rate as the input. We write this O(n), read as "order n".
* A binary search on a sorted list checks the middle, then throws away the half that can't hold the target. The work grows far more slowly, and we write it O(log n).
* A sort of an unsorted list almost always needs at least n × log₂n comparisons. We write that O(n log n).

Other algorithms take much more time, and the notation makes the difference visible at a glance.

---

### Where can I reduce complexity?

Choosing where to spend effort is a design decision, and Big O helps you make it. Take the same unsorted list of n values, with two plans:

* **Search once.** Sorting first and then searching costs about n × (log₂n)² in total for one sort and one search. For n = 10,000, that's around 1.7 million operations. A single linear search takes at most n, which is 10,000 operations. Sorting first costs far more, so the linear search wins.
* **Search many times.** Suppose the list is searched 10,000 times. Sorting once and then searching by binary search costs about 3.4 million operations in total. Searching 10,000 times with linear search costs about 100 million. The sort pays for itself many times over.

So the right choice depends on how often the work repeats, not only on the algorithm's growth rate. A common pattern is to pay a higher cost once, to make many later operations cheaper.

---

### The common Big O classes

These are the growth rates you'll meet most often in this course.

#### O(1), constant time

The cost is the same whatever the size of the input. Examples include:

* setting a variable
* doing one arithmetic operation
* reading an array element by its index

```c
long first_element(const long *values) {
    return values[0];   /* the same work for an array of any length */
}
```

#### O(n), linear time

The cost grows in step with the input. Examples include:

* looping once through an array
* a linear search for a value
* adding up every element

```c
long total(const long *values, size_t count) {
    long sum = 0;
    for (size_t i = 0; i < count; i++) {   /* one pass for each element */
        sum += values[i];
    }
    return sum;
}
```

#### O(n²), quadratic time

The cost grows with the square of the input. Examples include:

* two nested loops over the same list
* many simple sorts, such as bubble sort, selection sort, and insertion sort

```c
long count_equal_pairs(const long *values, size_t count) {
    long matches = 0;
    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < count; j++) {   /* the inner loop runs n times for each outer pass */
            if (values[i] == values[j]) {
                matches++;
            }
        }
    }
    return matches;
}
```

This assumes both loops run over the same list. Two loops over different lists of sizes n and m cost O(n × m), which is less common, and just as costly when n and m are large. Three nested loops give O(n³), and in general any fixed power of n is called polynomial time.

#### O(log n), logarithmic time

The cost grows with the logarithm of the input. Each step halves what's left, so the number of steps is the number of times n can be halved. Examples include:

* a binary search on a sorted list
* finding a value in a balanced tree

When a logarithmic step is repeated for every element, the total becomes O(n log n). That's how merge sort and quick sort are analyzed, and it's why O(n log n) is the best a general comparison sort can do.

#### O(n log n), loglinear time

The cost is n multiplied by log n. Good general-purpose sorts such as merge sort and quick sort have this growth in the typical case.

---

### How much difference can it make?

This table shows the number of operations for small values of n, for each of the major growth rates. The first column is log₂n, the number of times n can be halved.

| log₂n | n | n × log₂n | n² | 2ⁿ | n! |
|---:|---:|---:|---:|---:|---:|
| 1 | 2 | 2 | 4 | 4 | 2 |
| 2 | 4 | 8 | 16 | 16 | 24 |
| 3 | 8 | 24 | 64 | 256 | 40,320 |
| 4 | 16 | 64 | 256 | 65,536 | about 2 × 10¹³ |
| 5 | 32 | 160 | 1,024 | 4,294,967,296 | about 2.6 × 10³⁵ |

Look at the columns that grow fastest. Exponential and factorial growth become impossible to run within a few dozen steps. Quadratic growth is fine for hundreds of values and painful for millions. Logarithmic growth is almost flat, which is why binary search on a sorted list is so hard to beat.

The program in this step counts the steps of three loops, to show the same shapes with real numbers. Press **Run** and the output is:

```
n = 10: linear 10, quadratic 100, halving 3
n = 100: linear 100, quadratic 10000, halving 6
n = 1000: linear 1000, quadratic 1000000, halving 9
```

The linear count equals n, the quadratic count equals n², and the halving count grows by about three each time n grows tenfold, since 2³ is about ten.

---

### Why the notation drops constants

Big O ignores constant factors and smaller terms. A process that does 2n + 5 operations is still O(n), because for large n the term that grows fastest decides the growth. A process that does n² + 100n is O(n²) for the same reason.

This simplification is what makes the notation useful. Two implementations of the same algorithm can differ by a constant factor, because one uses a faster loop or a cheaper comparison. Big O says they grow at the same rate, and the difference in constants is a separate question.

---

### What the course measures

The counting steps in this chapter check these ideas with real numbers. Each search and sort in the next chapter reports how many comparisons or swaps it made, so you can compare the counts with the growth rates above. The counts won't match the Big O formula exactly, since Big O drops constants, but the shape of the numbers should match.

---

### Quiz

*These questions are written for this course.*

````quiz
Why does Big O describe growth rather than a time in seconds?
○ Because computers can't measure time.
→ Not quite. Time can be measured, but it changes from machine to machine.
◉ Because the time depends on the machine, compiler, and data, while growth stays the same across them.
→ Yes. Big O compares how the work grows, which is the same on any machine.
○ Because Big O only applies to very small inputs.
→ Not quite. Big O is about large inputs, which is the reverse of small ones.
````

````quiz
Which growth rate does a binary search on a sorted array have?
○ O(n)
→ Not quite. That's a linear search, which checks each value in turn.
◉ O(log n)
→ Yes. Each comparison halves the part still being searched.
○ O(n²)
→ Not quite. That's the cost of comparing every value with every other.
````

---

### Try it in your head

An array has 1,000 values. Roughly how many comparisons would a binary search need in the worst case? About 10, since each comparison halves the range, and 2¹⁰ is about 1,000. Then ask: how many would a linear search need? Up to 1,000. Then run the program, and check that its halving count for n = 1000 is 9, the number of halvings that take 1000 to 1.

---

Big O is the vocabulary for everything that follows. The next step counts operations in real programs, and the Fibonacci step shows how the same growth ideas expose a repeated calculation.
