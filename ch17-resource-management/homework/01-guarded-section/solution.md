## Walkthrough: Guarded section

`process` enters the guard once, at the top. The failure route jumps forward to the `leave` label, and so does the success route, since it falls through to the label. Every route therefore reaches `guard_leave` exactly once, and the return happens after the leave. That's why `Leave section` prints before `Caught` in the second call: the caller can't see the result until the function has returned.

The return value does the work that the exception did in the C++ version. A failure is a -1 from `process`, and `main` prints the message only when it sees it. The guard's leave still runs first, since the cleanup label sits before the `return`.

For the extension with two guards, the inner guard is entered after the outer one, so its leave label must come first, before the outer leave. Labels are reached in the order they're written, so the inner label sits above the outer one, and a failure after the inner enter jumps to the inner label. That's the reverse-order rule from the cleanup step.
