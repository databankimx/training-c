#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Core calculator. Bonus items are not included in this version. */

typedef enum {
    TOK_NUMBER,
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_LEFT,
    TOK_RIGHT,
    TOK_END
} Kind;

/* One token: its kind, its text, its value if it's a number, and the column where it starts (counting from 1). */
typedef struct {
    Kind kind;
    char text[32];
    double value;
    size_t column;
} Token;

/* The state of one calculation. Errors are recorded here instead of thrown: the first error sets failed, and
   every later step does nothing once failed is set. */
typedef struct {
    Token *tokens;
    size_t count;
    size_t pos;
    bool failed;
    char error[160];
} Calc;

/* Records the first error, with the column appended, such as "division by zero at column 3". */
static void fail(Calc *c, size_t column, const char *format, ...) {
    if (c->failed) {
        return;
    }
    c->failed = true;
    char message[128];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof message, format, args);
    va_end(args);
    snprintf(c->error, sizeof c->error, "%s at column %zu", message, column);
}

/* Writes how an error describes a token: its text in quotes, or "end of input". */
static void describe(const Token *token, char *out, size_t size) {
    if (token->kind == TOK_END) {
        snprintf(out, size, "end of input");
    } else {
        snprintf(out, size, "'%s'", token->text);
    }
}

/* Splits the text into tokens. Each token records its column. The last token is always END, one column past the input. */
static bool tokenize(Calc *c, const char *text) {
    size_t length = strlen(text);
    c->tokens = malloc((length + 2) * sizeof *c->tokens);
    if (c->tokens == NULL) {
        fail(c, 1, "out of memory");
        return false;
    }
    c->count = 0;

    size_t i = 0;
    while (i < length && !c->failed) {
        char ch = text[i];
        size_t column = i + 1;
        if (isspace((unsigned char)ch)) {
            i++;
            continue;
        }
        if (isdigit((unsigned char)ch) || ch == '.') {
            size_t start = i;
            int dots = 0;
            while (i < length && (isdigit((unsigned char)text[i]) || text[i] == '.')) {
                if (text[i] == '.') {
                    dots++;
                }
                i++;
            }
            size_t number_length = i - start;
            if (dots > 1 || (number_length == 1 && ch == '.') || number_length >= sizeof c->tokens[0].text) {
                char number[64];
                size_t copy = number_length < sizeof number ? number_length : sizeof number - 1;
                memcpy(number, text + start, copy);
                number[copy] = '\0';
                fail(c, column, "invalid number '%s'", number);
                break;
            }
            Token *token = &c->tokens[c->count++];
            token->kind = TOK_NUMBER;
            memcpy(token->text, text + start, number_length);
            token->text[number_length] = '\0';
            token->value = strtod(token->text, NULL);
            token->column = column;
            continue;
        }

        Kind kind;
        if (ch == '+') {
            kind = TOK_PLUS;
        } else if (ch == '-') {
            kind = TOK_MINUS;
        } else if (ch == '*') {
            kind = TOK_STAR;
        } else if (ch == '/') {
            kind = TOK_SLASH;
        } else if (ch == '(') {
            kind = TOK_LEFT;
        } else if (ch == ')') {
            kind = TOK_RIGHT;
        } else {
            fail(c, column, "unexpected character '%c'", ch);
            break;
        }
        Token *token = &c->tokens[c->count++];
        token->kind = kind;
        token->text[0] = ch;
        token->text[1] = '\0';
        token->value = 0.0;
        token->column = column;
        i++;
    }

    Token *end = &c->tokens[c->count++];
    end->kind = TOK_END;
    end->text[0] = '\0';
    end->value = 0.0;
    end->column = length + 1;
    return !c->failed;
}

static Token peek(const Calc *c) {
    return c->tokens[c->pos];
}

/* Moves past the current token and returns it. The END token is never moved past. */
static Token advance(Calc *c) {
    Token token = c->tokens[c->pos];
    if (token.kind != TOK_END) {
        c->pos++;
    }
    return token;
}

/* Recursive descent: one function per grammar rule. Each rule calls the rules below it, so precedence follows from
   the structure of the functions. */
static double parse_expr(Calc *c);

/* factor := '-' factor | number | '(' expr ')' */
static double parse_factor(Calc *c) {
    if (c->failed) {
        return 0.0;
    }
    if (peek(c).kind == TOK_MINUS) {
        advance(c);
        return -parse_factor(c);
    }
    Token token = peek(c);
    if (token.kind == TOK_NUMBER) {
        advance(c);
        return token.value;
    }
    if (token.kind == TOK_LEFT) {
        advance(c);
        double value = parse_expr(c);
        if (c->failed) {
            return 0.0;
        }
        if (peek(c).kind != TOK_RIGHT) {
            char found[64];
            describe(&c->tokens[c->pos], found, sizeof found);
            fail(c, peek(c).column, "expected ')', found %s", found);
            return 0.0;
        }
        advance(c);
        return value;
    }
    char found[64];
    describe(&token, found, sizeof found);
    fail(c, token.column, "expected a number or '(', found %s", found);
    return 0.0;
}

/* term := factor (('*' | '/') factor)* */
static double parse_term(Calc *c) {
    double value = parse_factor(c);
    while (!c->failed && (peek(c).kind == TOK_STAR || peek(c).kind == TOK_SLASH)) {
        Token op = advance(c);
        double right = parse_factor(c);
        if (c->failed) {
            return 0.0;
        }
        if (op.kind == TOK_STAR) {
            value *= right;
        } else {
            if (right == 0.0) {
                fail(c, op.column, "division by zero");
                return 0.0;
            }
            value /= right;
        }
    }
    return value;
}

/* expr := term (('+' | '-') term)* */
static double parse_expr(Calc *c) {
    double value = parse_term(c);
    while (!c->failed && (peek(c).kind == TOK_PLUS || peek(c).kind == TOK_MINUS)) {
        Token op = advance(c);
        double right = parse_term(c);
        if (c->failed) {
            return 0.0;
        }
        value = op.kind == TOK_PLUS ? value + right : value - right;
    }
    return value;
}

/* Parses the whole input, and reports anything left over. Returns the value, or sets c->failed. */
static double parse_all(Calc *c) {
    double value = parse_expr(c);
    if (!c->failed && peek(c).kind != TOK_END) {
        char found[64];
        describe(&c->tokens[c->pos], found, sizeof found);
        fail(c, peek(c).column, "expected end of input, found %s", found);
    }
    return value;
}

/* Evaluates one line of input. On success, writes the result to out with up to 15 significant digits, so whole
   numbers print without a decimal point, and small floating-point errors are hidden. On failure, writes the message
   to out, with the "error: " prefix. Returns true on success. */
static bool calculate(const char *text, char *out, size_t size) {
    Calc c;
    memset(&c, 0, sizeof c);
    if (!tokenize(&c, text)) {
        snprintf(out, size, "error: %s", c.error);
        free(c.tokens);
        return false;
    }
    double value = parse_all(&c);
    if (c.failed) {
        snprintf(out, size, "error: %s", c.error);
        free(c.tokens);
        return false;
    }
    snprintf(out, size, "%.15g", value);
    free(c.tokens);
    return true;
}

/* Each check is an input and its expected output. An error is expected as "error: " followed by its message.
   Returns the number of checks that failed. */
static int run_checks(void) {
    static const char *const cases[][2] = {
        {"2 + 3 * 4", "14"},
        {"(2 + 3) * 4", "20"},
        {"10 - 4 - 3", "3"},
        {"8 / 4 / 2", "1"},
        {"-3 + 5", "2"},
        {"2 * -3", "-6"},
        {"10 / 4", "2.5"},
        {"1.5 * 4", "6"},
        {"2 + $", "error: unexpected character '$' at column 5"},
        {"1 / 0", "error: division by zero at column 3"},
        {"(2 + 3", "error: expected ')', found end of input at column 7"},
        {"2 + 3)", "error: expected end of input, found ')' at column 6"},
        {"2 +", "error: expected a number or '(', found end of input at column 4"},
        {"1.2.3", "error: invalid number '1.2.3' at column 1"},
    };
    int failures = 0;
    size_t count = sizeof cases / sizeof cases[0];
    for (size_t i = 0; i < count; i++) {
        char actual[256];
        calculate(cases[i][0], actual, sizeof actual);
        bool passed = strcmp(actual, cases[i][1]) == 0;
        printf("%s %s -> %s\n", passed ? "PASS" : "FAIL", cases[i][0], actual);
        if (!passed) {
            failures++;
        }
    }
    printf("Failures: %d\n", failures);
    return failures;
}

/* Shows a fixed list of expressions, with each result or error. */
static void run_demo(void) {
    static const char *const expressions[] = {
        "2 + 3 * 4", "(2 + 3) * 4", "10 - 4 - 3", "8 / 4 / 2", "-3 + 5", "2 * -3", "10 / 4", "1.5 * 4",
        "2 + $", "1 / 0", "(2 + 3", "2 + 3)", "2 +", "1.2.3",
    };
    size_t count = sizeof expressions / sizeof expressions[0];
    for (size_t i = 0; i < count; i++) {
        char out[256];
        calculate(expressions[i], out, sizeof out);
        printf("%s => %s\n", expressions[i], out);
    }
}

/* Joins the words of the command line back into one line, since the shell splits what you type at each space. */
static bool join_arguments(int argc, char *argv[], char *out, size_t size) {
    out[0] = '\0';
    for (int i = 1; i < argc; i++) {
        size_t used = strlen(out);
        size_t needed = strlen(argv[i]) + (i > 1 ? 1 : 0);
        if (used + needed + 1 > size) {
            return false;
        }
        if (i > 1) {
            strcat(out, " ");
        }
        strcat(out, argv[i]);
    }
    return true;
}

static bool is_blank(const char *line) {
    for (const char *p = line; *p != '\0'; p++) {
        if (!isspace((unsigned char)*p)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    char request[512];
    if (!join_arguments(argc, argv, request, sizeof request)) {
        printf("error: the expression is too long\n");
        return 1;
    }

    if (strcmp(request, "selftest") == 0) {
        return run_checks() == 0 ? 0 : 1;
    }
    if (strcmp(request, "demo") == 0) {
        run_demo();
        return 0;
    }
    if (request[0] != '\0') {
        char out[256];
        bool ok = calculate(request, out, sizeof out);
        printf("%s\n", out);
        return ok ? 0 : 1;
    }

    /* The REPL: read a line, evaluate it, and print the result. Blank lines are skipped, and quit ends the loop. */
    printf("Calculator. Type an expression, or quit to exit.\n");
    char line[512];
    while (fgets(line, sizeof line, stdin) != NULL) {
        size_t length = strlen(line);
        while (length > 0 && (line[length - 1] == '\n' || line[length - 1] == '\r')) {
            line[--length] = '\0';
        }
        if (strcmp(line, "quit") == 0) {
            break;
        }
        if (is_blank(line)) {
            continue;
        }
        char out[256];
        calculate(line, out, sizeof out);
        printf("%s\n", out);
    }
    return 0;
}
