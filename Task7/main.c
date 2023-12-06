#include <stdio.h>
#include <string.h>
#include "environ_functions.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_environment();
    } else if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_help();
    } else if (argc == 3 && (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0)) {
        print_variable_info(argv[2]);
    } else if (argc == 4 && (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--set") == 0)) {
        set_variable_value(argv[2], argv[3]);
    } else if (argc == 4 && (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--assign") == 0) &&
               (strcmp(argv[3], "-v") == 0 || strcmp(argv[3], "--value") == 0)) {
        assign_variable_value(argv[2], argv[4]);
    } else if (argc == 3 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--del") == 0)) {
        delete_variable(argv[2]);
    } else if (argc == 2 && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--clear") == 0)) {
        clear_environment();
    } else {

        fprintf(stderr, "Error: Invalid arguments. Use -h or --help for usage information.\n");
        return 1;
    }

    return 0;
}
