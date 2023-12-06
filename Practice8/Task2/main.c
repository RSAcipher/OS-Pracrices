#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigaction_handler(int signo) {
    if (signo == SIGINT) {
        printf("Caught SIGINT signal.\n");
    } else if (signo == SIGTERM) {
        printf("Caught SIGTERM signal.\n");
    } else if (signo == SIGUSR1) {
        printf("Caught SIGUSR1 signal. Exiting...\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    struct sigaction sa;

    // Configure sigaction for SIGINT
    sa.sa_handler = sigaction_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

    // Configure sigaction for SIGTERM
    sigaction(SIGTERM, &sa, NULL);

    // Configure sigaction for SIGUSR1
    sigaction(SIGUSR1, &sa, NULL);

    // Restore default behavior for SIGPROF
    signal(SIGPROF, SIG_DFL);

    // Ignore SIGHUP
    signal(SIGHUP, SIG_IGN);

    // Infinite loop with pause
    while (1) {
        pause();
    }

    return 0;
}
