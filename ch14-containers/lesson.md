## Ch14 · Containers

Arrays hold a fixed number of values, and most programs need something more flexible. This chapter covers the collections C programs build: growable lists, which keep their order, and hash tables, which find values by key. C's standard library has neither, so both are written here from memory the program allocates itself. The chapter ends with the choice between them, and how a program can use several at once.

The steps are:

* [Vectors](#goto/01-vectors): a growable list, with adding, reading safely, and looping over it.
* [Hash tables](#goto/02-hash-tables): storing values under keys, counting with a table, and what a table gives up in exchange for speed.
* [Choosing a container](#goto/03-choosing-containers): comparing arrays, vectors, and hash tables, and how a program can use several at once.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C's standard library has no containers, so the vector and hash table are built in the chapter. The C++ map, which keeps its keys in sorted order, has no C counterpart in the standard library, and the hash table replaces it with the trade-offs the chapter describes.*
