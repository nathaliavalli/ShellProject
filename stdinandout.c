#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>//For EXIT codes and error handling
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h> //check if file or not
#include <sys/wait.h>
#include <fcntl.h>
#include "helpers.h"


void stdinandout (char * input){
    char *commands[50];
    int i = 0;

    char *token = strtok(input, " ");
    while (token != NULL && i < 50 - 1) {
        commands[i++] = token;
        token = strtok(NULL, " ");
    }
    commands[i] = NULL; // Null-terminate the commands array

    for (int j =0; commands[j] != NULL;j++){
         int original_stdin = dup(STDIN_FILENO);  // Duplicate the file descriptor for stdin
        int original_stdout = dup(STDOUT_FILENO); // Duplicate the file descriptor for stdout

        if (strcmp(commands[0], "ls") == 0) {
            char* lsCopy = mainTuls(NULL, input);
            // Handle ls command or store response
        } 
        // Handle other commands like wc, etc.

        if (strcmp(commands[j], '>') == 0) {
            // Open the output file for writing
            int file_descriptor = open(commands[i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
            if (file_descriptor == -1) {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
            // Redirect stdout to the output file
            dup2(file_descriptor, STDOUT_FILENO);
            close(file_descriptor);
            i++; // Skip the output file name
        }

        if (strcmp(commands[j ], '<') == 0) {
            // Open the input file for reading
            int file_descriptor = open(commands[i + 1], O_RDONLY);
            if (file_descriptor == -1) {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
            // Redirect stdin to the input file
            dup2(file_descriptor, STDIN_FILENO);
            close(file_descriptor);
            i++; // Skip the input file name
        }

        // Execute the command (ls) or any other command with the modified redirections
        execvp(commands[0], commands);

        // Restore original stdin and stdout
        dup2(original_stdin, STDIN_FILENO);
        dup2(original_stdout, STDOUT_FILENO);
    }
}