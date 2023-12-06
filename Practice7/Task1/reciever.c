#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define KEY 1234

int *shared_memory;

void signal_handler(int signum) {
    if (signum == SIGUSR2) {
        int sum = 0;
        for (int i = 1; i <= shared_memory[0]; i++) {
            sum += shared_memory[i];
        }

        printf("Receiver Process: Calculated sum: %d\n", sum);

        // Send signal to wake up Sender process
        kill(getppid(), SIGUSR1);

        // Sleep until the Sender process completes
        pause();

        // Detach shared memory
        shmdt(shared_memory);

        printf("Receiver Process: Finished.\n");

        // Exit the process
        exit(EXIT_SUCCESS);
    }
}

int main() {
    // Set up signal handler
    signal(SIGUSR2, signal_handler);

    // Create shared memory
    int shmid = shmget(KEY, 0, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory
    shared_memory = (int *)shmat(shmid, NULL, 0);
    if (shared_memory == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Sleep until signal received
    pause();

    return 0;
}
