#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {

        if (clearenv() == -1) {
            perror("clearenv");
            return 1;
        }
        printf("All environment variables cleared.\n");
    } else if (argc == 2) {

        char *variable_name = argv[1];
        if (unsetenv(variable_name) == -1) {
            perror("unsetenv");
            return 1;
        }
        printf("Variable '%s' removed from environment.\n", variable_name);
    } else {

        printf("Usage: %s [<variable_name>]\n", argv[0]);
        return 1;
    }


    extern char **environ;
    printf("Current environment:\n");
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }

    return 0;
}

