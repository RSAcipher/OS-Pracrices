#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define RANDOM_THRESHOLD 5

void *child_thread_function(void *arg) {
    int num_iterations = *((int *)arg);

    for (int i = 1; i <= num_iterations; i++) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3);

        if (rand() % RANDOM_THRESHOLD == 0) {
            printf("Child Thread: Random number reached. Exiting early.\n");
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}

void *random_numbers_thread_function(void *arg) {
    int num_iterations = *((int *)arg);

    for (int i = 1; i <= num_iterations; i++) {
        printf("Random Numbers Thread. Iteration: %d\n", i);
        sleep(rand() % 3);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t child_thread, random_numbers_thread;
    int num_iterations = 10;

    int thread_create_result1 = pthread_create(&child_thread, NULL, child_thread_function, (void *)&num_iterations);
    int thread_create_result2 = pthread_create(&random_numbers_thread, NULL, random_numbers_thread_function, (void *)&num_iterations);

    if (thread_create_result1 || thread_create_result2) {
        fprintf(stderr, "Error creating threads: %d, %d\n", thread_create_result1, thread_create_result2);
        exit(EXIT_FAILURE);
    }

    pthread_join(child_thread, NULL);
    pthread_join(random_numbers_thread, NULL);

    printf("Main Thread: All threads have finished.\n");

    return 0;
}
