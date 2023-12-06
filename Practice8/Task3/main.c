#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signo) {
    printf("Alarm: Time to wake up!\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <interval_seconds> <message>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int interval = atoi(argv[1]);
    char *message = argv[2];

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {


        signal(SIGALRM, alarm_handler);

        alarm(interval);

        pause();
    } else {

        printf("Main process has finished. Child process will handle the alarm.\n");

        exit(EXIT_SUCCESS);
    }

    return 0;
}