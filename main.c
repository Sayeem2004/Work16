#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int RANDOM = 0;
int child_process() {
    // Printing Initial Message
    printf("Child: Pid Is %d\n", getpid());

    // Sleeping Time
    if (!RANDOM) {
        srand(time(NULL));
        RANDOM++;
    }
    int time = (rand() % 4) + 2;
    sleep(time);

    // Ending Function
    printf("Child: Process With PID %d Is Complete\n", getpid());
    return time;
}

int main() {
    // Printing Initial Message
    printf("Parent: Forking Started\n");

    // First Fork
    int f1 = fork();

    if (f1) { // For Parent
        // Error Checking
        if (f1 == -1) {
            printf("Parent: Forking Error: %s\n", strerror(errno));
        }

        // Second Fork
        int f2 = fork();

        if (f2) { // For Parent
            // Error Checking
            if (f2 == -1) {
                printf("Parent: Forking Error: %s\n", strerror(errno));
            }

            // Waiting For One Child To Finish Its Process
            int status;
            int err = wait(&status);

            // Error Checking
            if (err == -1) {
                printf("Parent: Waiting Error: %s\n", strerror(errno));
            }

            // Printing And Ending Parent Process
            printf("Parent: Child Process %d Slept For %d Seconds\n", err, WEXITSTATUS(status));
            printf("Parent: Process Complete\n");
            return 0;

        } else { // For Child
            int time = child_process();
            return time;
        }
    } else { // For Child
        int time = child_process();
        return time;
    }

    // Ending Program
    return 0;
}
