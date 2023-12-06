#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX_HANDLERS 10

void exit_handler(int signo) {
    static int counter = 0;
    counter++;

    printf("Exit Handler %d: Process is terminating...\n", counter);
    sleep(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_handlers>\n", argv[0]);
        return 1;
    }

    int num_handlers = atoi(argv[1]);

    if (num_handlers <= 0 || num_handlers > MAX_HANDLERS) {
        fprintf(stderr, "Error: Invalid number of handlers. Should be between 1 and %d.\n", MAX_HANDLERS);
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = exit_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    for (int i = 0; i < num_handlers; i++) {
        if (sigaction(SIGINT, &sa, NULL) == -1) {
            perror("sigaction");
            return 1;
        }
    }

    printf("Press Ctrl+C to terminate the process.\n");

    while (1) {
        sleep(2);
        printf("Program is running...\n");
    }

    return 0;
}
