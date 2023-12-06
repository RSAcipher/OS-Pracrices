#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    char *name = ((char **)arg)[0];
    char *str = ((char **)arg)[1];
    int num = *((int *)arg + 2);

    for (int i = 1; i <= num; i++) {
        printf("%s. %s %d\n", name, str, i);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];
    char *names[4] = {"Thread1", "Thread2", "Thread3", "Thread4"};
    char *str = "String";
    int num = 5;

    for (int i = 0; i < 4; i++) {
        void *args[3] = {names[i], str, &num};
        int thread_create_result = pthread_create(&threads[i], NULL, thread_function, args);

        if (thread_create_result) {
            fprintf(stderr, "Error creating thread %d: %d\n", i + 1, thread_create_result);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
