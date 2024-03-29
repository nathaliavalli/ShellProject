#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>//For EXIT codes and error handling
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> //check if file or not
#include <sys/types.h>
#include <sys/stat.h> //check if file or not
#include <sys/wait.h>
#include "helpers.h"

int isExec(const char *path);



void programExec (char * input){


    pid_t pid = fork(); //proper use of the fork 

    if (pid <0){
        perror("Fork did not work");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0){//child process
        
        //stdinandout(input);
        
        
        char *args[] = {input, NULL};
        if (execv(input, args) == -1) {
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }
        
        const char* env_Variable = getenv("PATH");
        char * path = parse(env_Variable,":");// proper use of supplied parser code 

        for (int i =0; i< sizeof(path);i++){
            // Construct the full path to the executable
            char *fullPath = malloc(strlen(path[i]) + strlen(input) + 2); // +2 for '/' and '\0'
            strcpy(fullPath, path[i]);
            strcat(fullPath, "/");
            strcat(fullPath, input);
            printf('%s',fullPath);

            // Check if the executable exists in the current directory
            if (isExec(fullPath)) {
                // Execute the program
                char *args[] = {fullPath, NULL};
                if (execv(fullPath, args) == -1) {
                    perror("Exec failed");
                    exit(EXIT_FAILURE);
                }
            }

            free(fullPath); // Free the dynamically allocated memory
        }

        // If the loop completes, the program was not found in any directory
        fprintf(stderr, "Program not found: %s\n", input);
        exit(EXIT_FAILURE);

    } else { // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}


int isExec(const char *path) {
    struct stat st;

    // getting information about the file
    if (lstat(path, &st) == 0) {
        // USE MACRO to Check if it is a exec
        return S_ISREG(st.st_mode);
    } else {
        // Handle error (e.g., file not found)
        perror("lstat");
        return -1; 
    }
}