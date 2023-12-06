#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <program_name> <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *program_name = argv[1];
    char *file_name = argv[2];

    FILE *file = fopen(file_name, "a");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Program: %s\n", program_name);

    for (int i = 0; i < 10; i++) {
        fprintf(file, "%f\n", (double)rand() / RAND_MAX);
    }

    fclose(file);

    return 0;
}
