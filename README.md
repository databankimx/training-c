# DataBank IMX - C Developer Training

## License and Support

This repository is provided under the [MIT License](LICENSE). You are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell the materials in this repository, subject to the terms of that license.

This repository is provided for training and reference purposes only. DataBank IMX does not provide warranties, guarantees, maintenance, troubleshooting, implementation assistance, or technical support for this code or its use. Use it in any way permitted by the MIT License, but you are responsible for evaluating, adapting, testing, and supporting any use of it in your own environment.

---

## What is this repository for?

- C developer training curriculum for DataBank IMX, covering the language from first programs through memory, data structures, and the tools used to build and test C code, with a focus on reading and converting existing C code
- Chapter-by-chapter lessons, with code you can edit and run, and short quizzes
- A final project: a calculator built in stages, with a core track and a bonus track, each with a worked example
- A desktop lesson runner, built with C and WebView2, that lets you read lessons, edit and run each step, and run its tests

---

## A note on editors

This tutorial uses Visual Studio Code throughout. You're welcome to use whichever IDE you prefer, but that choice assumes you're already comfortable with your editor, including its debugger and build tools. Some lessons give steps specific to VS Code, such as setting a breakpoint or starting the debugger. If you use another IDE, you'll need to find the matching steps in its documentation.

The lesson runner, the build, and the tests don't depend on VS Code, so you can work through the course with any editor.

---

## About

- **Author:** [Scott McLean](mailto:smclean@databankimx.com)
- **Purpose:** Internal developer training curriculum for DataBank IMX

---

## DataBank Responsibilities for Custom Code

All DataBank employees, including those working with AI-assisted tools, are bound by the [Development Rules of Engagement](development-rules-of-engagement.md). That document defines the rules for quoting, approving, developing, reviewing, scanning, storing, and delivering custom code for client work.

Key obligations that apply to everyone on every custom code engagement:

- **You own the code you deliver.** This applies equally to hand-written code, AI-assisted code, and AI-generated code.
- **Code must be reviewed before delivery.** Review must confirm that the code works, meets DataBank standards, and is maintainable, and that the developer understands it well enough to explain, debug, and maintain it.
- **Code must be in source control before delivery.** All custom code must be committed to the appropriate DataBank GitHub Enterprise repository before it is delivered to a client.
- **CI scanning must pass before delivery.** Required checks are the standards policy scan, SonarQube, and Snyk.
- **All third-party dependencies must be license-vetted.** The license must permit closed-source commercial use. Copyleft or unclear licensing must be escalated before use.
- **Only approved AI tools may be used.** Use only IT-approved tools through company accounts.
- **Custom code is billable work.** Code must be tied to an approved quote or engagement before commitment or delivery.

See the [Development Rules of Engagement](development-rules-of-engagement.md) for the full policy.

---

## Textbook reference

The lessons draw on one reference: the **Wikibooks "C Programming" book**, at [en.wikibooks.org/wiki/C_Programming](https://en.wikibooks.org/wiki/C_Programming). It's free, and its text is licensed under the [Creative Commons Attribution-ShareAlike 4.0 License](https://creativecommons.org/licenses/by-sa/4.0/).

The lessons are written for this course. Where a lesson draws on the book, the step credits it, and the credit names the book and links to it. Any passage adapted from the book keeps the book's license, so adapted text stays under CC BY-SA 4.0. Before the course is published more widely, the reuse terms of the reference are confirmed on the book's own page.

---

## Setup and requirements

- **Windows 10 or 11**, with the WebView2 runtime (included with Windows 11)
- **MSYS2**, with the UCRT64 toolchain: gcc 14 or later, CMake, and Ninja
- **VS Code** with the C/C++ extension (recommended), or any editor you prefer

See [QUICKSTART.md](QUICKSTART.md) for a step-by-step guide.

### Quick start

From the repository root, in PowerShell:

```pwsh
powershell -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing
```

The script checks the toolchain, downloads the WebView2 SDK and cJSON into `resources\vendor`, makes the runner's icon, and builds the runner. It's safe to run more than once.

Then start the lesson runner:

```pwsh
cd lesson-runner
.\build\lesson-runner.exe
```

### Libraries used by the course

| Library | Where | Purpose | License |
|---|---|---|---|
| gcc (MSYS2 UCRT64) | Lessons and runner | Compiles every lesson program | GPL with the GCC runtime exception |
| CMake | Lessons and runner | Builds each step | BSD-3-Clause |
| Ninja | Lessons and runner | Runs the build | Apache 2.0 |
| WebView2 SDK | Lesson runner | The runner's window | Microsoft SDK license |
| cJSON | Lesson runner | Messages between the window and the back end | MIT |
| marked | Lesson runner (web folder) | Converts lesson Markdown to HTML | MIT |
| @viz-js/viz | Lesson runner (web folder) | Draws the diagrams in lessons | MIT, which wraps Graphviz (EPL-2.0) |
| highlight | Lesson runner (web folder) | Syntax coloring in the Source and Lesson panes | Written for this course |
| ImageMagick, librsvg | Setup only | Makes the runner's icon from the SVG logo. Not linked into any program | Apache 2.0 and LGPL-2.1, used as separate tools |

The GCC runtime exception and the Graphviz license should be reviewed under section 12 of the Development Rules of Engagement before the course leaves the company. The runner itself links only the MIT, BSD, Apache, and Microsoft-licensed components above.

### VS Code

Install the **C/C++** extension (publisher `Microsoft`). It checks your code as you type, and offers completion and navigation.

---

## Running the training

### Lesson Runner

The lesson runner is a desktop window, built with C and WebView2. It lets you browse chapters, read lessons, edit and run each step, and run its tests. Setup is in [QUICKSTART.md](QUICKSTART.md).

#### Finding lessons

The chapter list on the left shows each chapter, such as *Ch01 · Getting Started*. Click a chapter to show its steps, then click a step to open it.

- Chapters are listed in order. The final project comes after the numbered chapters.
- Each step is one folder. A step with a `CMakeLists.txt` has code you can run.
- Homework appears under its chapter, in its own list.

#### Reading and running a step

- The **Lesson** tab shows the step's lesson, with quizzes.
- The **Source** tab shows the step's `src/main.c`. It's an editor. Edits are kept in the runner until you click **Reset**, and nothing is written to the repository.
- Press **Run** (or F5) to build and run the step. The build status lines appear in the Output pane, followed by the program's output.
- Press **Test** to build the step and run its tests, for steps that have them.
- If a program asks for input, type in the input box under the Output pane, then press Enter or click **Go**.
- Press **Escape**, or click **Stop**, to stop a run. The Run button becomes Stop while a program runs.
- The **Backtrace** checkbox builds with debug information, so a debugger or a stack trace shows function names.
- Steps that declare options in their `CMakeLists.txt` show a checkbox for each option, next to Backtrace. Each checkbox starts at the default the step declares. Choices are kept while you move between steps, and reset when the runner restarts.

#### Quick picks

Each step's `commands.txt` lists quick picks. Choosing one fills the input box. A pick is either `run` or `test`, optionally followed by arguments for the program.

#### Homework and spoilers

Homework steps ask you to write your own program first. The Run button stays disabled until you choose **Show example (spoiler)**. Once you do, the example is available, and Run is enabled. Try the exercise before you reveal the example, since most of the learning happens while you're stuck.

#### Keyboard shortcuts

| Key | Action |
|---|---|
| F5 | Run the current step |
| Escape | Stop a running program, or cancel the input |

#### Troubleshooting

- **The window doesn't open:** check that the toolchain is in `C:\msys64\ucrt64\bin`, and run `setup.ps1` again.
- **Run says it could not start a build tool:** the MSYS2 toolchain isn't installed, or isn't in that folder.
- **A step says it didn't build a program:** the step's `CMakeLists.txt` should build an executable called `program`.
- **The first build is slow:** normal. Later builds are faster.

The runner's source code is in `lesson-runner/host` (the C back end) and `lesson-runner/web` (the page).

### Running lessons directly

Each step with code is a CMake project. From a terminal, in the step's folder:

```pwsh
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build build
.\build\program.exe
```

---

## Repository structure

```
training-c/
|- ch01-getting-started/         - Chapter 1: setup, the first programs, and the summary
|- ...                           - Further chapters, as they are written
|- final-project/                - The final project: a calculator, with a core and bonus items as homework steps
|- lesson-runner/                - The desktop lesson runner
|  |- host/                      - C back end: window, router, runner, discovery, and commands
|  |- web/                       - The page: HTML, CSS, JavaScript, and the vendored libraries
|  |- tools/                     - Test tools for the runner's parts
|- resources/                    - Vendored downloads (WebView2 SDK and cJSON), and the runner's test steps
|- setup.ps1                     - Prepares everything the runner needs
|- QUICKSTART.md                 - Step-by-step setup guide
|- AUTHORING.md                  - How to write and check lessons
```

Each chapter folder holds its sections, and each section holds its steps. A step is a folder with a `lesson.md`, and a `CMakeLists.txt` if it has code. Steps appear in the order of their names, so the number prefix keeps them in order.

### Course outline (in progress)

| Part | Chapters | Status |
|---|---|---|
| I - Basics | Getting started, variables and input, decisions, arrays, pointers, loops | In progress. Chapters 1 to 6 are written |
| II - Structuring programs | Functions, files, error handling, structures, opaque types and modules, polymorphism with function pointers, headers and multiple files | In progress. Chapters 7 to 14 (functions, files, error handling, structures, structures with behavior, composition and polymorphism, headers and multiple files, containers) are written |
| III - Additional topics | Dynamic memory and data structures, efficiency, searching and sorting, resource cleanup, ownership, generic code, callbacks, testing, threads with pthreads, build systems, debugging and sanitizers, modern C | Planned |
| Final project | A calculator, in two tracks: a core and bonus items | Planned |

The outline is a plan and may change as the lessons are written.

---

## Authorship note

This training curriculum was developed for internal use at DataBank. As with the other training repositories, I used generative AI in places for code review, cleanup, and turning rough notes into readable documentation.

~ Scott McLean, 2026

---

## Version history

| Date | Changes |
|---|---|
| 10/30/2026 | Chapter 1 written: setup, hello world, headers, comments, the summary, and two homework exercises. The repository's setup, QUICKSTART, and authoring guide written for C |
| 10/30/2026 | Chapter 2 written: variables, arithmetic, strings, user input, command-line arguments, the summary, and two homework exercises |
| 10/30/2026 | Chapter 3 written: booleans, logical operators, if statements, switch, the summary, and three homework exercises |
| 10/30/2026 | Chapters 1 to 3 checked against the C++ course. Lessons restored to full length where the C versions had dropped material. Homework rewritten to read input from the user, as the C++ exercises do, and the summaries cover every point of the C++ summaries |
| 10/30/2026 | Chapter 4 written: declaring arrays, initializing arrays, multidimensional arrays, the summary, and two homework exercises. Arrays of strings are deferred to the pointers chapter, and the C versions use char arrays or int arrays where the C++ versions use strings |
| 10/30/2026 | Chapter 5 written: pointers, pointers and arrays, the summary, and two homework exercises. C has no references, so the chapter covers pointers only. The homework does its swaps inline, since functions come in Chapter 7 |
| 10/30/2026 | Chapter 6 written: while loops, for loops, looping over arrays (C's replacement for the range-based loop), break and continue, Battleship, the summary, and two homework exercises. Chapter 5's folder was renamed to ch05-pointers to match its content |
| 10/30/2026 | Chapter 7 written: defining functions, parameters (C has no default values, so parameters are shown as copies), return values (C has no overloading, so each function has its own name), arrays as parameters, pointer parameters in place of references, recursion over a folder tree using the Windows file API, the summary, and two homework exercises |
| 10/30/2026 | Chapter 8 written: writing files, reading files, overwriting files and the fopen modes, the summary, and two homework exercises. The C version uses stdio.h in place of the C++ stream classes, and creates its data folder with the Windows API, since empty folders aren't kept in version control |
| 10/30/2026 | Chapter 9 written as Error Handling: return codes, errno, cleanup with goto, the summary, and two homework exercises. C has no exceptions, so the C++ exception steps are replaced by the techniques C provides |
| 10/30/2026 | Chapter 10 written: structures as variables (typedef and fixed-size text members), structures in functions (copies and pointers), initializing structures (C has no member defaults, so a function holds them), the summary, and two homework exercises |
| 10/30/2026 | Chapter 11 written as Structures with Behavior: structures and functions, functions that act on an object, init functions, hiding fields with an opaque type in a header, the summary, and two homework exercises (a bank account and a counter). C has no classes, so the class syntax is replaced by these techniques |
| 10/30/2026 | Chapter 12 written as Composition and Polymorphism: embedding a base structure, several parts and protection (C has no protected level), polymorphism with function pointers, the summary, and two homework exercises (shapes and employee pay). C has no inheritance or virtual functions, so these are replaced by composition and function pointers |
| 10/30/2026 | Chapter 13 written as Headers and Multiple Files: header and source, include guards, combining modules across seven files, the summary, and two homework exercises (a library and temperature utilities). The chapter closes Part II, since the C course's Part II covers chapters 7 to 13 |
| 10/30/2026 | Chapter 14 written as Containers: a growable vector and a hash table built from malloc, choosing between arrays, vectors, hash tables, and sorted arrays, the summary, and two homework exercises (a grade book and a word tally). C's standard library has no containers, so the chapter builds them. The dynamic-memory step was added to Chapter 5, with a discussion of double free and use after free as security flaws |

---

## Contact

- [Scott McLean](mailto:smclean@databankimx.com)
- [Dev Team](mailto:development@databankimx.com)
