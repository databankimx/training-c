## Ch10 · Structures

Many values belong together: a car has a brand, a model, and a year, and a program that handles cars should handle them as one thing. A structure groups related values under a single type, and this chapter covers how to declare one, how functions use it, and how to start every variable in a known state.

The steps are:

* [Structures as variables](#goto/01-structures-as-variables): declaring a structure type with `typedef`, creating variables of it, and reaching members with a dot.
* [Structures in functions](#goto/02-structures-in-functions): returning, copying, and changing structures through parameters.
* [Initializing structures](#goto/03-initializing-structures): brace initialization, zero-filling, and independent copies.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples in this chapter are adapted from the earlier C++ tutorial. C has no default member values, so the chapter uses brace initialization and zero-filling in their place.*
