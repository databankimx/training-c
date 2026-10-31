## Pointers and arrays

You've used `numbers[1]` for an element of an array, and the arrays chapter noted that an array's length can't be found once the array is passed to a function. This step shows why both of those are true: an array's name is a pointer to its first element.

Here's the program for this step, in `src/main.c`:

```c
int numbers[3] = {10, 20, 30};
int *first = numbers;
```

The name `numbers`, used on its own, gives the address of its first element. So `first` points at 10. No `&` is needed, since the array's name already works as an address. This is why `numbers` can be assigned to a pointer without any operator at all.

Press **Run**. The output is:

```
10
20
30
Array size: 12 bytes
Pointer size: 8 bytes
Elements counted from the array: 3
```

The first three lines show the program reading each element in a different way. `*first` reads the value at the address, which is 10. `first[1]` uses square brackets on a pointer, and gives the element one step past it, which is 20. `*(first + 2)` adds 2 to the pointer, and reads the element two steps along, which is 30.

The last three lines show what `sizeof` gives for the array and for the pointer. The array is three `int` values, 12 bytes on this toolchain. The pointer is 8 bytes, which is the size of an address on a 64-bit system. The count of elements is the array's size divided by the size of one element, which gives 3, as the arrays chapter showed.

### Adding to a pointer

Adding a number to a pointer moves it by that many elements, not by that many bytes. `first + 2` points two `int`s past `first`, whatever the size of an `int` on your system. That's why `first + 2` is the third element and not part of a byte count.

Square brackets are a shorthand for this: `first[1]` means `*(first + 1)`. The two forms always give the same element. You can write `numbers[1]` for the same reason, since the name of an array is a pointer to its first element.

### Why a function needs a count

The last line of output shows the problem a function would run into. In `main`, `sizeof numbers` gives the size of the whole array, so the count is 3. A pointer holds only an address, and `sizeof first` gives 8, which is the size of the address and says nothing about how many elements follow it.

When an array is passed to a function, the function receives only a pointer, just like `first`. Inside the function, `sizeof` on the parameter gives the pointer's size, so the function can't work out the count itself. The count has to be passed in as a separate parameter. The functions chapter shows how to write that function, and the `sizeof` output above shows why it's needed.

Keep the two meanings apart. In `main`, `numbers` is the whole array, and `sizeof numbers / sizeof numbers[0]` gives its length. Once it's a pointer, the same expression gives the wrong answer.

---

### Quiz

*These questions are written for this course.*

````quiz
With `int *first = numbers;`, what is `first[2]` for `int numbers[3] = {10, 20, 30};`?
○ 10
→ Not quite. That's first[0], the first element.
◉ 30
→ Yes. first[2] is *(first + 2), the third element.
○ 20
→ Not quite. That's first[1], the second element.
````

````quiz
Why does `sizeof first` give 8 in the program, when `sizeof numbers` gives 12?
○ Because first holds only three elements.
→ Not quite. first holds an address, not elements, so its size says nothing about the array's length.
◉ Because first is a pointer, and sizeof gives the size of the address it holds.
→ Yes. A pointer is the size of an address, and it doesn't carry the size of the array it points to.
○ Because pointers are always one byte.
→ Not quite. A pointer is the size of an address, which is 8 bytes on this 64-bit toolchain.
````

---

### Try it in the runner

Set `first = &numbers[2];`, and predict what `*first` shows before you press **Run**. It shows 30, since `&numbers[2]` is the address of the third element.

Then change `first` to point at `numbers[0]` again, and predict the output of `first[2]`. It's 30 again, since the square brackets reach two elements past the pointer.

Finally, predict the `Pointer size` line on a computer with a 32-bit toolchain. It would print 4 bytes, since an address is then half the size. The array's size would still be 12 bytes, since its three `int` values don't change.

---

An array's name is a pointer to its first element, and square brackets are a way to reach elements from it. That's the link behind the length problem when arrays are passed to functions. The next chapter covers loops, which are how a program visits every element without writing each index by hand.
