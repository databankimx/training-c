# Quickstart

This guide takes you from a fresh copy of the repository to a working lesson runner, where every lesson example can run. Follow the steps in order. Each step says how to check it worked. The last section covers the errors you're most likely to see.

Commands are for **Windows PowerShell**, and assume you're in the repository root, `training-c`, unless a step says otherwise.

---

## Where to clone the repository

Clone the repository under `C:\Development`, for example `C:\Development\training\training-c`. The lesson runner builds and runs each exercise inside the repository, in a folder called `.lesson-runner`. Security software on managed machines is set up to allow that folder when it's under `C:\Development`. A copy somewhere else, such as your Downloads folder or a temporary folder, may have its new programs removed as they're built.

---

## Quick setup with the script

`setup.ps1` checks the toolchain, downloads the vendored libraries, makes the runner's icon, and builds the runner. It's safe to run more than once.

First, install **MSYS2** (step 1 below). Then, from the repository root:

```pwsh
powershell -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing
```

The `-ExecutionPolicy Bypass` part lets this one script run. It doesn't change any setting on your machine.

With `-InstallMissing`, the script installs the MSYS2 packages it's missing, using pacman. Without it, the script stops and shows the pacman command to run. Company policy can block package installs, in which case the script says so, and you'll need IT.

When the script finishes, it prints a summary. Steps 1 to 5 below cover the same work, if you need to see what the script does, or run one part by hand.

---

## 1. Install MSYS2

Download the installer from [msys2.org](https://www.msys2.org) and install it to the default folder, `C:\msys64`.

Open the **MSYS2 UCRT64** shell from the Start menu, and run:

```sh
pacman -Syu
```

If pacman asks you to close the shell, do so, and open **MSYS2 UCRT64** again. Then run `pacman -Syu` until it reports nothing to do.

**Check:** `C:\msys64\ucrt64\bin` exists.

---

## 2. Install the toolchain

In the MSYS2 UCRT64 shell:

```sh
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-librsvg mingw-w64-ucrt-x86_64-imagemagick
```

**Check:** in the same shell, `gcc --version` shows version 14 or later, and `cmake --version` and `ninja --version` both print a version.

The course needs gcc 14 or later. If `gcc --version` shows an older version, run `pacman -Syu` again.

---

## 3. Check the WebView2 runtime

The lesson runner shows its window with the WebView2 runtime, which Windows 11 includes. On Windows 10, it's usually installed too. If it's missing, download the **Evergreen Bootstrapper** from [developer.microsoft.com/microsoft-edge/webview2](https://developer.microsoft.com/microsoft-edge/webview2/) and run it.

**Check:** in PowerShell, `Get-ItemProperty "HKLM:\SOFTWARE\WOW6432Node\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}"` shows a `pv` value.

---

## 4. Run the setup script

From the repository root:

```pwsh
powershell -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing
```

The script downloads the WebView2 SDK into `resources\vendor\webview2`, and cJSON into `resources\vendor\cjson`. It makes `lesson-runner\host\app.ico` from the blue logo, and builds the runner into `lesson-runner\build`.

**Check:** the summary at the end shows `ok` for each line, and the last line says the runner is built.

---

## 5. Start the lesson runner

From the repository root:

```pwsh
cd lesson-runner
.\build\lesson-runner.exe
```

A window titled **Lesson Runner** opens, with the chapters on the left. The first chapter, **Ch01 · Getting Started**, takes you through your first programs.

To rebuild after a change to the runner's own code, run from `lesson-runner`:

```pwsh
cmake --build build
```

---

## 6. Set up VS Code (optional, recommended)

Install VS Code from [code.visualstudio.com](https://code.visualstudio.com), and add the **C/C++** extension (publisher `Microsoft`). It gives you the editor features for C, such as code completion and error squiggles. Open the repository root (not a sub-folder) in VS Code.

**Check:** the Extensions view lists C/C++ as installed.

---

## 7. Your first run of each kind of step

Work through these once, to confirm each kind of example runs.

| Kind | Where | What you should see |
|---|---|---|
| Program with output | Ch01, Hello world | `Hello World!` and `I am learning C` in the Output pane. Press **Run** (or F5) |
| Program with a homework example | Ch01, Homework, Banner | The three lines of the banner. The example is hidden until you choose to reveal it |
| Quick picks | Ch01, Hello world | The Quick picks box stays hidden, since the step has one command |

The runner's own test steps, which exercise each kind of run, are in `resources\runner-test-steps`.

The first run of each step builds it, so it can take several seconds.

---

## Troubleshooting

| What you see | What to do |
|---|---|
| The setup script says MSYS2 isn't installed | Install MSYS2 to `C:\msys64` (step 1). |
| The setup script says a package is missing | Run it again with `-InstallMissing`, or run the pacman command it shows, in the MSYS2 UCRT64 shell. |
| `gcc` is version 13 or earlier | Run `pacman -Syu` in the MSYS2 UCRT64 shell, then open a new shell. |
| The runner says `Could not start CMake` | The build tool isn't in `C:\msys64\ucrt64\bin`. Check step 2, then restart the runner. |
| Run says the step didn't build a program | The step's `CMakeLists.txt` should build an executable called `program`. This is a problem in the step, not in your setup. |
| The runner window doesn't open | Check that `lesson-runner\build\WebView2Loader.dll` exists. If it doesn't, run `cmake --build build` in `lesson-runner`. |
| Run says the program couldn't start with "Access is denied", or the program is missing right after a build | Check that the repository is under `C:\Development`. If it is, report the step and the full error text, since your security software may be removing the new program. |
| The window opens with no icon, or the chapters don't load | Check the Output pane and the summary from `setup.ps1`, then send the first error to the development team. |
| The Output pane shows a `.WebView2` folder next to the runner | That's the browser's data folder, created on first run. It's normal, and can be ignored. |

If a problem isn't listed here, note the step you were on and the full error text, and report it. Include the Output pane text, because the first error is often the useful one.
