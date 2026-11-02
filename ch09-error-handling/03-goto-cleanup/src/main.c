#include <stdio.h>

int copy_file(const char *from, const char *to) {
    int result = -1;

    FILE *in = fopen(from, "r");
    if (in == NULL) {
        goto done;
    }

    FILE *out = fopen(to, "w");
    if (out == NULL) {
        goto close_in;
    }

    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (fputc(ch, out) == EOF) {
            goto close_out;
        }
    }
    result = 0;

close_out:
    fclose(out);
close_in:
    fclose(in);
done:
    return result;
}

int main(void) {
    if (copy_file("data/source.txt", "data/copy.txt") == 0) {
        printf("Copy 1: ok\n");
    } else {
        printf("Copy 1: failed\n");
    }

    if (copy_file("data/missing.txt", "data/other.txt") == 0) {
        printf("Copy 2: ok\n");
    } else {
        printf("Copy 2: failed\n");
    }

    // Try: copy data/source.txt into a name in a folder that doesn't exist, and predict the output before you press Run.
    return 0;
}
