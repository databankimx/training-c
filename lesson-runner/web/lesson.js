import { icon } from "./icons.js";
import { installExternalLinks } from "./links.js";
import { renderLessonInto } from "./lesson-render.js";
import { blockPageZoom, enableZoom } from "./zoom.js";

import { invoke, listen } from "./bridge.js";

const titleEl = document.querySelector("#lesson-title");
const lessonEl = document.querySelector("#lesson");

// The pop-out remembers where each lesson was left, as the main window does. A lesson shown
// for the first time starts at the top.
const scrollByTitle = new Map();
let currentTitle = null;

function restoreScroll(offset) {
  window.scrollTo(0, offset);
  requestAnimationFrame(() => window.scrollTo(0, offset));
  setTimeout(() => window.scrollTo(0, offset), 150);
}

function show(lesson) {
  const isNewLesson = lesson.title !== currentTitle;
  if (currentTitle !== null) scrollByTitle.set(currentTitle, window.scrollY);
  const offset = isNewLesson ? (scrollByTitle.get(lesson.title) ?? 0) : window.scrollY;
  currentTitle = lesson.title;
  titleEl.textContent = lesson.title || "Lesson";
  document.title = `Lesson: ${lesson.title}`;
  if (!lesson.text || !lesson.text.trim()) {
    lessonEl.textContent = "No lesson text yet for this step.";
    return;
  }
  lessonEl.innerHTML = "";
  renderLessonInto(lessonEl, lesson.text);
  restoreScroll(offset);
}

installExternalLinks(lessonEl);
blockPageZoom();
enableZoom(lessonEl, "lesson", 14);

const dockButton = document.querySelector("#dock");
dockButton.innerHTML = icon("dock");
dockButton.addEventListener("click", () => {
  invoke("dock_lesson").catch((error) => {
    lessonEl.textContent = `${error}`;
  });
});

function applyTheme(light) {
  document.body.classList.toggle("light", Boolean(light));
}

listen("theme-changed", (event) => applyTheme(event.payload));
invoke("get_theme").then(applyTheme);

listen("lesson-updated", (event) => show(event.payload));

invoke("get_lesson")
  .then(show)
  .catch((error) => {
    lessonEl.textContent = `${error}`;
  });
