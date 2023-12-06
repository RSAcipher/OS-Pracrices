#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void print_environment() {
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void print_help() {
    printf("Usage:\n");
    printf("environ              Display information about the current environment.\n");
    printf("environ -h, --help   Display help information.\n");
    printf("environ -i, --info   <variable> Display the value of the specified variable or a message if it is not present.\n");
    printf("environ -s, --set    <variable=value> Set the specified environment variable to a new value.\n");
    printf("environ -a, --assign <variable> -v, --value <value> Assign a new value to the specified variable.\n");
    printf("environ -d, --del    <variable> Delete the specified variable from the environment.\n");
    printf("environ -c, --clear  Clear the entire environment.\n");
}

void print_variable_info(const char *variable_name) {
    char *variable_value = getenv(variable_name);
    if (variable_value != NULL) {
        printf("Variable: %s\nValue: %s\n", variable_name, variable_value);
    } else {
        printf("Variable '%s' not found.\n", variable_name);
    }
}

void set_variable_value(const char *variable_name, const char *value) {
    if (setenv(variable_name, value, 1) == -1) {
        perror("setenv");
        exit(1);
    }
    printf("Variable '%s' set to value '%s'.\n", variable_name, value);
}

void assign_variable_value(const char *variable_name, const char *value) {
    char *existing_value = getenv(variable_name);
    if (existing_value != NULL) {
        printf("Old value of variable '%s': %s\n", variable_name, existing_value);
    }

    if (setenv(variable_name, value, 1) == -1) {
        perror("setenv");
        exit(1);
    }

    printf("New value of variable '%s': %s\n", variable_name, value);
}

void delete_variable(const char *variable_name) {
    if (unsetenv(variable_name) == -1) {
        perror("unsetenv");
        exit(1);
    }
    printf("Variable '%s' deleted from environment.\n", variable_name);
}

void clear_environment() {
    clearenv();
    printf("Environment cleared.\n");
}
