// bridge.js: the page's connection to the C host.
//
// The page calls the host through the two functions below. Their names match the calls the page was written with,
// invoke and listen. The transport is WebView2's
// message channel: the page posts a JSON string to the host, and the host posts JSON back.
//
// Messages from the host are one of two kinds:
//   { "kind": "reply", "id": 7, "result": ... }   or   { "kind": "reply", "id": 7, "error": "text" }
//   { "kind": "event", "event": "run-output", "payload": ... }

const pending = new Map();
const listeners = new Map();
let nextId = 1;

window.chrome.webview.addEventListener("message", (event) => {
  const message = typeof event.data === "string" ? JSON.parse(event.data) : event.data;

  if (message.kind === "reply") {
    const waiter = pending.get(message.id);
    if (!waiter) return;
    pending.delete(message.id);
    // Errors arrive as plain text, and are rejected as text.
    if (message.error !== undefined) {
      waiter.reject(message.error);
    } else {
      waiter.resolve(message.result);
    }
    return;
  }

  if (message.kind === "event") {
    for (const handler of listeners.get(message.event) ?? []) {
      handler({ payload: message.payload });
    }
  }
});

/** Calls a command in the host, and resolves with its result. */
export function invoke(command, args = {}) {
  return new Promise((resolve, reject) => {
    const id = nextId++;
    pending.set(id, { resolve, reject });
    window.chrome.webview.postMessage(JSON.stringify({ kind: "command", id, command, args }));
  });
}

/** Calls handler(event) each time the host emits the named event. The event's data is in event.payload. */
export function listen(event, handler) {
  if (!listeners.has(event)) listeners.set(event, []);
  listeners.get(event).push(handler);
  return () => {
    const list = listeners.get(event) ?? [];
    listeners.set(event, list.filter((existing) => existing !== handler));
  };
}
