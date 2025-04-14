#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

#define MAX_INPUT_LENGTH 1024

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf(">> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strcmp(input, "Exit") == 0) break;
        parse_and_execute(input);
    }

    return 0;
}
