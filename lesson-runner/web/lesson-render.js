import { highlightC } from "./highlight.js";
import { icon } from "./icons.js";
import { marked } from "./vendor/marked.js";

// Diagrams are Graphviz source in a ```dot block. The Graphviz library is loaded the first
// time a diagram is needed, from src/vendor/viz.js.
let vizPromise = null;

function getViz() {
  if (!vizPromise) vizPromise = import("./vendor/viz.js").then((module) => module.instance());
  return vizPromise;
}

// Quizzes are written in a lesson as a fenced block:
//
//   ````quiz
//   Question text (Markdown is allowed)
//   ○ a wrong choice
//   → why it is wrong
//   ◉ the right choice
//   → why it is right
//   ````
//
// A line starting with → explains the choice above it. A short-answer question has no
// choices and gives its answer in brackets, with an optional → line for a wrong answer:
//
//   ````quiz
//   What is the name of the tool that reads CMake files and writes the build files?
//   [ cmake ]
//   → cmake reads the CMake files and writes the build files. g++ is the compiler that builds the program.
//   ````
//
// Several answers can be accepted, separated by "|": [ main | int main ]

const STORE = "c-training-quiz:";

function hashText(text) {
  let hash = 5381;
  for (let i = 0; i < text.length; i++) {
    hash = ((hash << 5) + hash + text.charCodeAt(i)) | 0;
  }
  return (hash >>> 0).toString(36);
}

function loadState(key) {
  try {
    return JSON.parse(localStorage.getItem(STORE + key)) || null;
  } catch {
    return null;
  }
}

function saveState(key, state) {
  try {
    localStorage.setItem(STORE + key, JSON.stringify(state));
  } catch {
    // Storage is only a convenience, so a failure is not worth reporting.
  }
}

export function parseQuiz(source) {
  const questionLines = [];
  const choices = [];
  let answers = null;
  let explanation = null;
  for (const raw of source.split("\n")) {
    const line = raw.trimEnd();
    if (!line.trim()) continue;
    if (line.startsWith("\u2192 ")) {
      const text = line.slice(2);
      if (choices.length) choices[choices.length - 1].explanation = text;
      else explanation = text;
    } else if (line.startsWith("\u25C9 ")) {
      choices.push({ text: line.slice(2), correct: true, explanation: null });
    } else if (line.startsWith("\u25CB ")) {
      choices.push({ text: line.slice(2), correct: false, explanation: null });
    } else if (choices.length === 0 && /^\[.*\]$/.test(line.trim())) {
      answers = line.trim().slice(1, -1).split("|").map((a) => a.trim());
    } else {
      questionLines.push(line);
    }
  }
  return { question: questionLines.join("\n"), choices, answers, explanation };
}

function normal(text) {
  return text.trim().toLowerCase().replace(/\s+/g, " ");
}

function inline(text) {
  const span = document.createElement("span");
  span.innerHTML = marked.parseInline(text.replace(/<(?=[A-Za-z\/])/g, "&lt;"));
  return span;
}

/** An interactive question. Its answer and feedback are kept under `key`. */
function renderQuiz(source, key) {
  const quiz = parseQuiz(source);
  const id = `quiz-${key}`;
  const state = loadState(key) || { choice: null, text: "", verdict: null, revealed: false };

  const box = document.createElement("div");
  box.className = "quiz";

  const question = document.createElement("div");
  question.className = "quiz-question";
  question.innerHTML = marked.parse(quiz.question);
  question.querySelectorAll("pre code").forEach((code) => {
    code.innerHTML = highlightC(code.textContent);
  });
  box.appendChild(question);

  const feedback = document.createElement("div");
  feedback.className = "quiz-feedback";

  const check = document.createElement("button");
  check.textContent = "Check answer";
  const retry = document.createElement("button");
  retry.textContent = "Try again";
  const show = document.createElement("button");
  show.textContent = "Show answer";
  show.className = "link";

  const inputs = [];
  const labels = [];
  let textInput = null;

  if (quiz.choices.length) {
    const list = document.createElement("div");
    list.className = "quiz-choices";
    quiz.choices.forEach((choice, index) => {
      const label = document.createElement("label");
      label.className = "quiz-choice";
      const radio = document.createElement("input");
      radio.type = "radio";
      radio.name = id;
      radio.value = String(index);
      label.append(radio, inline(choice.text));
      list.appendChild(label);
      inputs.push(radio);
      labels.push(label);
    });
    box.appendChild(list);
  } else {
    textInput = document.createElement("input");
    textInput.type = "text";
    textInput.className = "quiz-text";
    textInput.placeholder = "Type your answer";
    box.appendChild(textInput);
  }

  const buttons = document.createElement("div");
  buttons.className = "quiz-buttons";
  buttons.append(check, retry, show);
  box.append(buttons, feedback);

  function say(kind, message, extra) {
    feedback.className = `quiz-feedback ${kind}`;
    feedback.replaceChildren();
    const line = document.createElement("div");
    line.textContent = message;
    feedback.appendChild(line);
    if (extra) {
      const note = document.createElement("div");
      note.className = "explain";
      note.appendChild(inline(extra));
      feedback.appendChild(note);
    }
  }

  function paint() {
    const locked = state.verdict === "correct" || state.revealed;
    inputs.forEach((input) => (input.disabled = locked));
    if (textInput) textInput.disabled = locked;
    check.classList.toggle("hidden", locked);
    show.classList.toggle("hidden", locked);
    retry.classList.toggle("hidden", !(state.verdict === "wrong" && !state.revealed));
  }

  function remember() {
    saveState(key, state);
  }

  function showChoiceMarks() {
    labels.forEach((label, index) => {
      label.classList.toggle("right", quiz.choices[index].correct);
      label.classList.toggle("picked-wrong", index === state.choice && !quiz.choices[index].correct);
    });
  }

  // Restore what the learner did last time.
  if (state.choice !== null && inputs[state.choice]) inputs[state.choice].checked = true;
  if (textInput) textInput.value = state.text || "";
  if (quiz.choices.length && state.choice !== null) showChoiceMarks();
  if (state.revealed) {
    const right = quiz.choices.find((c) => c.correct);
    say("correct", right ? `The answer is: ${right.text}` : `The answer is: ${(quiz.answers || []).join(" or ")}`, right ? right.explanation : quiz.explanation);
  } else if (state.verdict === "correct") {
    const picked = quiz.choices[state.choice];
    say("correct", "Correct.", picked ? picked.explanation : null);
  } else if (state.verdict === "wrong") {
    const picked = quiz.choices[state.choice];
    say("wrong", "Not quite. Try again.", picked ? picked.explanation : quiz.explanation);
  }
  paint();

  check.addEventListener("click", () => {
    if (quiz.choices.length) {
      const picked = inputs.findIndex((input) => input.checked);
      if (picked < 0) {
        say("", "Choose an answer first.");
        return;
      }
      state.choice = picked;
      showChoiceMarks();
      if (quiz.choices[picked].correct) {
        state.verdict = "correct";
        say("correct", "Correct.", quiz.choices[picked].explanation);
      } else {
        state.verdict = "wrong";
        say("wrong", "Not quite. Try again.", quiz.choices[picked].explanation);
      }
    } else {
      const typed = textInput.value;
      if (!normal(typed)) {
        say("", "Type an answer first.");
        return;
      }
      state.text = typed;
      if (quiz.answers.some((answer) => normal(answer) === normal(typed))) {
        state.verdict = "correct";
        say("correct", "Correct.");
      } else {
        state.verdict = "wrong";
        say("wrong", "Not quite. Try again.", quiz.explanation);
      }
    }
    remember();
    paint();
  });

  retry.addEventListener("click", () => {
    state.verdict = null;
    state.choice = null;
    state.text = "";
    inputs.forEach((input) => (input.checked = false));
    labels.forEach((label) => label.classList.remove("right", "picked-wrong"));
    if (textInput) textInput.value = "";
    say("", "");
    remember();
    paint();
  });

  // As in the course quizzes: once the answer has been shown, the question cannot be retried.
  show.addEventListener("click", () => {
    state.revealed = true;
    remember();
    if (quiz.choices.length) {
      const right = quiz.choices.find((c) => c.correct);
      labels.forEach((label, index) => label.classList.toggle("right", quiz.choices[index].correct));
      say("correct", `The answer is: ${right ? right.text : ""}`, right ? right.explanation : null);
    } else {
      say("correct", `The answer is: ${(quiz.answers || []).join(" or ")}`, quiz.explanation);
    }
    paint();
  });

  return box;
}

/**
 * Renders a quiz block. A block containing lines of "---" holds several parts, each a
 * question of its own, labelled (a), (b), and so on.
 */
function renderQuizBlock(source, key) {
  const parts = source.split(/^---\s*$/m);
  if (parts.length === 1) return renderQuiz(source, key);
  const group = document.createElement("div");
  group.className = "quiz-group";
  parts.forEach((part, index) => {
    const wrapper = document.createElement("div");
    wrapper.className = "quiz-part";
    const label = document.createElement("div");
    label.className = "quiz-part-label";
    label.textContent = `(${String.fromCharCode(97 + index)})`;
    wrapper.append(label, renderQuiz(part, `${key}:${index}`));
    group.appendChild(wrapper);
  });
  return group;
}

/**
 * Renders Markdown into an element: highlights C code and turns quiz blocks into
 * questions. Quiz answers are remembered for each lesson, keyed by the lesson's text.
 */
export function renderLessonInto(element, markdown) {
  const lessonKey = hashText(markdown);
  element.innerHTML = marked.parse(markdown);

  // Truth-table results: a cell holding exactly T or F is colored, so the answers are easy to scan.
  element.querySelectorAll("td").forEach((cell) => {
    const value = cell.textContent.trim();
    if (value === "T") cell.classList.add("truth-true");
    if (value === "F") cell.classList.add("truth-false");
  });
  element.querySelectorAll("pre code[class^=\"language-c\"]").forEach((code) => {
    code.innerHTML = highlightC(code.textContent);
  });
  element.querySelectorAll("pre code.language-quiz").forEach((code, index) => {
    code.closest("pre").replaceWith(renderQuizBlock(code.textContent, `${lessonKey}:${index}`));
  });

  // Diagrams: a ```dot block is drawn with Graphviz, in the browser.
  element.querySelectorAll("pre code.language-dot").forEach((code) => {
    const box = document.createElement("div");
    box.className = "diagram";
    box.textContent = "Drawing diagram...";
    code.closest("pre").replaceWith(box);
    const source = code.textContent;
    getViz()
      .then((viz) => {
        // Graphviz draws at the dpi named in the source, so its coordinates are scaled by dpi / 72.
        // Scaling the width back by 72 / dpi makes the 14-point labels match the lesson font.
        const svg = viz.renderSVGElement(source);
        const dpi = Number((source.match(/dpi\s*=\s*([\d.]+)/) || [])[1]) || 72;
        const width = svg.viewBox.baseVal.width * (72 / dpi);
        svg.removeAttribute("width");
        svg.removeAttribute("height");
        if (width) svg.style.width = `${width}px`;
        box.replaceChildren(svg);
      })
      .catch((error) => {
        box.className = "diagram error";
        box.textContent = `Could not draw this diagram: ${error}`;
      });
  });

  // A copy button for each code block in the lesson (quiz questions are left alone).
  element.querySelectorAll("pre").forEach((pre) => {
    if (pre.closest(".quiz")) return;
    const wrapper = document.createElement("div");
    wrapper.className = "code-block";
    pre.replaceWith(wrapper);
    wrapper.appendChild(pre);

    const copy = document.createElement("button");
    copy.className = "icon-button copy-code";
    copy.title = "Copy code";
    copy.innerHTML = icon("copy");
    copy.addEventListener("click", () => {
      navigator.clipboard.writeText(pre.textContent).catch((error) => console.error(error));
    });
    wrapper.appendChild(copy);
  });
}
