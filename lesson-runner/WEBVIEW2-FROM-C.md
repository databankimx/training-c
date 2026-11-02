# WebView2 from C: what we learned

This record covers the lesson runner's window in C. It's the part of the work that cost the most time, so it's written
down in the order the problems appeared. The C++ runner doesn't have these problems, because its COM bindings handle
some of them for you, and the C code has to do each one by hand.

## The short version

WebView2 works from plain C. The runner's window in `host\app.c` follows the C++ runner's `app.cpp` step for step.
Three things had to be exactly right before a page would load, and each one was easy to miss.

## Gotchas, in the order we hit them

**1. The header warnings.** `WebView2.h` declares its interface IDs with `EXTERN_C __declspec(selectany)`. In C, that
becomes a plain `extern` with an initializer, and GCC warns about it. The header is vendored code, so it's included as a
system folder (`target_include_directories(... SYSTEM ...)`). That keeps its warnings out of the build, and this
program's own code keeps every warning.

**2. The GetProcAddress cast.** Casting the `FARPROC` that `GetProcAddress` returns straight to a function pointer type
triggers `-Wcast-function-type`. Reading it through a union avoids the warning without changing the behavior.

**3. Callbacks must answer for their own interface.** WebView2 asks each callback object for its handler's interface,
not only `IUnknown`. An object that answers only `IUnknown` is dropped without any error, and the window stays blank.
The runner's callbacks answer for `IUnknown` and their own interface only.

**4. Keep a reference to the controller.** The runtime releases the controller when the completed-handler callback
returns. The runner calls `AddRef` on it, and releases it when the window closes. Without the `AddRef`, the browser is
torn down and the page never appears.

**5. Use a virtual host, not `NavigateToString`.** Pages loaded from a string, or from a plain web address, didn't
complete navigation in our tests. The runner maps `https://runner.local/` to the web folder with
`SetVirtualHostNameToFolderMapping`, and loads the page from there. That's the approach the C++ runner's `app.cpp`
describes, and it's the one that works.

**6. Start as a GUI program.** The window needs the GUI entry point (`wWinMain`, with `-mwindows -municode`) and
`UpdateWindow` after `ShowWindow`. The spike ran as a console program for its diagnostics, and it only started working
once it matched the runner's startup.

**7. Release in order.** On close: the controller is closed and released, then the web view, then the environment. The
C++ runner does the same, and it avoids leaving browser processes running.

**8. Leftover processes are other programs.** Many `msedgewebview2.exe` processes run on a machine, because Teams,
Outlook, OneDrive, and Windows all use WebView2. Killing them only makes them restart. To see which program owns a
process, count them by their data folder, which is what the diagnostic one-liner did.

**9. The data folder.** The spike gave WebView2 its own data folder. The runner passes NULL and lets the runtime choose
the default, as the C++ runner does, so the browser profile isn't shared with the spike's.

**10. Stale SDK paths in CMake.** `set(... CACHE PATH ...)` keeps the value from the first configure. After the SDK
location changed, the build kept using the old path until the build folder was reconfigured.

**11. Antivirus.** One machine's security software removed a newly built program right after linking. The runner's
build folder needed an exception. The C++ course's exception covers `C:\Development\training\**`, which is why the runner
works from there.

**12. Icons.** The window classes have to ask for the icon with `LoadIconW(instance, MAKEINTRESOURCEW(1))`. Embedding
the resource in the program isn't enough on its own.

## Where the code is

- `host\app.c`: the window, the COM callbacks, and the message protocol.
- `host\router.c` and `host\commands.c`: the page's commands.
- `host\runner.c`: building and running a step, with its output sent back as events.
- `host\discovery.c`: finding the chapters, steps, sections, and homework.
- `web\`: the page itself, copied from the C++ runner and changed for C (title, syntax highlighting, and saved-state keys).
