## Set up your workstation

Before we write any C, we need a compiler, which turns the text you write into a program the computer can run. This course uses **gcc** from **MSYS2**, the same toolchain the lesson runner builds with. If you haven't set it up yet, do that first.

The full steps are in [QUICKSTART.md](../../QUICKSTART.md) at the root of the repository. The short version is:

1. Install MSYS2 to `C:\msys64`.
2. Run `setup.ps1` from the repository root, with `-InstallMissing`.
3. Start the lesson runner.

### Check the compiler

Open the **MSYS2 UCRT64** shell from the Start menu, and run:

```sh
gcc --version
```

You should see a version number of 14 or later. Anything older will fail to build the later chapters, so run `pacman -Syu` if you see one.

### What is this step for?

This step doesn't have any code to run, and that's on purpose. The Run button is grayed out, and the Source tab says the step has no code. Read the lesson, make sure the setup works, and then move on to the next step.

When everything is working, you'll have a compiler, a build system called CMake, a second tool called Ninja that does the actual building, and the runner itself. You don't need to know how those fit together yet. The next lessons will show you what happens when you press Run.

---

And that's the whole setup. From here on, the work happens in the runner.
