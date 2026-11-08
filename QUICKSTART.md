# Quickstart

This guide takes you from a fresh copy of the repository to a working lesson runner, where every lesson example can run. Follow the steps in order. Each step says how to check it worked. The last section covers the errors you're most likely to see.

Commands are for **Windows PowerShell**, and assume you're in the repository root, `training-c`, unless a step says otherwise.

---

## Where to clone the repository

Clone the repository under `C:\Development`, for example `C:\Development\training\training-c`. The repository has two build folders, and they do different jobs:

- `lesson-runner\build` holds the lesson runner, the program with the window and the list of chapters. `setup.ps1` builds it.
- `.lesson-runner` holds the builds of the exercises. The runner creates it the first time you press **Run** on a step, and each step's program is built there.

Security software on managed machines is set up to allow those folders when they're under `C:\Development`. A copy somewhere else, such as your Downloads folder or a temporary folder, may have its new programs removed as they're built.

---

## Quick setup with the script

`setup.ps1` installs what's missing, clones the repository if you don't have it yet, checks the toolchain, downloads the vendored libraries, makes the runner's icon, and builds the runner. It's safe to run more than once.

Open **PowerShell as Administrator**, go to the folder where you saved `setup.ps1`, and run:

```pwsh
powershell -ExecutionPolicy Bypass -File .\setup.ps1
```

The `-ExecutionPolicy Bypass` part lets this one script run. It doesn't change any setting on your machine.

By default, the script:

- installs **Git** and **MSYS2** with winget, if they're missing
- clones the repository into `C:\Development\training\training-c`, if the script isn't already inside it, and continues from the clone
- installs the MSYS2 packages it's missing, and updates MSYS2 with `pacman -Syu`

An Administrator window is needed, because the script installs by default. To check only, without installing anything, run `powershell -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing:$false`. It stops and shows what's missing, and the command to fix it. Company policy can block installs, in which case the script says so, and you'll need IT.

When the script finishes, it prints a summary. Steps 1 to 5 below cover the same work, if you need to see what the script does, or want to run one part by hand.

---

## 1. Install MSYS2

The script does this step by default. Follow these steps by hand only if the script stopped at MSYS2, or you want to install it yourself.

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
powershell -ExecutionPolicy Bypass -File .\setup.ps1
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

## 6. If you're using VS Code

VS Code is optional, but the course is written for it, and these steps set it up.

### Install VS Code and the extension

Install VS Code from [code.visualstudio.com](https://code.visualstudio.com). Open the repository root in VS Code, not a sub-folder, and open a `.c` file from a lesson.

VS Code offers to install the **C/C++ Extension Pack** (publisher Microsoft). Accept it, or install it from the Extensions view by searching for "C/C++ Extension Pack".

The pack includes CMake Tools. When it asks for a kit, choose **GCC 16.2.0 x86_64-w64-mingw32 (ucrt64)**, the MSYS2 compiler the course uses. Don't choose **[Scan for kits]** or **[Unspecified]**, since they can select a different compiler.

CMake Tools may report that it activated the runner's project in `lesson-runner`. That message is informational, and you can dismiss it.

Restart VS Code after `setup.ps1` has run, so it picks up the MSYS2 folder on your user PATH.

**Check:** the Extensions view lists C/C++ as installed, and the kit you chose appears in the status bar.

### Single-file lessons

Open the lesson's `.c` file, then:

- **Build:** Ctrl+Shift+B.
- **Build and run:** Terminal > Run Task > `C/C++: run active file`. The program's output appears in the terminal.
- **Debug:** press F5, and choose `Debug active C file (MSYS2 gdb)`. Click in the gutter first, if you want a breakpoint.

These compile only the file that's open, so they work for lessons with one source file.

**Check:** the Run Task above prints the lesson's output in the terminal.

### Multiple-file lessons

Some lessons use more than one source file, such as Chapter 13 (headers and multiple files). The build and run tasks compile only the open file, so they report `undefined reference` errors for functions in the other files. That's expected.

Build and run these lessons through the lesson runner: open the step and press **Run**. The runner builds every file the step's `CMakeLists.txt` lists.

In VS Code, open any `.c` file in the step's `src` folder, then use Terminal > Run Task:

- `C/C++: build lesson (CMake)` configures and builds the step's project.
- `C/C++: run lesson (CMake)` builds it, then runs the program.

The runner also works for these lessons: open the step and press **Run**.

To build from a terminal instead, open a terminal in the step's folder and run:

```pwsh
cd C:\Development\training\training-c\ch13-headers-and-multiple-files\02-include-guards
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build build
.\build\program.exe
```

Replace the `cd` path with the step's own folder. The `-S .` argument must point at the folder that holds the step's `CMakeLists.txt`.

### Messages you can ignore

- `"main.c" not found in ... compile_commands.json ... c_cpp_properties.json will be used`. The editor's settings cover the lesson's files, so this is informational.
- `CMake Tools detected and activated the project`. This is informational.

---

## 7. Your first run of each kind of step

Work through these once, to confirm each kind of example runs.

| Kind | Where | What you should see |
|---|---|---|
| Program with output | Ch01, Hello world | `Hello World!` and `I am learning C` in the Output pane. Press **Run** (or F5) |
| Program with a homework example | Ch01, Homework, Banner | The three lines of the banner. The example is hidden until you choose to reveal it |
| Quick picks | Ch01, Hello world | The Quick picks box stays hidden, since the step has one command |
| Visualizer | Ch16, Linear search | Press **Run**, then **Visualize**. A browser opens with the bars and the search stepping through them |
| Tests | Ch21, Running tests with CTest | Press **Test**. The output reports the test as passed |
| Quick pick with arguments | Final project, Core calculator | Open the Quick picks box and choose `run demo`. The eight examples and six error cases print |

The runner's own test steps, which exercise each kind of run, are in `resources\runner-test-steps`.

The first run of each step builds it, so it can take several seconds.

---

## 8. The static analyzer

The course checks memory errors with GCC's static analyzer, `-fanalyzer`. It's built into the compiler you already installed in step 2, so it needs no extra install. Add the option to any compile command:

```pwsh
gcc -fanalyzer -g main.c -o main.exe
```

**Check:** compile a program that frees the same pointer twice, and the analyzer reports a `double-'free'` warning.

On Linux and macOS, Valgrind is the usual run-time checker. It isn't available on Windows, so you can skip it there.

---

## Troubleshooting

| What you see | What to do |
|---|---|
| The setup script says MSYS2 isn't installed | Run the script from an Administrator PowerShell, since it installs by default, or install MSYS2 to `C:\msys64` (step 1). |
| The setup script says a package is missing | Run it again from an Administrator PowerShell, or run the pacman command it shows, in the MSYS2 UCRT64 shell. |
| `gcc` is version 13 or earlier | Run `pacman -Syu` in the MSYS2 UCRT64 shell, then open a new shell. |
| The runner says `Could not start CMake` | The build tool isn't in `C:\msys64\ucrt64\bin`. Check step 2, then restart the runner. |
| Run says the step didn't build a program | The step's `CMakeLists.txt` should build an executable called `program`. This is a problem in the step, not in your setup. |
| The runner window doesn't open | Check that `lesson-runner\build\WebView2Loader.dll` exists. If it doesn't, run `cmake --build build` in `lesson-runner`. |
| Run says the program couldn't start with "Access is denied", or the program is missing right after a build | Check that the repository is under `C:\Development`. If it is, report the step and the full error text, since your security software may be removing the new program. |
| The window opens with no icon, or the chapters don't load | Check the Output pane and the summary from `setup.ps1`, then send the first error to the development team. |
| The Output pane shows a `.WebView2` folder next to the runner | That's the browser's data folder, created on first run. It's normal, and can be ignored. |
| The Visualize button doesn't appear | The step's program must write `trace.js` when it runs. Press **Run** once, then check whether the button appears. |
| The Visualize page says "No trace found" | Press **Run** in the step first. The page reads the `trace.js` that the last run wrote. |
| The Visualize button opens a page that doesn't animate | Check that the Output pane shows no error from the program, then press **Visualize** again after a successful run. |
| `The preLaunchTask ... terminated with exit code -1` in VS Code | Restart VS Code. Setup adds the MSYS2 folder to your user PATH, and VS Code only sees that after a restart. |
| `libgcc_s_seh-1.dll was not found` | The MSYS2 folder isn't on your user PATH. Run `setup.ps1` again from an Administrator PowerShell, then restart VS Code. |
| `undefined reference to ...` in a single-file build | The lesson has more than one source file. Build it through the lesson runner. |
| The debug list shows only `(Windows) Launch`, or no gdb | gdb isn't installed. Run `setup.ps1` again from an Administrator PowerShell. |
| The kit list shows only Scan, Unspecified, or a different GCC | Choose the GCC 16.2.0 ucrt64 kit. If it isn't listed, run the kit scan from the CMake Tools menu, then choose it. |

If a problem isn't listed here, note the step you were on and the full error text, and report it. Include the Output pane text, because the first error is often the useful one.
