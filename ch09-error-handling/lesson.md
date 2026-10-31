## Ch09 · Error Handling

Programs often reach a point where they can't carry on normally: a value is out of range, a file won't open, or an input is unusable. C has no exceptions, so this chapter covers the tools C provides instead. A function reports failure through its return value, the caller checks that value, and the standard library sets `errno` to say what went wrong. You'll also see the `goto` pattern that C programs use to release resources when something fails partway through.

The steps are:

* [Return codes](#goto/01-return-codes): reporting failure through a return value, and why every call has to be checked.
* [errno](#goto/02-errno): reading the reason a library call failed, and turning it into a message.
* [Cleanup with goto](#goto/03-goto-cleanup): releasing resources on every exit path, in one place.
* [Summary](#goto/04-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*This chapter is written for this course. C has no exceptions. The C++ exception examples are replaced by the error-handling techniques the C standard provides.*
