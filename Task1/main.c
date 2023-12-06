#include <stdio.h>
#include <stdlib.h>

int main() {
    extern char **environ;

    printf("Complete list of environment variables:\n");

    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }

    return 0;
}
