#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <environment_variable>\n", argv[0]);
        return 1;
    }

    char *variable_name = argv[1];
    char *variable_value = getenv(variable_name);

    if (variable_value == NULL) {
        printf("Environment variable '%s' not found.\n", variable_name);
    } else if (variable_value[0] == '\0') {
        printf("Environment variable '%s' is set but has an empty value.\n", variable_name);
    } else {
        printf("Value of environment variable '%s': %s\n", variable_name, variable_value);
    }

    return 0;
}
