
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>//For EXIT codes and error handling
#include "helpers.h"

void changeDir(char * input){
    char **array = parse(input , " ");
    if (array == NULL){
        perror("Error parsing");
        exit (EXIT_FAILURE);
    }
    char *dir = NULL;
    dir = array[1];
    
    dir[strcspn(dir, "\n")] = '\0';

    if (chdir(dir)!=0){
        perror("cd failed");
    }

    
    free(array);
    
}