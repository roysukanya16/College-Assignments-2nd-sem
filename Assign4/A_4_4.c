#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>

#include <string.h>
int main() {
    while (1) {
        printf("1. ls\n");
        printf("2. pwd\n");
        printf("3. uname\n");
        printf("4. exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                pid_t pid = fork();
                if (pid < 0) {
                    printf("Failed to fork child process.\n");
                    return 1;
                }
                if (pid == 0) {
                    // Child process
                    char* args[] = {"ls", NULL};
                    execv("/bin/ls", args);
                    exit(0);
                } else {
                    // Parent process
                    wait(NULL);
                }
                break;
            }
            case 2: {
                pid_t pid = fork();
                if (pid < 0) {
                    printf("Failed to fork child process.\n");
                    return 1;
                }
                if (pid == 0) {
                    // Child process
                    char* args[] = {"pwd", NULL};
                    execv("/bin/pwd", args);
                    exit(0);
                } 
                else {
                    // Parent process
                    wait(NULL);
                }
                break;
            }
            case 3: {
                pid_t pid = fork();
                if (pid < 0) {
                    printf("Failed to fork child process.\n");
                    return 1;
                }
                if (pid == 0) {
                    // Child process
                    char* args[] = {"uname", NULL};
                    execv("/bin/uname", args);
                    exit(0);
                } 
                else {
                    // Parent process
                    wait(NULL);
                }
                break;
            }
            case 4:
                // Terminate the program
                printf("Exit\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                continue;
        }
    }
}

