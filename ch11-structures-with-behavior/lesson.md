## Ch11 · Structures with Behavior

Structures group data, and this chapter adds behavior. C has no classes, so a structure and the functions that work on it are kept side by side, and a pointer tells each function which object it's working on. This chapter also covers how C hides a structure's fields from the rest of the program, which C++ does with access labels. You'll write functions that act on a structure, set up each object with an init function, and hide the fields behind a header file so that only checked functions can change them.

The steps are:

* [Structures and their functions](#goto/01-structures-and-functions): keeping data and the functions that work on it together.
* [Functions that act on an object](#goto/02-methods): passing a pointer to the object, and `const` for functions that only read it.
* [Init functions](#goto/03-init-functions): functions that set up each object, and how brace initialization differs.
* [Hiding fields](#goto/04-encapsulation): an opaque type, a header file, and checks that protect an object's rules.
* [Summary](#goto/05-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C has no classes or access labels, so the C++ class syntax is replaced by structures, functions, and an opaque type.*
