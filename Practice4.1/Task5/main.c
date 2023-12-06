#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    uid_t uid = getuid();
    struct passwd *user_info_uid = getpwuid(uid);

    if (user_info_uid == NULL) {
        perror("getpwuid");
        return 1;
    }

    printf("User Information for UID %d:\n", uid);
    printf("Username: %s\n", user_info_uid->pw_name);
    printf("User ID: %d\n", user_info_uid->pw_uid);
    printf("Group ID: %d\n", user_info_uid->pw_gid);
    printf("Full Name: %s\n", user_info_uid->pw_gecos);
    printf("Home Directory: %s\n", user_info_uid->pw_dir);

    const char *root_username = "root";
    struct passwd *user_info_root = getpwnam(root_username);

    if (user_info_root == NULL) {
        perror("getpwnam");
        return 1;
    }

    printf("\nUser Information for Username '%s':\n", root_username);
    printf("Username: %s\n", user_info_root->pw_name);
    printf("User ID: %d\n", user_info_root->pw_uid);
    printf("Group ID: %d\n", user_info_root->pw_gid);
    printf("Full Name: %s\n", user_info_root->pw_gecos);
    printf("Home Directory: %s\n", user_info_root->pw_dir);

    return 0;
}
