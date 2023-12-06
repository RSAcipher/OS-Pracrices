#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *child_thread_function(void *arg) {
    int *iteration = (int *)arg;

    for (int i = 1; i <= 10; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t child_thread;
    int iteration = 1;

    printf("Main Thread. Iteration: %d\n", iteration);
    sleep(rand() % 3);

    int thread_create_result = pthread_create(&child_thread, NULL, child_thread_function, (void *)&iteration);

    if (thread_create_result) {
        fprintf(stderr, "Error creating thread: %d\n", thread_create_result);
        exit(EXIT_FAILURE);
    }

    pthread_join(child_thread, NULL);

    return 0;
}
