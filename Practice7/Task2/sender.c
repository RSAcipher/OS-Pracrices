#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <wait.h>

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
        kill(getpid() + 1, SIGUSR2);
    }
}

int main() {

    signal(SIGUSR1, signal_handler);
    printf("Enter the size of data: ");
    int buffer_size;
    scanf("%d", &buffer_size);
    int shmid = shmget(KEY, (buffer_size + 1) * sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    shared_memory = (int *)shmat(shmid, NULL, 0);
    if (shared_memory == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    shared_memory[0] = buffer_size;

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {

        printf("Sender Process: Shared memory created and Receiver process forked.\n");
        printf("Enter %d integers:\n", buffer_size);
        for (int i = 1; i <= buffer_size; i++) {
            scanf("%d", &shared_memory[i]);
        }

        kill(pid, SIGUSR2);
        wait(NULL);
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);

        printf("Sender Process: Finished.\n");
    } else {
        execl("./receiver", "receiver", (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
