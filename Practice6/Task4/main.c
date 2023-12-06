#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_CATALAN 10
#define MAX_PRIMES 10

typedef struct {
    int *result;
    int max_iterations;
} ThreadParams;

void *catalan_thread_function(void *arg) {
    ThreadParams *params = (ThreadParams *)arg;

    int *result = (int *)malloc(params->max_iterations * sizeof(int));

    if (result == NULL) {
        perror("malloc");
        pthread_exit(NULL);
    }

    // Calculation of Catalan numbers
    result[0] = 1;
    for (int i = 1; i < params->max_iterations; i++) {
        result[i] = result[i - 1] * (2 * (2 * i - 1)) / (i + 1);
    }

    params->result = result;
    pthread_exit(NULL);
}

void *primes_thread_function(void *arg) {
    ThreadParams *params = (ThreadParams *)arg;

    int *result = (int *)malloc(params->max_iterations * sizeof(int));

    if (result == NULL) {
        perror("malloc");
        pthread_exit(NULL);
    }

    // Calculation of prime numbers
    int count = 0;
    int num = 2;
    while (count < params->max_iterations) {
        int is_prime = 1;
        for (int i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            result[count++] = num;
        }
        num++;
    }

    params->result = result;
    pthread_exit(NULL);
}

int main() {
    pthread_t catalan_thread, primes_thread;
    ThreadParams catalan_params = {.result = NULL, .max_iterations = MAX_CATALAN};
    ThreadParams primes_params = {.result = NULL, .max_iterations = MAX_PRIMES};

    int thread_create_result1 = pthread_create(&catalan_thread, NULL, catalan_thread_function, (void *)&catalan_params);
    int thread_create_result2 = pthread_create(&primes_thread, NULL, primes_thread_function, (void *)&primes_params);

    if (thread_create_result1 || thread_create_result2) {
        fprintf(stderr, "Error creating threads: %d, %d\n", thread_create_result1, thread_create_result2);
        exit(EXIT_FAILURE);
    }

    pthread_join(catalan_thread, NULL);
    pthread_join(primes_thread, NULL);

    printf("Catalan Numbers: ");
    for (int i = 0; i < MAX_CATALAN; i++) {
        printf("%d ", catalan_params.result[i]);
    }
    printf("\n");

    printf("Prime Numbers: ");
    for (int i = 0; i < MAX_PRIMES; i++) {
        printf("%d ", primes_params.result[i]);
    }
    printf("\n");

    free(catalan_params.result);
    free(primes_params.result);

    return 0;
}
