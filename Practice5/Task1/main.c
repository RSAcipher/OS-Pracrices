#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <commands>\n", argv[0]);
        return 1;
    }
    char *commands = argv[1];
    char *token = strtok(commands, ";");
    while (token != NULL) {
        int exit_code = system(token);
        printf("Command: %s\nExit Code: %d\n", token, exit_code);
        token = strtok(NULL, ";");
    }

    return 0;
}

