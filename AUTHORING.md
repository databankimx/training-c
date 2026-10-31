# Authoring Guide

This guide is for anyone adding or changing lessons in `training-c`. It explains how the lesson runner finds content, how to write a step and its quizzes, how to build homework with a spoiler, and what to check before a change is committed.

Read the [README](README.md) first for an overview of the course. For setup, see [QUICKSTART.md](QUICKSTART.md).

---

## How the runner finds content

The lesson runner reads the repository's folders when it starts. Names matter.

| Level | Folder name | Example | Title shown in the runner |
|---|---|---|---|
| Chapter | `chNN-name` at the repository root | `ch01-getting-started` | `Ch01 · Getting Started` |
| Section (optional) | `sNN-name` inside a chapter | `s01-pointers` | `Pointers` |
| Step | `NN-name` inside a chapter or section | `01-hello` | `Hello` |
| Homework | `homework` folder inside a chapter | `ch01-getting-started/homework/01-introduce-yourself` | Listed under the chapter's homework label |
| Extra section | `final-name` at the repository root | `final-project` | `Final Project`, with no chapter number, after the numbered chapters |

Some rules follow from this:

- **Use two digits for numbers,** such as `01`, so the order is right. Folders are sorted by name.
- **Words are capitalized automatically.** `01-hello-async` shows as `Hello async`. Acronyms and special words come from lists in `lesson-runner\host\discovery.c`. The all-caps list covers words such as `c`, `api`, `io`, and `json`, so `c` shows as `C`. To change a title, add the word to that list and rebuild the runner.
- **A folder with neither a `lesson.md` nor a `CMakeLists.txt` isn't a step.** It's ignored.
- **A step has code when it has a `CMakeLists.txt`.** Without one, the step shows its lesson only, and Run is disabled.
- **A homework folder can name its own label.** A `title.txt` file inside it replaces the word "Homework" in the menu, as the final project's does.

Inside a step, the runner looks for these files:

| File | Used for |
|---|---|
| `lesson.md` | The lesson text, shown in the **Lesson** tab |
| `CMakeLists.txt` | How the step is built. See the next section |
| `src/main.c` | The step's main source file, which can be edited in the **Source** tab and is sent to the runner on Run |
| Other `.c` and `.h` files | Shown in the file selector when the step has more than one source file |
| `tests/` | Test sources. Their names are shown with a `tests/` prefix |
| `commands.txt` | Quick picks. See below |
| `solution.md` | Homework only. Shown after the example is revealed |

## The CMake convention

Each step builds with CMake. The runner depends on three rules in the step's `CMakeLists.txt`:

1. **An executable target named `program`.** Run builds the step and then runs `program.exe`. A step without it shows an error when Run is pressed.
2. **Tests declared with `add_test`.** The Test button runs `ctest` on the step's build. A step with `add_test` in its CMake file shows the Test button.
3. **The backtrace switch.** The runner passes `LESSON_BACKTRACE=ON` when the Backtrace checkbox is on. The step should add `-g` in that case, so a debugger or a stack trace shows function names.

A minimal step looks like this:

```cmake
cmake_minimum_required(VERSION 3.25)
project(hello LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Wpedantic)

if(LESSON_BACKTRACE)
    add_compile_options(-g)
endif()

add_executable(program src/main.c)
```

A step with tests adds a second executable, and registers it with CTest:

```cmake
add_executable(tests tests/test_math.c src/math.c)
target_include_directories(tests PRIVATE src)

enable_testing()
add_test(NAME math COMMAND tests)
```

Copy an existing step from `ch01-getting-started` when you start a new one. It already has these rules in place. The runner's own test steps, which exercise each kind of run, are kept in `resources\runner-test-steps`.

## Quick picks

`commands.txt` lists quick picks, one per line. Each line is either `run` or `test`, optionally followed by arguments for the program:

```
run demo
test
```

`NAME=value` words at the start of a line become environment variables for that run only, such as `IGNORE_CASE=1 run`.

## Writing a step

Each step explains one idea. A complete beginner should be able to follow it, and should know what to expect.

### The structure of a step

Use this order. Each part is a heading, and sections are separated by a line with three dashes (`---`).

1. **The heading.** A short title, such as `## Reading input`.
2. **The explanation.** Introduce the idea, then show the code in a block. Explain what the code does in the sentences around it, not in comments alone.
3. **Expected output.** Show what the program prints, in a plain block with no language.
4. **Try it in the runner.** What to change in `src/main.c`, and what should happen. The comments in `src/main.c` should match this section, so the reader can find the `// Try:` comment.
5. **Quiz.** Optional, but most steps that teach a concept include one.
6. **The source.** A line with the book reference, in italics, where the step draws on one.

Write in US English. Use hyphens, not em dashes. Don't use emojis.

### Code samples

- **Runnable code** goes in `src/main.c`, in a step with a `CMakeLists.txt`. Use the C17 standard. Warnings are on, and a step should build without any.
- **Snippets** that show part of a program, or that won't compile on purpose, use a block marked `c,ignore`. The runner shows these, and doesn't try to run them.
- **Output blocks** have no language.
- **Pipes and buffering.** Output sent to a pipe is buffered, so a prompt with no newline may not appear until after input is typed. Steps that prompt should call `fflush(stdout)`, and the lesson can say why.

### Warnings

- Name unused parameters with `(void)`, or leave the name out of the definition.
- When something is unused on purpose, say so in a comment.
- Treat any warning in the runner's Output pane as a problem to fix before the step is committed.

### Programs that wait

A program that runs until stopped, or waits for input, needs its lesson to say so:

- **Stop (Esc)** ends it. Say so.
- Say what the reader should see in the Output pane, which may be nothing.

---

## Writing quizzes

A quiz checks one idea. The runner's format uses four backticks around the block, so code can appear inside it:

````
````quiz
Which header declares printf?
○ <stdlib.h>
→ Not quite. <stdlib.h> holds general utilities.
◉ <stdio.h>
→ Yes. <stdio.h> declares the standard input and output functions.
````
````

- The question is one line, or a short paragraph and a code block before the quiz block.
- Lines beginning `○` are wrong answers. Lines beginning `◉` are right answers. Each answer is followed by a line beginning `→`, which explains it. Start a correct answer's explanation with `Yes.`, and a wrong answer's with `Not quite.`.
- **Single answer only.** The runner has no checkboxes. If a source question allows several correct answers, make one yes-or-no question per option.
- **Short-answer questions** give the accepted answer in square brackets, such as `[ main ]`. Use `|` to accept more than one answer.

### Sources

The course's lessons are written for this course. Where a lesson draws on text from another source, the source is credited in the step, in italics, before the quiz. The course's reference is the Wikibooks "C Programming" book, which is licensed under CC BY-SA 4.0. Any passage adapted from it must keep that license, and the credit must name the book and link to it. Write explanations in your own words wherever possible.

---

## Writing homework

Homework is a step where the student writes their own program first. The runner keeps the example solution hidden until the student reveals it.

Each homework step is a folder in `chNN-name/homework/`, and contains:

| File | Purpose |
|---|---|
| `lesson.md` | The exercise. State the problem, the requirements, and the expected output. Give hints and a check-your-work section. Don't give the solution. |
| `CMakeLists.txt` and `src/main.c` | The example solution. The student doesn't see it until they reveal it. |
| `commands.txt` | Quick picks, such as `run` and `test`. |
| `solution.md` | A walkthrough of the example. Shown after the reveal. Explain the decisions, not each line. |

While the student hasn't revealed the example, the Run button is disabled. When they reveal it, Run is enabled, and the walkthrough is shown.

Exercises that aren't from a reference say so at the bottom of the lesson: `*This exercise is not from the book.*`

---

## Chapter structure

Every chapter ends the same way:

1. The teaching steps, in order. Each one has a lesson, and code where the lesson needs it.
2. A final `NN-summary` step, placed after the teaching steps so it's last in the steps list. It recaps the chapter in a few bullet points, and ends with a quiz of two or three questions.
3. A `homework` folder, with at least two exercises, each in its own `NN-name` folder. A chapter can have more when a topic needs them. The homework is listed under the chapter in the runner, and each exercise has its example hidden behind a spoiler.

Don't use a separate section for the summary. A summary section appears in the chapter pane, and the summary belongs at the end of the steps list. A step can move into a new section if a chapter grows too long, as long as the lesson links are updated.

## Quality checks before committing

1. **Build the step.** Press **Run** in the runner, or run `cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc` and then `cmake --build build` in the step's folder. The output should match the lesson's expected output exactly.
2. **Run the tests.** For steps with tests, press **Test**, or run `ctest --test-dir build --output-on-failure`.
3. **Check for warnings.** The build should be clean.
4. **Read the lesson aloud.** The explanation should match the code, and the Try section should match the comments.
5. **Check the quizzes.** Each answer should be correct, and only one option should be marked `◉`.
6. **Check the names.** Folder names follow the rules above, and the titles the runner shows read well.
7. **Check the style.** US English, hyphens rather than em dashes, no emojis.
8. **Check for secrets and paths.** No tokens, no personal paths, and no machine-specific settings.
9. **Update the docs.** When a chapter or step is added, renamed, or removed, update the README's repository tree and course outline, the chapter names in QUICKSTART, and any example names in this guide.

---

## Common mistakes

- **A missing `program` target.** The step builds, but Run reports that it didn't build a program. Name the executable `program`.
- **Tests that aren't registered with `add_test`.** The Test button won't appear. Register them.
- **An expected output that isn't what the program prints.** Run the step, and copy the output exactly.
- **A `// Try:` comment that doesn't match the Try section.** Keep them the same.
- **A quiz with two correct answers.** The runner accepts one. Split the question.
- **A homework solution in the lesson.** The solution belongs in `src/main.c` and `solution.md`.
- **A prompt that doesn't show.** Add `fflush(stdout)` after the prompt.

---

*This guide is for the training repository. Questions about the runner itself go to the development team.*
