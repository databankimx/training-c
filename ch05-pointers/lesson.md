## Ch05 · Pointers

Arrays gave you a list of values under one name. This chapter covers the pointer, which holds the address of a variable rather than a copy of its value. Pointers are how C refers to a value without copying it, and they're the foundation for passing data to functions, for dynamic memory, and for strings. An array's name is itself a pointer to its first element, so the chapter ends by connecting the two ideas.

C++ also has references, which are another name for a variable. C doesn't have them, so this chapter covers pointers only, and the functions chapter shows how a pointer does the job a reference does in C++.

The steps are:

* [Pointers](#goto/01-pointers): taking an address, reading and writing through a pointer, and empty pointers.
* [Pointers and arrays](#goto/02-pointers-and-arrays): why an array's name works as a pointer, and what adding to a pointer does.
* [Strings and pointers](#goto/03-strings-and-pointers): a string as a pointer to its first character, `const char *`, and arrays of strings.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. Pointers are described in the C17 standard.*
