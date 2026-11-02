// A small tokenizer for the Source and Lesson panes. It is not a parser: it recognizes comments, strings, numbers,
// keywords, and identifiers well enough to color C code the way Visual Studio does.

const C_KEYWORDS = new Set([
  "alignas", "alignof", "auto", "bool", "constexpr", "enum", "extern", "false", "inline", "nullptr",
  "register", "restrict", "sizeof", "static", "static_assert", "struct", "thread_local", "true", "typedef",
  "typeof", "typeof_unqual", "union", "volatile", "_Atomic", "_Bool", "_Complex", "_Generic", "_Noreturn",
  "_Static_assert", "_Thread_local",
]);

const C_CONTROL = new Set([
  "break", "case", "continue", "default", "do", "else", "for", "goto", "if", "return", "switch", "while",
]);

const C_TYPES = new Set([
  "char", "const", "double", "float", "int", "long", "short", "signed", "unsigned", "void", "size_t",
  "ptrdiff_t", "intptr_t", "uintptr_t", "wchar_t", "FILE", "time_t", "va_list", "int8_t", "int16_t", "int32_t",
  "int64_t", "uint8_t", "uint16_t", "uint32_t", "uint64_t",
]);

// Order matters: the first alternative that matches at a position wins.
const C_TOKEN = new RegExp(
  [
    String.raw`\/\*[\s\S]*?\*\/`,                       // block comment
    String.raw`\/\/[^\n]*`,                             // line comment
    String.raw`"(?:\\[\s\S]|[^"\\\n])*"`,               // string
    String.raw`'(?:\\[\s\S]|[^'\\\n])+'`,               // character literal
    String.raw`#[^\n]*`,                                // preprocessor line, such as #include
    String.raw`\b0[xX][0-9a-fA-F']+\b`,                 // hexadecimal number
    String.raw`\b\d[\d']*(?:\.\d[\d']*)?(?:[eE][+-]?\d+)?[fFuUlL]*\b`, // number
    String.raw`[A-Za-z_][A-Za-z0-9_]*`,                 // identifier
    String.raw`\s+`,                                    // whitespace
    String.raw`[\s\S]`,                                 // anything else
  ].join("|"),
  "g",
);

function escapeHtml(text) {
  return text
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;");
}

function classifyWord(word, next) {
  if (C_KEYWORDS.has(word)) return "keyword";
  if (C_CONTROL.has(word)) return "control";
  if (C_TYPES.has(word)) return "type";
  if (next === "(") return "function";
  if (/^[A-Z][A-Z0-9_]+$/.test(word)) return "constant";
  if (/^[A-Z]/.test(word)) return "type";
  return "variable";
}

function classifyC(text, source, end) {
  if (text.startsWith("/*") || text.startsWith("//")) return "comment";
  if (text.startsWith('"') || text.startsWith("'")) return "string";
  if (text.startsWith("#")) return "attribute";
  if (/^\d/.test(text) || /^0[xX]/.test(text)) return "number";
  if (/^[A-Za-z_]/.test(text)) {
    const next = (source.slice(end).match(/^\s*(.)/) || [])[1];
    return classifyWord(text, next);
  }
  return "";
}

/** Returns C source as HTML with `tok-*` spans. */
export function highlightC(source) {
  const parts = [];
  C_TOKEN.lastIndex = 0;
  let match;
  while ((match = C_TOKEN.exec(source)) !== null) {
    const text = match[0];
    const type = classifyC(text, source, C_TOKEN.lastIndex);
    parts.push(type ? `<span class="tok-${type}">${escapeHtml(text)}</span>` : escapeHtml(text));
  }
  return parts.join("");
}
