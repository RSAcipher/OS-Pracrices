#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 127

void print_prompt(char *username) {
    printf("[%s]$", username);
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    char *username = getenv("USER");

    if (username == NULL) {
        fprintf(stderr, "Error: Unable to get username.\n");
        return 1;
    }

    printf("Welcome, %s, to the Simple Shell!\n", username);
    printf("Type 'stop' to exit.\n");

    int buffer_size = (argc == 3 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "--buffer") == 0))
                      ? atoi(argv[2])
                      : BUFFER_SIZE;

    char buffer[buffer_size];

    while (1) {
        print_prompt(username);

        if (strcmp(buffer, "stop") == 0) {
            break;
        }

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error reading input.\n");
            break;
        }

        int result = system(buffer);

        if (result == -1) {
            fprintf(stderr, "Error executing command.\n");
            break;
        }

        sleep(3);
        system("clear");
    }

    printf("Wait 3 seconds...\n");
    sleep(3);
    system("clear");

    return 0;
}

