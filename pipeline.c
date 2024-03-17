#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>//For EXIT codes and error handling
#include "helpers.h"


void execute_pipeline(char *commands[]) {
    int pipefd[2];
    pid_t pid;
    int status;

    int i = 0;
    while (commands[i + 1] != NULL) {
        // Create a pipe
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        // Fork a child process
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) { // Child process
            // Close read end of the pipe for child
            close(pipefd[0]);

            // Redirect stdout to the write end of the pipe
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);

            // Execute the command
            execlp(commands[i], commands[i], NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else { // Parent process
            // Close write end of the pipe for parent
            close(pipefd[1]);

            // Redirect stdin to the read end of the pipe
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            // Move to the next command
            i++;
        }
    }
    // Execute the last command in the pipeline
    execlp(commands[i], commands[i], NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
}

