#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <variable_name> <variable_value>\n", argv[0]);
        return 1;
    }

    char *variable_name = argv[1];
    char *variable_value = argv[2];

    if (setenv(variable_name, variable_value, 1) == -1) {
        perror("setenv");
        return 1;
    }

    char *env_value = getenv(variable_name);
    if (env_value != NULL) {
        printf("Variable: %s\nValue: %s\n", variable_name, env_value);
    } else {
        printf("Variable %s not found.\n", variable_name);
    }

    return 0;
}
