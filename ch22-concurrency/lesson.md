## Ch22 · Concurrency

Modern programs use several processors at once, and threads are how a C program puts that work to use. Running work at the same time brings its own hazards: two threads changing the same data can lose updates, and two threads waiting on each other can stop altogether. This chapter covers starting and joining threads, protecting shared data with a lock, and the habits that keep threaded code correct.

C's standard library has a thread interface, but MinGW does not provide it reliably on Windows, which is where this course runs. The course uses the Windows thread and lock functions from `<windows.h>` instead. They do the same jobs as the C++ `std::thread`, `join`, and `std::mutex`, and the lessons name each one.

The steps are:

* [Threads](#goto/01-threads): starting a thread, and waiting for it to finish.
* [Locks](#goto/02-locks): protecting shared data with a critical section, and the rule for using it.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. It uses the Windows thread functions, since the course's toolchain on Windows does not provide the C11 thread interface, and the lessons name the C++ equivalents.*
