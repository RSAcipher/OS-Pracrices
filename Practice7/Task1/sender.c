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
    if (signum == SIGUSR1) {
        int sum = 0;
        for (int i = 0; i < shared_memory[0]; i++) {
            sum += shared_memory[i + 1];
        }

        shared_memory[0] = sum;
        printf("Sender Process: Received sum from Receiver: %d\n", sum);

        // Send signal to wake up Receiver process
        kill(getpid() + 1, SIGUSR2);
    }
}

int main() {
    // Set up signal handler
    signal(SIGUSR1, signal_handler);

    // Get buffer size from the user
    printf("Enter the size of data: ");
    int buffer_size;
    scanf("%d", &buffer_size);

    // Create shared memory
    int shmid = shmget(KEY, (buffer_size + 1) * sizeof(int), IPC_CREAT | 0666);
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

    // Store buffer size in shared memory
    shared_memory[0] = buffer_size;

    // Fork to create the Receiver process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent (Sender) Process
        printf("Sender Process: Shared memory created and Receiver process forked.\n");

        // Wait for the user to enter data
        printf("Enter %d integers:\n", buffer_size);
        for (int i = 1; i <= buffer_size; i++) {
            scanf("%d", &shared_memory[i]);
        }

        // Send signal to wake up Receiver process
        kill(pid, SIGUSR2);

        // Wait for Receiver process to complete
        wait(NULL);

        // Detach and remove shared memory
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);

        printf("Sender Process: Finished.\n");
    } else {
        // Child (Receiver) Process
        execl("./receiver", "receiver", (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
