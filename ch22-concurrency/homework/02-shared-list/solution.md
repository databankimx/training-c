## Walkthrough: Shared list

`add_values` enters the critical section once per value, adds the value only if there is room, and leaves the section before the next value. The check on the size happens inside the lock, so two threads can't both see a free slot and write to it. That is the same rule as the counter in the locks step, applied to a list.

The final size and sum don't depend on the order of the values, because each value is added exactly once. That's why the program can print them without printing the list. The threads may fill the slots in any order, and the sum is the same for every order.

For the extension that removes the lock, two threads could read the same size, both write to the same slot, and one value would be lost. The size would then come out below 10, and the sum would be wrong as well. The program would often look correct, since the threads rarely interleave at the exact moment of a write, which is why such a bug can pass testing and still be present.
