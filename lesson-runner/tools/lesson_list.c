/* lesson-list: prints the course's parts as JSON, so the discovery code can be checked against the C++ runner.
 *
 *   lesson-list <repository root>
 *
 * Run it on the C++ repository and the C repository, and compare the two outputs' structure. */

#include <stdio.h>
#include <stdlib.h>

#include "cJSON.h"
#include "discovery.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: lesson-list <repository root>\n");
        return 2;
    }
    cJSON *parts = lesson_list_parts(argv[1]);
    char *text = cJSON_Print(parts);
    if (!text) {
        fprintf(stderr, "could not print the parts\n");
        cJSON_Delete(parts);
        return 1;
    }
    puts(text);
    free(text);
    cJSON_Delete(parts);
    return 0;
}
