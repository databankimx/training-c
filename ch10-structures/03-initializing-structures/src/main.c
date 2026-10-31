#include <stdbool.h>
#include <stdio.h>

typedef struct {
    char name[16];
    int volume;
    bool muted;
} Settings;

void show(Settings s) {
    printf("%s %d %s\n", s.name, s.volume, s.muted ? "yes" : "no");
}

Settings default_settings(void) {
    Settings s = {"default", 5, false};
    return s;
}

int main(void) {
    Settings a = default_settings();
    show(a);

    Settings b = {"Scott", 9, true};
    show(b);

    Settings c = b;
    c.volume = 1;
    show(c);

    // Try: add Settings d = {"Ada"}; and show(d), and predict the volume before you press Run.
    return 0;
}
