## Walkthrough: Shared owners

The count starts at 1 when `original` is created. Each retain adds an owner: the first retain goes into the first holder, so the count reads 2, and the second retain makes it 3. The holders are owners in the same sense as `original`, since each holds the pointer and is counted.

Clearing the holders releases each of them, lowering the count from 3 to 1. `original` still holds the resource, so nothing is freed yet. Only the final release, after `End`, drops the count to zero and prints `Release shared`.

If `original` were released before the holders were cleared, the count would drop from 3 to 2, and nothing would be freed. The holders would still point at a live block. The count keeps the block alive in that order too, which is the point of counting owners instead of trusting the first release.

For the thread extension, two threads that retain or release at the same moment can each read the same count and write back a wrong value. The count can then miss an owner, which frees the block too early, or keep a block that should have been freed. The threads chapter covers the atomic updates that prevent this.
