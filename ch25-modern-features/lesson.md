## Ch25 · Modern Features

Recent C++ standards added features that cut the repetition from older code and make intent clearer. C has been changing too. C23, the newest standard, adds some of the same conveniences, such as `auto` for type inference and `nullptr`. This chapter uses C23 for those features, and the CMake files in this chapter set the standard to C23. It also covers what C does without the C++ features that have no counterpart, such as `std::optional` and structured bindings.

The steps are:

* [auto and named parts](#goto/01-auto-and-named-parts): letting the compiler work out types with C23, and naming the parts of a record.
* [Optional values](#goto/02-optional-values): returning a value or nothing, with a struct that carries a presence flag.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The explanations are new. The C23 features follow the standard's `auto`, and the chapter notes which C++ features have no C counterpart. The overview of the newer C++ features follows Stroustrup's *A Tour of C++*, third edition.*
