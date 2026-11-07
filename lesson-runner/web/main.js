import { highlightC } from "./highlight.js";
import { icon } from "./icons.js";
import { installExternalLinks } from "./links.js";
import { renderLessonInto } from "./lesson-render.js";
import { blockPageZoom, enableZoom } from "./zoom.js";

import { invoke, listen } from "./bridge.js";

const chaptersEl = document.querySelector("#chapters");
const stepsEl = document.querySelector("#steps");
const titleEl = document.querySelector("#title");
const subtitleEl = document.querySelector("#subtitle");
const output = document.querySelector("#output");
const runButton = document.querySelector("#run");
const testButton = document.querySelector("#test");
const stopButton = document.querySelector("#stop");
const clearButton = document.querySelector("#clear");
const inputForm = document.querySelector("#input-form");
const input = document.querySelector("#input");
const sendButton = document.querySelector("#send");
const themeToggle = document.querySelector("#theme");
const sourceView = document.querySelector("#source-view");
const lessonEl = document.querySelector("#lesson");
const editor = document.querySelector("#editor");
const gutter = document.querySelector("#gutter");
const highlightEl = document.querySelector("#highlight");
const modifiedEl = document.querySelector("#modified");
const resetButton = document.querySelector("#reset");
const spoilerEl = document.querySelector("#spoiler");
const revealButton = document.querySelector("#reveal");
const copyOutputButton = document.querySelector("#copy-output");
const copySourceButton = document.querySelector("#copy-source");
const popoutButton = document.querySelector("#popout");

// Visualize: opens the step's browser visualizer, which steps through the algorithm one comparison at a time.
// The visualizer is written by the step's program, so press Run first. The button is shown only for steps that have one.
const visualizeButton = document.createElement("button");
visualizeButton.textContent = "Visualize";
visualizeButton.className = testButton.className;
visualizeButton.title = "Open this step's visualizer in your browser";
visualizeButton.classList.add("hidden");
testButton.after(visualizeButton);
visualizeButton.addEventListener("click", () => {
  invoke("open_visualizer", { path: selectedStep.path }).catch((error) => appendNote(`${error}\n`, "stderr"));
});

// Source files: a step can have several .c and .h files. The drop-down above the editor picks one, and main.c is the default.
const fileSelect = document.createElement("select");
fileSelect.id = "file-select";
fileSelect.title = "Choose a source file in this step";
fileSelect.style.margin = "4px 8px";
sourceView.before(fileSelect);
let currentFile = null;
let originalMain = "";
let mainDraft = null;
let fileCount = 0;

// Quick picks: whole commands from the step's commands.txt. Choosing one fills the argument box.
const commandPick = document.createElement("select");
commandPick.className = "command-pick hidden";
commandPick.title = "Quick picks for this step";
input.before(commandPick);

// The drop-down is shown only on the Source tab, for steps with more than one source file.
function updateFileSelect() {
  fileSelect.classList.toggle("hidden", activeTab !== "source" || spoilerHidden || fileCount < 2);
}

// Backtrace toggle: when it is on, each run builds with debug information (-g) and stack-trace support, so a stack trace shows function names.
const BACKTRACE_KEY = "c-training-backtrace";
const backtraceLabel = document.createElement("label");
backtraceLabel.dataset.tip = "Show a stack trace when a program throws an exception";
backtraceLabel.style.fontSize = "12px";
backtraceLabel.style.marginLeft = "32px";
backtraceLabel.style.fontWeight = "normal";
backtraceLabel.style.letterSpacing = "normal";
const backtraceToggle = document.createElement("input");
backtraceToggle.type = "checkbox";
backtraceToggle.checked = localStorage.getItem(BACKTRACE_KEY) === "1";
backtraceToggle.addEventListener("change", () => {
  localStorage.setItem(BACKTRACE_KEY, backtraceToggle.checked ? "1" : "0");
});
backtraceLabel.append(backtraceToggle, " Backtrace");
// The checkbox sits to the right of the OUTPUT heading, in a group that keeps the two together on the left of the bar.
const paneLabel = document.querySelector(".pane-label");
const paneLeft = document.createElement("span");
paneLeft.className = "pane-left";
paneLabel.before(paneLeft);
paneLeft.append(paneLabel, backtraceLabel);

// Step options: one checkbox for each option(...) line in the step's CMakeLists.txt. Each checkbox starts at the default
// the step declares, and the choices are kept for this session only, so a restart returns them to the defaults.
const optionChoices = new Map();
const optionsGroup = document.createElement("span");
optionsGroup.className = "step-options";
optionsGroup.style.marginLeft = "24px";
paneLeft.append(optionsGroup);

function optionKey(step, name) {
  return step.path + "\u0000" + name;
}

function renderStepOptions(step) {
  optionsGroup.replaceChildren();
  for (const option of step.options ?? []) {
    const label = document.createElement("label");
    label.dataset.tip = option.description;
    label.style.fontSize = "12px";
    label.style.fontWeight = "normal";
    label.style.letterSpacing = "normal";
    label.style.marginRight = "16px";
    const box = document.createElement("input");
    box.type = "checkbox";
    const key = optionKey(step, option.name);
    box.checked = optionChoices.has(key) ? optionChoices.get(key) : option.default;
    box.addEventListener("change", () => optionChoices.set(key, box.checked));
    label.append(box, " " + option.name);
    optionsGroup.append(label);
  }
}

// The current value of each option the step declares, as name: true or false, for the run request.
function stepOptionValues(step) {
  const values = {};
  for (const option of step.options ?? []) {
    const key = optionKey(step, option.name);
    values[option.name] = optionChoices.has(key) ? optionChoices.get(key) : option.default;
  }
  return values;
}

let chapters = [];
let selectedChapter = null;
let selectedStep = null;
let homeworkMode = false;
let selectedSection = null;
let running = false;
let original = "";
let lessonText = "";
let popped = false;
let spoilerHidden = false;

// Which kind of run the argument box and quick picks are for: "run" or "test". Set by the Run and Test buttons.
let pickKind = "run";
let stepCommands = [];

// Output

/** Colors a line by what it says, so compiler status is not mistaken for an error. */
function outputClass(line, stream) {
  if (/^\s*(Compiling|Checking|Building|Configuring|Testing|Finished|Running|Fresh|Updating|Locking|Downloading|Adding)\b/.test(line)) {
    return "status";
  }
  if (/^\s*error(\[|:)/.test(line)) return "error";
  if (/^\s*warning(\[|:)/.test(line)) return "warning";
  return stream === "stderr" ? "stderr" : "";
}

function appendOutput(text, stream) {
  for (const line of text.split(/(?<=\n)/)) {
    const span = document.createElement("span");
    span.className = outputClass(line, stream);
    span.textContent = line;
    output.appendChild(span);
  }
  output.scrollTop = output.scrollHeight;
}

function appendNote(text, className) {
  const span = document.createElement("span");
  span.className = className;
  span.textContent = text;
  output.appendChild(span);
  output.scrollTop = output.scrollHeight;
}

// Buttons and chapters

function updateButtons() {
  const hasTests = Boolean(selectedStep && selectedStep.has_tests);
  const testOnly = hasTests && !selectedStep.has_main;
  // A step whose only program is its tests shows Test in place of Run. Otherwise the two sit side by side.
  // While a program runs, the Run button stays visible, because it has become Stop.
  runButton.classList.toggle("hidden", testOnly && !running);
  testButton.classList.toggle("hidden", !hasTests);
  visualizeButton.classList.toggle("hidden", !(selectedStep && selectedStep.has_visualizer));
  const ready = !running && Boolean(selectedStep) && selectedStep.has_code && !spoilerHidden;
  // While a program runs, the Run button is Stop, and it stays enabled so the program can be stopped.
  runButton.innerHTML = running ? "&#9632; Stop" : "&#9654; Run";
  runButton.classList.toggle("stop", running);
  runButton.disabled = running ? false : !ready;
  testButton.disabled = !ready;
  stopButton.disabled = !running;
  // While nothing is running, the input box takes the arguments for a run or a test.
  input.disabled = !running && !ready;
  sendButton.disabled = !running && !ready;
  input.placeholder = running ? "type a line for the program, then Enter" : "arguments, then Enter to run";
  sendButton.textContent = running ? "Send" : "Go";
  commandPick.classList.toggle("hidden", running || !ready || stepCommands.length <= 1);
}

// Parts group the chapters. Only one part is open at a time: opening a part closes the others. No part starts open.
let parts = [];
let openPart = null;

function renderChapters() {
  chaptersEl.replaceChildren();
  for (const part of parts) {
    const expanded = openPart === part.title;
    const partRow = document.createElement("div");
    partRow.className = "part" + (expanded ? " open" : "");
    const partChevron = document.createElement("span");
    partChevron.className = "chevron";
    partChevron.textContent = "\u25B8";
    const partLabel = document.createElement("span");
    partLabel.textContent = part.title;
    partRow.append(partChevron, partLabel);
    partRow.addEventListener("click", () => {
      openPart = expanded ? null : part.title;
      renderChapters();
    });
    chaptersEl.appendChild(partRow);
    if (!expanded) continue;

    for (const chapter of part.chapters) {
    const row = document.createElement("div");
    row.className = "chapter";
    if (chapter === selectedChapter) row.classList.add("open");
    if (chapter === selectedChapter && !homeworkMode && !selectedSection) row.classList.add("selected");

    const chevron = document.createElement("span");
    chevron.className = "chevron";
    chevron.textContent = "\u25B8";
    const label = document.createElement("span");
    label.textContent = chapter.title;

    row.append(chevron, label);
    row.addEventListener("click", () => selectChapter(chapter));
    chaptersEl.appendChild(row);

    // Sub-chapters appear under the selected chapter, collapsed until one is chosen.
    if (chapter === selectedChapter) {
      for (const section of chapter.sections) {
        const sectionRow = document.createElement("div");
        sectionRow.className = "section-row";
        if (section === selectedSection) sectionRow.classList.add("open", "selected");
        const sectionChevron = document.createElement("span");
        sectionChevron.className = "chevron";
        sectionChevron.textContent = "\u25B8";
        const sectionLabel = document.createElement("span");
        sectionLabel.textContent = section.title;
        sectionRow.append(sectionChevron, sectionLabel);
        sectionRow.addEventListener("click", (event) => {
          event.stopPropagation();
          selectSection(chapter, section);
        });
        chaptersEl.appendChild(sectionRow);
      }
    }

    // Homework appears only under the selected chapter, collapsed until it is chosen.
    if (chapter === selectedChapter && chapter.homework.length) {
      const homework = document.createElement("div");
      homework.className = "homework-row";
      if (homeworkMode) homework.classList.add("open", "selected");
      const homeworkChevron = document.createElement("span");
      homeworkChevron.className = "chevron";
      homeworkChevron.textContent = "\u25B8";
      const homeworkLabel = document.createElement("span");
      homeworkLabel.textContent = chapter.homework_title;
      homework.append(homeworkChevron, homeworkLabel);
      homework.addEventListener("click", (event) => {
        event.stopPropagation();
        selectHomework(chapter);
      });
      chaptersEl.appendChild(homework);
    }
    }
  }
}

function renderSteps() {
  stepsEl.replaceChildren();
  document.querySelector(".steps-heading").textContent = homeworkMode && selectedChapter ? selectedChapter.homework_title : "Steps";
  if (!selectedChapter) return;
  const items = homeworkMode ? selectedChapter.homework : selectedSection ? selectedSection.steps : selectedChapter.steps;
  for (const step of items) {
    const button = document.createElement("button");
    button.className = "step";
    if (step === selectedStep) button.classList.add("selected");
    button.textContent = step.title;
    button.addEventListener("click", () => selectStep(selectedChapter, step));
    stepsEl.appendChild(button);
  }
}

function selectSection(chapter, section) {
  revealPartOf(chapter);
  selectedChapter = chapter;
  selectedSection = section;
  homeworkMode = false;
  renderChapters();
  renderSteps();
  showOverview(section.path, "section:" + section.path, section.title, chapter.title);
}

async function selectHomework(chapter) {
  revealPartOf(chapter);
  selectedChapter = chapter;
  homeworkMode = true;
  selectedSection = null;
  output.replaceChildren();
  selectedStep = null;
  spoilerHidden = false;
  titleEl.textContent = chapter.homework_title;
  subtitleEl.textContent = chapter.title;
  renderChapters();
  renderSteps();
  updateButtons();
  setTab("lesson");
  rememberLessonScroll();
  lessonText = await invoke("read_lesson", { path: chapter.homework_path });
  renderLesson();
  showLessonAt("homework:" + chapter.homework_path);
  invoke("set_lesson", { title: `${chapter.title} · ${chapter.homework_title}`, text: lessonText });
}

// Selecting a chapter or section shows its overview lesson, if it has one.
async function showOverview(path, key, title, subtitle) {
  selectedStep = null;
  spoilerHidden = false;
  titleEl.textContent = title;
  subtitleEl.textContent = subtitle;
  updateButtons();
  setTab("lesson");
  rememberLessonScroll();
  lessonText = await invoke("read_lesson", { path });
  if (!lessonText.trim()) lessonText = `${title} has no overview yet.`;
  renderLesson();
  showLessonAt(key);
  invoke("set_lesson", { title, text: lessonText });
}

// Opening a chapter, section, homework, or step opens the part it belongs to, closing the others, so the selection is visible.
function revealPartOf(chapter) {
  const owner = parts.find((part) => part.chapters.includes(chapter));
  if (owner) openPart = owner.title;
}

function selectChapter(chapter) {
  revealPartOf(chapter);
  selectedChapter = chapter;
  selectedSection = null;
  homeworkMode = false;
  renderChapters();
  renderSteps();
  revealSubChapters();
  showOverview(chapter.path, "chapter:" + chapter.path, chapter.title, "");
}

// After a chapter is selected, scroll the chapters pane just far enough that its sub-chapters and Homework sit above the splitter below it.
function revealSubChapters() {
  const rows = chaptersEl.querySelectorAll(".section-row, .homework-row");
  const last = rows.length ? rows[rows.length - 1] : chaptersEl.querySelector(".chapter.open");
  if (!last) return;
  requestAnimationFrame(() => {
    const pane = chaptersEl.getBoundingClientRect();
    const row = last.getBoundingClientRect();
    const overflow = row.bottom - pane.bottom;
    if (overflow > 0) chaptersEl.scrollTop += overflow + 4;
  });
}

// Links in an overview lesson, such as #goto/s02-example-structs, select the named child.
listen("goto", (event) => {
  const chapter = selectedChapter;
  if (!chapter) return;
  const name = event.payload;
  const section = chapter.sections.find((s) => s.name === name);
  if (section) {
    selectSection(chapter, section);
    return;
  }
  const step = (selectedSection ? selectedSection.steps : chapter.steps).find((s) => s.name === name);
  if (step) selectStep(chapter, step);
});

async function selectStep(chapter, step) {
  revealPartOf(chapter);
  // A program that is still running belongs to the step being left, so stop it before showing the new one.
  if (running) await stop();
  selectedChapter = chapter;
  homeworkMode = chapter.homework.includes(step);
  selectedSection = chapter.sections.find((section) => section.steps.includes(step)) || null;
  if (selectedStep !== step) {
    output.replaceChildren();
    clearOutputFiles();
  }
  selectedStep = step;
  renderStepOptions(step);
  titleEl.textContent = step.title;
  subtitleEl.textContent = homeworkMode ? `${chapter.title} · ${chapter.homework_title}` : selectedSection ? selectedSection.title : chapter.title;
  spoilerHidden = homeworkMode && !isRevealed(step);
  renderChapters();
  renderSteps();
  updateButtons();
  setTab(activeTab);
  input.value = "";
  pickKind = step.has_main ? "run" : "test";
  loadCommandPicks(step);
  if (spoilerHidden) {
    await loadLesson(step);
  } else {
    await Promise.all([loadSource(step), loadLesson(step)]);
  }
}

// Source editor

function renderEditor() {
  const text = editor.value;
  highlightEl.innerHTML = highlightC(text) + "\n";
  const lineCount = text.split("\n").length;
  gutter.textContent = Array.from({ length: lineCount }, (_, i) => i + 1).join("\n");
  const modified = text !== original;
  modifiedEl.classList.toggle("hidden", !modified);
  resetButton.disabled = !modified;
}

function syncScroll() {
  highlightEl.scrollTop = editor.scrollTop;
  highlightEl.scrollLeft = editor.scrollLeft;
  gutter.scrollTop = editor.scrollTop;
}

async function loadSource(step) {
  mainDraft = null;
  originalMain = "";
  currentFile = null;
  if (!step.has_code) {
    fileSelect.replaceChildren();
    fileCount = 0;
    updateFileSelect();
    editor.value = "// This step has no code to run. See the Lesson tab.";
    original = editor.value;
    editor.readOnly = true;
    renderEditor();
    return;
  }
  try {
    const files = await invoke("list_source_files", { path: step.path });
    fileCount = files.length;
    updateFileSelect();
    fileSelect.replaceChildren(
      ...files.map((file) => {
        const option = document.createElement("option");
        option.value = file;
        option.textContent = file;
        return option;
      }),
    );
    await loadSourceFile(step, "main.c");
  } catch (error) {
    original = "";
    editor.value = `${error}`;
    renderEditor();
  }
}

/** Shows one source file. Only main.c can be edited, because only main.c is sent to the runner. */
async function loadSourceFile(step, file) {
  if (currentFile === "main.c" && !editor.readOnly) mainDraft = editor.value;
  currentFile = file;
  fileSelect.value = file;
  const text = (await invoke("read_source", { path: step.path, file })).replace(/\r\n/g, "\n");
  if (file === "main.c") {
    originalMain = text;
    editor.value = mainDraft ?? text;
    editor.readOnly = false;
  } else {
    editor.value = text;
    editor.readOnly = true;
  }
  original = text;
  editor.scrollTop = 0;
  renderEditor();
}

fileSelect.addEventListener("change", () => {
  if (selectedStep) loadSourceFile(selectedStep, fileSelect.value);
});

function resetEditor() {
  editor.value = original;
  renderEditor();
}

editor.addEventListener("input", renderEditor);
editor.addEventListener("scroll", syncScroll);
editor.addEventListener("keydown", (event) => {
  if (event.key === "Tab") {
    event.preventDefault();
    const start = editor.selectionStart;
    editor.setRangeText("    ", start, editor.selectionEnd, "end");
    renderEditor();
  }
});
resetButton.addEventListener("click", resetEditor);

// Lesson (Markdown)

const REVEALED_PREFIX = "c-training-revealed:";

function isRevealed(step) {
  return localStorage.getItem(REVEALED_PREFIX + step.path) === "1";
}

async function loadLesson(step) {
  rememberLessonScroll();
  lessonText = await invoke("read_lesson", { path: step.path });
  // Once a homework example has been revealed, its walkthrough is shown with the exercise.
  if (homeworkMode && isRevealed(step)) {
    const solution = await invoke("read_step_file", { path: step.path, file: "solution.md" });
    if (solution.trim()) lessonText += "\n\n---\n\n" + solution;
  }
  renderLesson();
  showLessonAt(step.path);
  invoke("set_lesson", { title: step.title, text: lessonText });
}

function renderLesson() {
  if (popped) {
    const note = document.createElement("p");
    note.textContent = "This lesson is open in its own window.";
    const dock = document.createElement("button");
    dock.innerHTML = `${icon("dock")} Dock lesson here`;
    dock.addEventListener("click", () => invoke("dock_lesson"));
    lessonEl.replaceChildren(note, dock);
    return;
  }
  if (!lessonText.trim()) {
    lessonEl.textContent = "No lesson text yet for this step.";
    return;
  }
  lessonEl.innerHTML = "";
  renderLessonInto(lessonEl, lessonText);
}

// Quick picks for the step. Only the picks for the current kind of run (run or test) are listed.
async function loadCommandPicks(step) {
  const commands = step.has_code ? await invoke("read_commands", { path: step.path }) : [];
  if (selectedStep !== step) return;
  stepCommands = commands;
  renderCommandPick();
}

function renderCommandPick() {
  commandPick.replaceChildren();
  const placeholder = document.createElement("option");
  placeholder.textContent = "Quick picks";
  placeholder.value = "";
  commandPick.appendChild(placeholder);
  for (const command of stepCommands) {
    // A pick may start with NAME=value settings, such as IGNORE_CASE=1. They stay in the box, and the run or test word gives the kind.
    const match = command.match(/^((?:\w+=\S+\s+)*)(run|test)\s*(.*)$/);
    const option = document.createElement("option");
    option.textContent = command;
    option.value = match ? match[1] + match[3] : command;
    option.dataset.kind = match && match[2] === "test" ? "test" : "run";
    commandPick.appendChild(option);
  }
  updateButtons();
}

commandPick.addEventListener("change", () => {
  // Choosing a pick sets the kind of run as well as the arguments. Choosing "test" (no arguments) clears the box.
  const option = commandPick.selectedOptions[0];
  if (option && option.dataset.kind) pickKind = option.dataset.kind;
  input.value = commandPick.value;
  input.focus();
});

// Running

// The argument box's text, split into separate arguments. An empty box gives no arguments.
function boxArgs() {
  return input.value.trim().split(/\s+/).filter(Boolean);
}

async function run(mode, args = []) {
  if (!selectedStep || running) return;
  // With no mode given (F5), a test-only step runs its tests, and any other step runs its program.
  const kind = mode ?? (selectedStep.has_tests && !selectedStep.has_main ? "test" : "run");
  running = true;
  clearOutputFiles();
  output.replaceChildren();
  updateButtons();
  // Send main.c only when its text differs from the file on disk. Other files are read-only.
  const mainText = currentFile === "main.c" ? editor.value : mainDraft ?? originalMain;
  const edited = mainText !== originalMain ? mainText : null;
  try {
    await invoke("run_step", { path: selectedStep.path, source: edited, backtrace: backtraceToggle.checked, test: kind === "test", args, options: stepOptionValues(selectedStep) });
  } catch (error) {
    appendOutput(`${error}\n`, "stderr");
    running = false;
    updateButtons();
  }
}

async function stop() {
  if (!running) return;
  await invoke("stop_run");
}

async function sendInput(event) {
  event.preventDefault();
  // While a program is running, the box sends a line to it. Otherwise it gives the arguments for a run.
  if (!running) {
    if (!selectedStep) return;
    const args = boxArgs();
    run(pickKind, args);
    return;
  }
  const text = input.value;
  input.value = "";
  appendNote(`${text}\n`, "input");
  try {
    await invoke("send_input", { text: `${text}\n` });
  } catch (error) {
    appendNote(`${error}\n`, "stderr");
  }
}

// Each lesson remembers where the reader left it. A lesson opened for the first time starts at the top.
const lessonScroll = new Map();
let currentLessonKey = null;
let pendingLessonScroll = 0;

function rememberLessonScroll() {
  if (currentLessonKey !== null && !lessonEl.classList.contains("hidden")) {
    lessonScroll.set(currentLessonKey, lessonEl.scrollTop);
  }
}

function applyLessonScroll() {
  // Set the offset now, then again once the new content has laid out, and again shortly
  // after, since diagrams and quizzes can change the height of the lesson as they render.
  const offset = pendingLessonScroll;
  lessonEl.scrollTop = offset;
  requestAnimationFrame(() => {
    lessonEl.scrollTop = offset;
  });
  setTimeout(() => {
    lessonEl.scrollTop = offset;
  }, 150);
}

function showLessonAt(key) {
  currentLessonKey = key;
  pendingLessonScroll = lessonScroll.get(key) ?? 0;
  applyLessonScroll();
}

let activeTab = "source";
function setTab(name) {
  if (activeTab === "lesson" && name !== "lesson") rememberLessonScroll();
  activeTab = name;
  document.querySelectorAll(".tab").forEach((tab) => {
    tab.classList.toggle("active", tab.dataset.tab === name);
  });
  const showSource = name === "source" && !spoilerHidden;
  sourceView.classList.toggle("hidden", !showSource);
  spoilerEl.classList.toggle("hidden", !(name === "source" && spoilerHidden));
  lessonEl.classList.toggle("hidden", name !== "lesson");
  document.querySelector("#reset").classList.toggle("hidden", !showSource);
  modifiedEl.classList.toggle("hidden", !showSource || editor.value === original);
  updateFileSelect();
  if (name === "lesson") applyLessonScroll();
}

runButton.addEventListener("click", () => {
  // While a program is running, the Run button is Stop.
  if (running) {
    stop();
    return;
  }
  pickKind = "run";
  renderCommandPick();
  run("run", boxArgs());
});
testButton.addEventListener("click", () => {
  pickKind = "test";
  renderCommandPick();
  run("test", boxArgs());
});

// A short message that fades out. The text is shown for a moment, then removed.
function showToast(message) {
  const toast = document.createElement("div");
  toast.className = "toast";
  toast.textContent = message;
  document.body.append(toast);
  setTimeout(() => toast.classList.add("fade"), 400);
  setTimeout(() => toast.remove(), 1250);
}

// Undocumented: Ctrl+Shift+Alt+Backspace clears quiz answers and revealed solutions. Backtrace and theme settings are kept.
// It listens in the capture phase, so the editor and other controls cannot swallow the key before it arrives.
window.addEventListener(
  "keydown",
  (event) => {
    if (!(event.ctrlKey && event.shiftKey && event.altKey && event.key === "Backspace")) return;
    event.preventDefault();
    for (const key of Object.keys(localStorage)) {
      if (key.startsWith("c-training-quiz:") || key.startsWith("c-training-revealed:")) {
        localStorage.removeItem(key);
      }
    }
    if (selectedStep) selectStep(selectedChapter, selectedStep);
    showToast("Progress reset");
  },
  true,
);

// Spoiler: reveals the example solution for a homework step, and remembers that it was revealed.
revealButton.addEventListener("click", async () => {
  if (!selectedStep) return;
  localStorage.setItem(REVEALED_PREFIX + selectedStep.path, "1");
  spoilerHidden = false;
  updateButtons();
  await Promise.all([loadSource(selectedStep), loadLesson(selectedStep), loadCommandPicks(selectedStep)]);
  setTab("source");
});

// Copy and pop-out

function copyText(text) {
  navigator.clipboard.writeText(text).catch((error) => appendNote(`${error}\n`, "stderr"));
}

copyOutputButton.addEventListener("click", () => copyText(output.textContent));
copySourceButton.addEventListener("click", () => {
  const onLesson = document.querySelector(".tab.active").dataset.tab === "lesson";
  copyText(onLesson ? lessonText : editor.value);
});
popoutButton.addEventListener("click", () => {
  invoke("open_lesson_window").catch((error) => appendNote(`${error}\n`, "stderr"));
});
installExternalLinks(lessonEl);

// Ctrl + mouse wheel zooms each pane's text. The rest of the window keeps its size.
blockPageZoom();
enableZoom(output, "output", 13);
enableZoom(sourceView, "source", 13);
enableZoom(lessonEl, "lesson", 14);
stopButton.addEventListener("click", stop);
clearButton.addEventListener("click", () => output.replaceChildren());
inputForm.addEventListener("submit", sendInput);
themeToggle.addEventListener("change", () => {
  document.body.classList.toggle("light", themeToggle.checked);
  invoke("set_theme", { light: themeToggle.checked });
});
document.querySelectorAll(".tab").forEach((tab) => {
  tab.addEventListener("click", () => setTab(tab.dataset.tab));
});

document.addEventListener("keydown", (event) => {
  if (event.key === "F5") {
    event.preventDefault();
    run(undefined, boxArgs());
  } else if (event.key === "Escape") {
    if (running) {
      stop();
    } else if (editor.value !== original) {
      resetEditor();
    }
  }
});

listen("lesson-popped", () => {
  popped = true;
  renderLesson();
});

listen("lesson-docked", () => {
  popped = false;
  renderLesson();
});

listen("run-output", (event) => {
  appendOutput(event.payload.text, event.payload.stream);
});

// Output files: a run that writes files lists them over the bottom right of the Output pane, each with a View button.
let outputFilesEl = null;

function clearOutputFiles() {
  outputFilesEl?.remove();
  outputFilesEl = null;
}

function showOutputFiles(files) {
  clearOutputFiles();
  if (!files.length) return;
  // A zero-height wrapper sits just below the Output text, so the buttons float above its bottom edge, over the text.
  outputFilesEl = document.createElement("div");
  outputFilesEl.className = "output-files-anchor";
  const stack = document.createElement("div");
  stack.className = "output-files";
  for (const file of files) {
    const button = document.createElement("button");
    button.className = "view-file";
    button.textContent = `View ${file.name}`;
    button.title = file.path;
    button.addEventListener("click", () => {
      invoke("open_file", { path: file.path }).catch((error) => appendNote(`${error}\n`, "stderr"));
    });
    stack.append(button);
  }
  outputFilesEl.append(stack);
  output.after(outputFilesEl);
}

listen("output-files", (event) => showOutputFiles(event.payload));

listen("run-finished", (event) => {
  const code = event.payload.code;
  appendNote(`\n\u2014 Finished${code === null ? "" : ` with exit code ${code}`} \u2014\n`, "status");
  running = false;
  updateButtons();
});

// Splitters: drag to resize the sidebar, the steps list, and the source pane.

function drag(handle, onMove) {
  handle.addEventListener("pointerdown", (event) => {
    event.preventDefault();
    handle.setPointerCapture(event.pointerId);
    handle.addEventListener("pointermove", onMove);
    const stopDrag = () => {
      handle.removeEventListener("pointermove", onMove);
      handle.removeEventListener("pointerup", stopDrag);
    };
    handle.addEventListener("pointerup", stopDrag);
  });
}

const root = document.documentElement.style;

drag(document.querySelector("#split-sidebar"), (event) => {
  const width = Math.min(Math.max(event.clientX, 220), window.innerWidth - 420);
  root.setProperty("--sidebar-width", `${width}px`);
});

drag(document.querySelector("#split-tree"), (event) => {
  const top = chaptersEl.getBoundingClientRect().top;
  const height = Math.min(Math.max(event.clientY - top, 80), window.innerHeight - top - 200);
  root.setProperty("--chapters-height", `${height}px`);
});

drag(document.querySelector("#split-source"), (event) => {
  const height = Math.min(Math.max(window.innerHeight - event.clientY, 140), window.innerHeight - 220);
  root.setProperty("--source-height", `${height}px`);
});

invoke("list_parts")
  .then((result) => {
    parts = result;
    // No part starts open, so the menu opens showing only the part headings.
    openPart = null;
    chapters = result.flatMap((part) => part.chapters);
    renderChapters();
  })
  .catch((error) => appendOutput(`${error}\n`, "stderr"));

copyOutputButton.innerHTML = icon("copy");
clearButton.innerHTML = icon("eraser");
copySourceButton.innerHTML = icon("copy");
popoutButton.innerHTML = icon("popout");
document.querySelector("#moon").innerHTML = icon("moon");
document.querySelector("#sun").innerHTML = icon("sun");

updateButtons();
setTab("source");
