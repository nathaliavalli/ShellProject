//Nathalia Valli 02/11/24
//Project 1 - SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>//For EXIT codes and error handling
#include "helpers.h"

int isBuiltIn (char * ipt);

int main (){
    char input [50];

    while (1){
        printf("shell>");
        fflush(stdout);

        //requesting user input
        fgets(input,sizeof(input),stdin);
        if (input == NULL){
            break;
        }
         //taking the new line char from user input
        int idx = strcspn(input, "\n");
        input[idx] = '\0';

        if (isBuiltIn){
            builtIn(input);
        }
       else if (!builtIn){
        programExec(input);
        }

        
    }
    execute_pipeline(input);
}



int isBuiltIn (char * ipt){
    if (strncmp(ipt, "cd", 2) == 0 || strcmp(ipt, "pwd") == 0 || strcmp(ipt, "help") == 0 || strcmp(ipt, "exit") == 0||strcmp(ipt, "wait")==0){
        return 0;
    }
    return 1;
}