## Ch17 · Resource Management

C programs hold resources: files, locks, memory on the heap. Every one has to be released, and releasing them by hand is where bugs come from. C has no destructors, so the release has to be written out. This chapter covers how to release resources on every way out of a function, how to make one owner responsible for each block of memory, and how to share a block safely when more than one part of a program needs it. Those are the C forms of RAII and the smart pointers from the C++ course.

The steps are:

* [Cleanup on every exit](#goto/01-cleanup-on-exit): releasing resources when a function leaves by any route, using one cleanup block.
* [Single owners](#goto/02-single-owner): one owner for each block, with ownership handed over by convention.
* [Shared ownership](#goto/03-shared-ownership): several owners of one block, and a count that decides when it's released.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C has no destructors, smart pointers, or scope-based release, so the chapter uses the cleanup block from the error-handling chapter, ownership conventions, and reference counts written out by hand.*
