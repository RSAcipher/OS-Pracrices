#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname");
        return 1;
    }
    struct utsname system_info;
    if (uname(&system_info) == -1) {
        perror("uname");
        return 1;
    }
    printf("Computer Information:\n");
    printf("Hostname: %s\n", hostname);
    printf("System: %s\n", system_info.sysname);
    printf("Node (hostname): %s\n", system_info.nodename);
    printf("Release: %s\n", system_info.release);
    printf("Version: %s\n", system_info.version);
    printf("Machine: %s\n", system_info.machine);

    return 0;
}

