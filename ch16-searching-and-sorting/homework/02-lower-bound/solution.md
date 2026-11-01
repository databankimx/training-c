## Walkthrough: Lower bound

The search keeps a range from `low` up to, but not including, `high`. Each pass checks the middle. If the middle is smaller than the target, the answer must lie after it, so `low` moves past the middle. Otherwise the middle could be the answer, or the answer lies before it, so `high` moves down to the middle and keeps it in range. The loop stops when the range is empty, and `low` is then the answer.

The rule that makes the duplicates work is the `else` branch. When the middle equals the target, the code doesn't stop. It moves `high` down to the middle, so the search keeps looking to the left for an earlier 3. That's why the answer for 3 is index 1, the first of the three 3s, and not index 2 or 3.

For the target 9, every value is smaller, so `low` moves up until it reaches `count`, and the function returns 6. For the target 4, the search finds that the answer is the 5 at index 4.

The extension's version keeps `high` one past the range from the start, so the first pass never has an empty range to think about. The comparison with a target smaller than every value is the useful check: both versions must return 0 for it.

The search makes about log₂n comparisons, since each comparison halves the range. Duplicates don't change that, because the rule keeps the range intact until it's down to the first matching position.
