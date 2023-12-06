#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define DEFAULT_FILE_NAME "output.txt"

int main(int argc, char *argv[]) {
    char *file_name = getenv("FILE_NAME");

    if (file_name == NULL) {
        file_name = DEFAULT_FILE_NAME;
    }

    int num_programs = 1;

    int opt;
    while ((opt = getopt(argc, argv, "f:n:")) != -1) {
        switch (opt) {
            case 'f':
                file_name = optarg;
                break;
            case 'n':
                num_programs = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-f file_name] [-n num_programs]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= num_programs; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char program_name[50];
            sprintf(program_name, "Child %d", i);
            execl("./child_program", "child_program", program_name, file_name, NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_programs; i++) {
        wait(NULL);
    }

    return 0;
}
