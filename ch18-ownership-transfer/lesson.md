## Ch18 · Ownership Transfer

Copying an object is the default in C, and it's the right choice when two objects each need their own value. Often the source is about to be discarded, though, and copying it is wasted work. C++ has move constructors and `std::move` for that case. C has no moves, but it has the same idea in a plainer form: a value is handed from one owner to another, and the source is left empty so it can't be used by mistake. This chapter covers how to transfer ownership safely, and the rules that make the transfer work.

The steps are:

* [Copies and transfers](#goto/01-copies-and-transfers): copying a structure, and handing a block over by pointer.
* [Transferring ownership](#goto/02-transferring-ownership): a transfer function that clears its source, so no two owners remain.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C has no move constructors or `std::move`, so the chapter uses structure copies and pointer transfers, with the source cleared by convention.*
