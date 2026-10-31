## Ch12 · Composition and Polymorphism

Many types share most of their data and behavior, and some code needs to treat different objects in the same way. C has no inheritance, so this chapter uses the two techniques C provides instead. A structure can contain another structure as its first member, so one type extends another. A table of function pointers lets one call do the right thing for each object it's given. Together they're the usual way to organize larger C programs.

The steps are:

* [Embedding a base structure](#goto/01-embedding-a-base): one structure contains another, and how the members are reached.
* [Several parts and protection](#goto/02-several-parts): building a structure from more than one part, and why C has no protected members.
* [Polymorphism with function pointers](#goto/03-polymorphism): a table of function pointers, and calling through it.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples in this chapter are adapted from the earlier C++ tutorial. C has no inheritance, no access levels, and no virtual functions, so the chapter uses structures and function pointers in their place.*
