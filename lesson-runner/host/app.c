/* app.c: the lesson runner's windows. The main window hosts the front end (from lesson-runner\web). The pop-out lesson
 * window hosts the lesson page from the same folder. The page's commands come in as web messages, and the router's
 * replies and events go back out.
 *
 * Both pages are served from the virtual address https://runner.local/, mapped to the web folder. Modules and relative
 * imports only load from a real web address, so NavigateToString is not used. This follows the C++ runner's app.cpp.
 *
 * The COM callbacks are written by hand, as the WebView2 spike proved they can be. Each one answers QueryInterface for
 * IUnknown and for its own handler interface only, and it frees itself when its reference count reaches zero.
 */

#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN
#define CINTERFACE
#define COBJMACROS

#include <windows.h>
#include <objbase.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "WebView2.h"

#include "cJSON.h"
#include "discovery.h"
#include "router.h"
#include "runner.h"

#define MAIN_WINDOW_CLASS L"LessonRunner"
#define LESSON_WINDOW_CLASS L"LessonRunnerLesson"
#define VIRTUAL_HOST L"runner.local"
#define START_PAGE L"https://runner.local/index.html"
#define LESSON_PAGE L"https://runner.local/lesson.html"
#define PATH_BYTES 1024

typedef struct Host Host;

/* One web page in one window, with its controller and web view. */
typedef struct {
    HWND window;
    ICoreWebView2Controller *controller;
    ICoreWebView2 *webview;
    EventRegistrationToken token;
    int is_main;
    Host *host;
} Page;

struct Host {
    HINSTANCE instance;
    wchar_t web_root[PATH_BYTES];
    char repo_root[PATH_BYTES];
    Page main;
    Page *lesson;               /* the pop-out lesson page, or NULL when it is closed */
    HWND lesson_window;
    ICoreWebView2Environment *environment;
    LessonRunner *runner;
    LessonRouter *router;
};

static Host *g_host = NULL;

/* ---- Strings --------------------------------------------------------------------------------- */

/* UTF-8 to UTF-16. Invalid bytes become U+FFFD rather than failing, as the C++ runner's replacement does. Owned by the
 * caller. */
static wchar_t *utf8_to_wide(const char *text) {
    int size = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
    if (size <= 0) return NULL;
    wchar_t *wide = (wchar_t *)malloc((size_t)size * sizeof(wchar_t));
    if (wide) MultiByteToWideChar(CP_UTF8, 0, text, -1, wide, size);
    return wide;
}

/* UTF-16 to UTF-8. Owned by the caller. */
static char *wide_to_utf8(const wchar_t *wide) {
    int size = WideCharToMultiByte(CP_UTF8, 0, wide, -1, NULL, 0, NULL, NULL);
    if (size <= 0) return NULL;
    char *text = (char *)malloc((size_t)size);
    if (text) WideCharToMultiByte(CP_UTF8, 0, wide, -1, text, size, NULL, NULL);
    return text;
}

/* A message that says what went wrong, with the error code, shown in a dialog. */
static void fail(const wchar_t *message, HRESULT code) {
    wchar_t text[512];
    swprintf(text, 512, L"%ls\n\nError code: 0x%08lX", message, (unsigned long)code);
    MessageBoxW(NULL, text, L"Lesson Runner", MB_ICONERROR);
}

/* ---- Sending to pages ----------------------------------------------------------------------------- */

static void page_post_text(Page *page, const char *utf8) {
    if (!page->webview) return;
    wchar_t *wide = utf8_to_wide(utf8);
    if (!wide) return;
    page->webview->lpVtbl->PostWebMessageAsString(page->webview, wide);
    free(wide);
}

/* Sends a JSON message to a page. The message is printed, then posted as text. The caller still owns it. */
static void page_post_json(Page *page, const cJSON *message) {
    char *text = cJSON_PrintUnformatted(message);
    if (!text) return;
    page_post_text(page, text);
    free(text);
}

/* Sends an event to every open page, since each one may show the lesson or the run's output. Takes ownership of the
 * payload. */
static void post_event(Host *host, const char *name, cJSON *payload) {
    cJSON *message = cJSON_CreateObject();
    cJSON_AddStringToObject(message, "kind", "event");
    cJSON_AddStringToObject(message, "event", name);
    cJSON_AddItemToObject(message, "payload", payload ? payload : cJSON_CreateNull());
    page_post_json(&host->main, message);
    if (host->lesson) page_post_json(host->lesson, message);
    cJSON_Delete(message);
}

/* Sends the reply to a command back to the page that sent it. Takes ownership of result. */
static void post_reply(Page *page, const cJSON *id, cJSON *result, const char *error) {
    cJSON *message = cJSON_CreateObject();
    cJSON_AddStringToObject(message, "kind", "reply");
    cJSON_AddItemToObject(message, "id", cJSON_Duplicate(id, 1));
    if (error) {
        cJSON_AddStringToObject(message, "error", error);
        cJSON_Delete(result);
    } else {
        cJSON_AddItemToObject(message, "result", result);
    }
    page_post_json(page, message);
    cJSON_Delete(message);
}

/* ---- Page controls --------------------------------------------------------------------------------- */

static void page_resize(Page *page) {
    if (!page->controller) return;
    RECT bounds;
    GetClientRect(page->window, &bounds);
    page->controller->lpVtbl->put_Bounds(page->controller, bounds);
}

/* Closes the WebView2 control. Done before the window goes, so the page is shut down cleanly. */
static void page_close(Page *page) {
    if (page->controller) {
        page->controller->lpVtbl->Close(page->controller);
        page->controller->lpVtbl->Release(page->controller);
        page->controller = NULL;
    }
    if (page->webview) {
        page->webview->lpVtbl->Release(page->webview);
        page->webview = NULL;
    }
}

/* ---- COM callbacks --------------------------------------------------------------------------------- */

typedef enum { CALLBACK_ENVIRONMENT, CALLBACK_CONTROLLER, CALLBACK_MESSAGE } CallbackKind;

typedef HRESULT(STDMETHODCALLTYPE *QueryFn)(void *self, REFIID riid, void **out);
typedef ULONG(STDMETHODCALLTYPE *RefFn)(void *self);
typedef HRESULT(STDMETHODCALLTYPE *CompletedFn)(void *self, HRESULT result, void *value);
typedef HRESULT(STDMETHODCALLTYPE *MessageFn)(void *self, void *sender, void *args);

typedef struct {
    QueryFn QueryInterface;
    RefFn AddRef;
    RefFn Release;
    CompletedFn Invoke;
} CompletedVtbl;

typedef struct {
    QueryFn QueryInterface;
    RefFn AddRef;
    RefFn Release;
    MessageFn Invoke;
} MessageVtbl;

/* A callback object. The vtable pointer comes first, so WebView2 can call through it. */
typedef struct {
    const void *lpVtbl;
    LONG refs;
    CallbackKind kind;
    void *target; /* the Host for the environment, the Page for the controller and messages */
} Callback;

static ULONG STDMETHODCALLTYPE callback_add_ref(void *self) {
    return (ULONG)InterlockedIncrement(&((Callback *)self)->refs);
}

static ULONG STDMETHODCALLTYPE callback_release(void *self) {
    Callback *callback = (Callback *)self;
    ULONG count = (ULONG)InterlockedDecrement(&callback->refs);
    if (count == 0) free(callback);
    return count;
}

/* Answers only IUnknown and the interface this callback implements. */
static HRESULT STDMETHODCALLTYPE callback_query_interface(void *self, REFIID riid, void **out) {
    Callback *callback = (Callback *)self;
    const IID *own = callback->kind == CALLBACK_ENVIRONMENT
                         ? &IID_ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler
                         : callback->kind == CALLBACK_CONTROLLER
                               ? &IID_ICoreWebView2CreateCoreWebView2ControllerCompletedHandler
                               : &IID_ICoreWebView2WebMessageReceivedEventHandler;
    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, own)) {
        *out = self;
        callback_add_ref(self);
        return S_OK;
    }
    *out = NULL;
    return E_NOINTERFACE;
}

static HRESULT STDMETHODCALLTYPE environment_invoke(void *self, HRESULT result, void *value);
static HRESULT STDMETHODCALLTYPE controller_invoke(void *self, HRESULT result, void *value);
static HRESULT STDMETHODCALLTYPE message_invoke(void *self, void *sender, void *args);

static const CompletedVtbl kEnvironmentVtbl = {callback_query_interface, callback_add_ref, callback_release,
                                               environment_invoke};
static const CompletedVtbl kControllerVtbl = {callback_query_interface, callback_add_ref, callback_release,
                                              controller_invoke};
static const MessageVtbl kMessageVtbl = {callback_query_interface, callback_add_ref, callback_release,
                                         message_invoke};

/* Creates a callback with one reference, which the caller hands to WebView2. */
static Callback *callback_new(CallbackKind kind, void *target) {
    Callback *callback = (Callback *)calloc(1, sizeof *callback);
    if (!callback) return NULL;
    callback->lpVtbl = kind == CALLBACK_ENVIRONMENT    ? (const void *)&kEnvironmentVtbl
                       : kind == CALLBACK_CONTROLLER  ? (const void *)&kControllerVtbl
                                                      : (const void *)&kMessageVtbl;
    callback->refs = 1;
    callback->kind = kind;
    callback->target = target;
    return callback;
}

/* ---- Startup: environment, controller, and the page ----------------------------------------------- */

static HRESULT host_on_environment(Host *host, HRESULT result, ICoreWebView2Environment *environment) {
    if (FAILED(result)) {
        fail(L"The WebView2 environment couldn't be created.", result);
        return result;
    }
    host->environment = environment;
    environment->lpVtbl->AddRef(environment);
    Callback *controller_done = callback_new(CALLBACK_CONTROLLER, &host->main);
    if (!controller_done) return E_OUTOFMEMORY;
    return environment->lpVtbl->CreateCoreWebView2Controller(
        environment, host->main.window, (ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *)controller_done);
}

/* A page's controller is ready. Its web view gets the virtual host, its message handler, and its first page. */
static HRESULT host_on_controller(Page *page, HRESULT result, ICoreWebView2Controller *controller) {
    Host *host = page->host;
    if (FAILED(result)) {
        fail(L"The WebView2 controller couldn't be created.", result);
        return result;
    }
    page->controller = controller;
    controller->lpVtbl->AddRef(controller);

    HRESULT hr = controller->lpVtbl->get_CoreWebView2(controller, &page->webview);
    if (FAILED(hr)) {
        fail(L"The WebView2 control couldn't be reached from the controller.", hr);
        return hr;
    }

    /* The virtual host maps https://runner.local/ to the web folder, so the page's modules load as normal files. */
    ICoreWebView2_3 *webview3 = NULL;
    hr = page->webview->lpVtbl->QueryInterface(page->webview, &IID_ICoreWebView2_3, (void **)&webview3);
    if (FAILED(hr)) {
        fail(L"This WebView2 Runtime is too old for the lesson runner. Install the current Evergreen Runtime.", hr);
        return hr;
    }
    hr = webview3->lpVtbl->SetVirtualHostNameToFolderMapping(webview3, VIRTUAL_HOST, host->web_root,
                                                             COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND_ALLOW);
    webview3->lpVtbl->Release(webview3);
    if (FAILED(hr)) {
        fail(L"The lesson runner's web folder couldn't be mapped.", hr);
        return hr;
    }

    page_resize(page);

    Callback *message_done = callback_new(CALLBACK_MESSAGE, page);
    if (!message_done) return E_OUTOFMEMORY;
    hr = page->webview->lpVtbl->add_WebMessageReceived(
        page->webview, (ICoreWebView2WebMessageReceivedEventHandler *)message_done, &page->token);
    if (FAILED(hr)) {
        fail(L"Couldn't listen for messages from the page.", hr);
        return hr;
    }
    return page->webview->lpVtbl->Navigate(page->webview, page->is_main ? START_PAGE : LESSON_PAGE);
}

/* A message from a page: { kind: "command", id, command, args }. The reply goes back to that page. */
static HRESULT host_on_message(Page *page, ICoreWebView2WebMessageReceivedEventArgs *args) {
    Host *host = page->host;
    LPWSTR raw = NULL;
    HRESULT hr = args->lpVtbl->TryGetWebMessageAsString(args, &raw);
    if (FAILED(hr) || !raw) return hr;
    char *text = wide_to_utf8(raw);
    CoTaskMemFree(raw);
    if (!text) return S_OK;

    cJSON *message = cJSON_Parse(text);
    free(text);
    if (!message) return S_OK; /* not JSON, so it isn't a command from the bridge */

    const cJSON *kind = cJSON_GetObjectItemCaseSensitive(message, "kind");
    const cJSON *command = cJSON_GetObjectItemCaseSensitive(message, "command");
    const cJSON *id = cJSON_GetObjectItemCaseSensitive(message, "id");
    const cJSON *arguments = cJSON_GetObjectItemCaseSensitive(message, "args");
    if (!cJSON_IsString(kind) || strcmp(kind->valuestring, "command") != 0) {
        cJSON_Delete(message);
        return S_OK;
    }

    cJSON *empty = NULL;
    if (!arguments) {
        empty = cJSON_CreateObject();
        arguments = empty;
    }
    cJSON *id_copy = id ? cJSON_Duplicate(id, 1) : cJSON_CreateNumber(0);
    char error[512] = "";
    cJSON *result = lesson_router_handle(host->router, cJSON_IsString(command) ? command->valuestring : "", arguments,
                                         error, sizeof error);
    if (result) {
        post_reply(page, id_copy, result, NULL);
    } else {
        post_reply(page, id_copy, NULL, error[0] ? error : "The command failed.");
    }
    cJSON_Delete(id_copy);
    cJSON_Delete(empty);
    cJSON_Delete(message);
    return S_OK;
}

static HRESULT STDMETHODCALLTYPE environment_invoke(void *self, HRESULT result, void *value) {
    Callback *callback = (Callback *)self;
    return host_on_environment((Host *)callback->target, result, (ICoreWebView2Environment *)value);
}

static HRESULT STDMETHODCALLTYPE controller_invoke(void *self, HRESULT result, void *value) {
    Callback *callback = (Callback *)self;
    return host_on_controller((Page *)callback->target, result, (ICoreWebView2Controller *)value);
}

static HRESULT STDMETHODCALLTYPE message_invoke(void *self, void *sender, void *args) {
    Callback *callback = (Callback *)self;
    (void)sender;
    return host_on_message((Page *)callback->target, (ICoreWebView2WebMessageReceivedEventArgs *)args);
}

/* Loads WebView2 and asks for the environment. The rest happens in the callbacks. */
static int host_start(Host *host) {
    HMODULE loader = LoadLibraryW(L"WebView2Loader.dll");
    if (!loader) {
        fail(L"WebView2Loader.dll wasn't found next to the program.", (HRESULT)GetLastError());
        return 0;
    }
    typedef union {
        FARPROC generic;
        HRESULT(WINAPI *typed)(PCWSTR, PCWSTR, void *, void *);
    } ProcAddress;
    ProcAddress found;
    found.generic = GetProcAddress(loader, "CreateCoreWebView2EnvironmentWithOptions");
    if (!found.typed) {
        fail(L"The loader DLL doesn't export CreateCoreWebView2EnvironmentWithOptions.", (HRESULT)GetLastError());
        return 0;
    }
    Callback *environment_done = callback_new(CALLBACK_ENVIRONMENT, host);
    if (!environment_done) return 0;
    HRESULT hr = found.typed(NULL, NULL, NULL, environment_done);
    if (FAILED(hr)) {
        fail(L"WebView2 couldn't start. Is the WebView2 Runtime installed?", hr);
        return 0;
    }
    return 1;
}

/* ---- The pop-out lesson window ------------------------------------------------------------------- */

static void host_close_lesson_window(Host *host) {
    if (host->lesson_window) DestroyWindow(host->lesson_window);
}

static void host_open_lesson_window(Host *host) {
    if (host->lesson_window) {
        ShowWindow(host->lesson_window, SW_RESTORE);
        SetForegroundWindow(host->lesson_window);
        return;
    }
    host->lesson_window = CreateWindowExW(0, LESSON_WINDOW_CLASS, L"Lesson", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                          CW_USEDEFAULT, 900, 720, NULL, NULL, host->instance, host);
    if (!host->lesson_window) {
        fail(L"The lesson window couldn't be created.", (HRESULT)GetLastError());
        return;
    }
    host->lesson = (Page *)calloc(1, sizeof(Page));
    if (!host->lesson) return;
    host->lesson->window = host->lesson_window;
    host->lesson->host = host;
    host->lesson->is_main = 0;
    Callback *controller_done = callback_new(CALLBACK_CONTROLLER, host->lesson);
    if (controller_done && host->environment) {
        host->environment->lpVtbl->CreateCoreWebView2Controller(
            host->environment, host->lesson_window,
            (ICoreWebView2CreateCoreWebView2ControllerCompletedHandler *)controller_done);
    }
    ShowWindow(host->lesson_window, SW_SHOW);
    post_event(host, "lesson-popped", cJSON_CreateNull());
}

/* The lesson window has gone, however it closed. Its page is released, and the main window is told. */
static void host_on_lesson_window_destroyed(Host *host) {
    if (host->lesson) {
        page_close(host->lesson);
        free(host->lesson);
        host->lesson = NULL;
    }
    host->lesson_window = NULL;
    post_event(host, "lesson-docked", cJSON_CreateNull());
}

/* The router asks for the window to open or dock. */
static void window_action(void *context, const char *action) {
    Host *host = (Host *)context;
    if (strcmp(action, "open") == 0) {
        host_open_lesson_window(host);
    } else {
        host_close_lesson_window(host);
    }
}

/* Events from the router and the runner go to the page through post_event. */
static void router_event(void *context, const char *name, cJSON *payload) {
    post_event((Host *)context, name, payload);
}

/* Sends the output and results the runner has queued. Called on the window's thread. */
static void host_flush_runner_events(Host *host) {
    LessonEvent *events = lesson_runner_take_events(host->runner);
    for (LessonEvent *event = events; event; event = event->next) {
        post_event(host, event->name, event->payload ? event->payload : cJSON_CreateNull());
        event->payload = NULL; /* post_event owns it now */
    }
    lesson_free_events(events);
}

static void host_create(Host *host, HINSTANCE instance, HWND window, const char *repo_root, const wchar_t *web_root) {
    memset(host, 0, sizeof *host);
    host->instance = instance;
    snprintf(host->repo_root, sizeof host->repo_root, "%s", repo_root);
    wcsncpy(host->web_root, web_root, PATH_BYTES - 1);
    host->main.window = window;
    host->main.is_main = 1;
    host->main.host = host;
    host->runner = lesson_runner_create(window, repo_root);
    host->router = lesson_router_create(repo_root, host->runner, router_event, host);
    lesson_router_set_window_action(host->router, window_action, host);
}

static void host_destroy(Host *host) {
    if (host->lesson) {
        page_close(host->lesson);
        free(host->lesson);
        host->lesson = NULL;
    }
    page_close(&host->main);
    if (host->environment) {
        host->environment->lpVtbl->Release(host->environment);
        host->environment = NULL;
    }
    lesson_router_destroy(host->router);
    lesson_runner_destroy(host->runner);
}

/* ---- Windows --------------------------------------------------------------------------------- */

static LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    if (message == WM_NCCREATE) {
        const CREATESTRUCTW *create = (const CREATESTRUCTW *)lparam;
        SetWindowLongPtrW(window, GWLP_USERDATA, (LONG_PTR)create->lpCreateParams);
    }
    Host *host = (Host *)GetWindowLongPtrW(window, GWLP_USERDATA);
    if (!host) host = g_host;

    switch (message) {
    case WM_SIZE:
        if (host) {
            if (window == host->main.window) {
                page_resize(&host->main);
            } else if (host->lesson && window == host->lesson->window) {
                page_resize(host->lesson);
            }
        }
        return 0;
    case LESSON_RUNNER_EVENTS_MESSAGE:
        if (g_host) host_flush_runner_events(g_host);
        return 0;
    case WM_DESTROY:
        if (host && window == host->lesson_window) {
            host_on_lesson_window_destroyed(host);
            return 0;
        }
        /* Closing the main window closes the lesson window too, so the program can exit. */
        if (g_host && g_host->lesson_window) DestroyWindow(g_host->lesson_window);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(window, message, wparam, lparam);
}

/* ---- Entry point ----------------------------------------------------------------------------- */

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE previous, PWSTR command_line, int show) {
    (void)previous;
    (void)command_line;

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr)) {
        fail(L"COM couldn't start.", hr);
        return 1;
    }

    /* The repository root is found from the program's folder, so the runner works wherever the repo is. */
    char module[PATH_BYTES];
    GetModuleFileNameA(NULL, module, sizeof module);
    char *slash = strrchr(module, '\\');
    if (slash) *slash = '\0';
    char repo_root[PATH_BYTES];
    lesson_find_repo_root(module, repo_root, sizeof repo_root);

    char web_narrow[PATH_BYTES + 64];
    snprintf(web_narrow, sizeof web_narrow, "%s\\lesson-runner\\web", repo_root);
    char index_path[PATH_BYTES + 96];
    snprintf(index_path, sizeof index_path, "%s\\index.html", web_narrow);
    if (GetFileAttributesA(index_path) == INVALID_FILE_ATTRIBUTES) {
        fail(L"The lesson runner's web folder wasn't found. Check the repository layout.", 0);
        CoUninitialize();
        return 1;
    }
    wchar_t *web_root = utf8_to_wide(web_narrow);

    WNDCLASSW main_class;
    memset(&main_class, 0, sizeof main_class);
    main_class.lpfnWndProc = window_proc;
    main_class.hInstance = instance;
    main_class.lpszClassName = MAIN_WINDOW_CLASS;
    main_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
    main_class.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(1));
    RegisterClassW(&main_class);

    WNDCLASSW lesson_class;
    memset(&lesson_class, 0, sizeof lesson_class);
    lesson_class.lpfnWndProc = window_proc;
    lesson_class.hInstance = instance;
    lesson_class.lpszClassName = LESSON_WINDOW_CLASS;
    lesson_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
    lesson_class.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(1));
    RegisterClassW(&lesson_class);

    HWND window = CreateWindowExW(0, MAIN_WINDOW_CLASS, L"Lesson Runner", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                                  CW_USEDEFAULT, 1200, 800, NULL, NULL, instance, NULL);
    if (!window) {
        fail(L"The window couldn't be created.", (HRESULT)GetLastError());
        free(web_root);
        CoUninitialize();
        return 1;
    }
    ShowWindow(window, show);
    UpdateWindow(window);

    int exit_code = 0;
    {
        /* Scoped so the host releases its WebView2 objects before COM shuts down. */
        Host *host = (Host *)calloc(1, sizeof *host);
        host_create(host, instance, window, repo_root, web_root);
        g_host = host;
        if (host_start(host)) {
            MSG message;
            while (GetMessageW(&message, NULL, 0, 0) > 0) {
                TranslateMessage(&message);
                DispatchMessageW(&message);
            }
            exit_code = (int)message.wParam;
        } else {
            exit_code = 1;
        }
        g_host = NULL;
        host_destroy(host);
        free(host);
    }
    free(web_root);
    CoUninitialize();
    return exit_code;
}
