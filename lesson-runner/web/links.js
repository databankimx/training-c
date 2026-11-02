import { invoke } from "./bridge.js";

/**
 * Sends clicks on web and mail links to the default browser, so the lesson window
 * never navigates away. Other links (such as in-page anchors) are left alone.
 */
export function installExternalLinks(root) {
  root.addEventListener("click", (event) => {
    const link = event.target.closest("a[href]");
    if (!link) return;
    event.preventDefault();
    const href = link.getAttribute("href");
    if (href.startsWith("#goto/")) {
      // An in-lesson link to a child chapter section or step. The main window does the navigation.
      invoke("navigate_to", { name: href.slice(6) }).catch((error) => console.error(error));
      return;
    }
    if (/^(https?:\/\/|mailto:)/i.test(href)) {
      invoke("open_external", { url: href }).catch((error) => console.error(error));
    }
  });
}
