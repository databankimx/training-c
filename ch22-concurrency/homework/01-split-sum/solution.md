## Walkthrough: Split sum

Each thread gets its own `Range`, and each `Range` holds a pointer to a different result variable. The threads never write to a variable that another thread reads or writes, so nothing needs a lock. The wait then makes sure both sums are finished before `main` adds them.

The ranges meet at 501 with no gap and no overlap. The first range goes up to, but not including, 501, and the second starts at 501, so each number from 1 to 1000 is counted once. The same rule applies to three threads: each range's end is the next range's start.

For the extension that shares one total, two threads would each read and write the same variable, which is the data race from the locks step. A critical section around each addition would prevent lost updates, at the cost of making the threads wait for each other, which is why splitting the work is the better design.
