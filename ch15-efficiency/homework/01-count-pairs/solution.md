## Walkthrough: Count pairs

The inner loop starts at `i + 1`, so each pair appears once: the pair (1, 3) is counted when `i` is 1, and the pair (3, 1) is never visited. Starting the inner loop at zero would count every pair twice and also count each item with itself, which is the mistake the exercise asks you to watch for.

The formula gives the same answer in one step. There are n items, and each one pairs with the n − 1 items after or before it. That counts every pair twice, so the total is halved. Multiplying first and dividing second keeps the arithmetic in whole numbers, which is safe because n times n − 1 is always even.

The loops do n times (n − 1) divided by 2 steps of work, which grows as n squared, while the formula does one multiplication and one division. For the extension about n = 1000, the loops count 499,500 pairs, which is about half of n squared, since the inner loop covers only the later positions.
