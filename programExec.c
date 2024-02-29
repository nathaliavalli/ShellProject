#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>//For EXIT codes and error handling
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "helpers.h"

void programExec (char * path){
    pid_t pid = fork();

    if (pid <0){
        perror("Fork did not work");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0){//child process
        
        char *args[] = {path, NULL};
        if (execv(path, args) == -1) {
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}