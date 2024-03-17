#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>//For EXIT codes and error handling
#include "helpers.h"


void wait_command() {
    int status;
    pid_t pid;

    // Wait for any child process to terminate
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child process %d terminated with exit status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }

    if (pid == -1 && errno != ECHILD) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
}
