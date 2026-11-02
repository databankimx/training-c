---
applyTo: "**/*"
---

# GitHub Copilot Instructions - DataBank Development Standards

## Purpose
This file defines how GitHub Copilot should generate code for DataBank IMX development teams.
All generated code must align with internal standards for quality, maintainability, security, and consistency.

## Scope
This repository is a **C training repository** (C23, built with CMake, GCC, and Ninja on MSYS2 UCRT64 for Windows). Follow the **Common Standards** section and the **C Project Instructions** section for all code generation in this repository.

---

## Common Standards

### General Principles
- Prioritize **readability, maintainability, and clarity** over brevity.
- Follow **DataBank coding standards** at all times.
- Assume code will be **reviewed, tested, and deployed to client environments**.
- Avoid unsafe, experimental, or non-production-ready patterns.
- Do not introduce unnecessary dependencies or frameworks.
- Third-party packages **must** have licenses that allow closed-source commercial use.
- Prefer existing project patterns over introducing new architectural or library choices.

### Architecture and Design
- Prefer clear separation of concerns.
- Avoid tightly coupled designs.
- Design for reuse and extensibility.
- Keep controllers, endpoints, and entry points thin; place business logic in services or domain components.
- Match the structure and conventions already used by the repository unless the user explicitly requests a redesign.

### Error Handling and Security
- Validate all inputs.
- Avoid exposing sensitive information in exceptions, logs, API responses, or console output.
- Follow least-privilege principles.
- Do not generate insecure defaults, hardcoded secrets, or bypass validation/authentication/authorization checks.
- Exception and error messages must be clear, concise, grammatically correct, and end with a period.

### Comments and Documentation
- Write comments only when necessary.
- Use clear, concise US-English.
- Document complex logic, non-obvious decisions, and important operational behavior.
- Avoid comments that merely restate the code.

### Source Control and Workflow
- All code must be tracked in source control.
- Commit early and often.
- Use meaningful commit messages.
- Link commits to tasks, issues, bugs, or enhancements where appropriate.
- Use branches and pull requests for review; do not commit directly to protected mainline branches.

### Code Reviews and Quality Gates
- All code must be reviewed before merge or delivery.
- Address correctness, readability, performance, security, and maintainability.
- Where applicable, code must pass SonarQube or other required quality gates before merge.

### Testing and QA Expectations
- Follow a **test-driven mindset** where practical.
- Ensure new code is testable.
- Include unit tests and integration tests where appropriate.
- Consider edge cases, invalid inputs, failure scenarios, and regression risk.

### Prohibited Practices
- Do NOT generate hardcoded credentials, secrets, tokens, or connection strings.
- Do NOT introduce unapproved third-party libraries.
- Do NOT expose internal implementation details unnecessarily.
- Do NOT produce code that violates DataBank IP, security, or delivery policies.

---

## C Project Instructions

### General Style

- Write clear, portable C targeting the C standard set in each lesson's `CMakeLists.txt` (C23 unless stated otherwise).
- Prefer explicit, maintainable code over compact or clever code.
- Use descriptive names for functions, variables, types, and parameters.
- Match the repository's existing layout, naming, and brace/indent style.
- Compile cleanly with warnings enabled (`-Wall -Wextra`) and fix warnings rather than suppressing them.

### Structure

- Keep functions small and single-purpose.
- Put declarations in headers with include guards and implementations in `.c` files.
- Use `static` for functions and variables that are private to a file.
- Keep `main` thin; place logic in separate functions.
- Reuse existing helpers and patterns before introducing new ones.

### Memory and Safety

- Check the result of every allocation and every I/O call.
- Free what you allocate, exactly once, and make ownership clear in names and comments.
- Never use unbounded functions such as `gets`, `strcpy`, `strcat`, or `sprintf`. Use bounded alternatives such as `fgets`, `snprintf`, and `memcpy` with explicit sizes.
- Validate input, array indexes, and pointer arguments before use.
- Avoid undefined behavior: uninitialized reads, out-of-bounds access, signed overflow, use after free.
- Use `const` wherever data is not modified.
- Code should run clean under AddressSanitizer, UndefinedBehaviorSanitizer, and Dr. Memory where applicable.

### Error Handling

- Return error codes or status values and report failures clearly; do not ignore return values.
- Release resources on every error path.
- Keep user-facing error messages clear and safe.

### Logging and Output

- Write errors to `stderr` and normal output to `stdout`.
- Never print secrets, credentials, tokens, or sensitive customer data.

### Documentation

- Add comments when behavior is not obvious. Keep inline comments minimal and purposeful.

### Testing

- Prefer simple, self-contained test programs that use `assert` or small check helpers, built and run through CMake/CTest.
- Do not add third-party test frameworks unless already required by the repository.
- Cover normal flow, invalid input, edge cases, and failure paths.

### Training Repository Notes

- This repository contains training content. Lesson files and homework are teaching material, not production code.
- Vendored third-party code under `resources/vendor/` is not ours to restyle or harden. Do not modify it.
- The lesson runner (`lesson-runner/`) is the only application code. Hold it to the full standards above.
- Follow the conventions in `AUTHORING.md` when writing or editing lessons.

---

## Copilot Behavior Guidelines

When generating code, Copilot should:
- Follow all applicable rules in this document automatically.
- Prefer existing project patterns over new ones.
- Match surrounding code style closely.
- Avoid speculative implementations.
- Ask for clarification through comments or generated TODO notes only when requirements are genuinely unclear.

---

## Definition of Done

Generated code is acceptable only if it:
- Runs successfully without warnings in the target project context.
- Passes required static analysis and quality gates where applicable.
- Follows the C standards in this file.
- Includes appropriate validation, error handling, and safe memory use.
- Is readable, maintainable, and testable.
