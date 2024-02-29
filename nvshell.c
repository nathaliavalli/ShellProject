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
        else if (strncmp(input, "cd", 2) == 0) {
            changeDir(input);
            continue;
        }
        //taking the new line char from user input
        int idx = strcspn(input, "\n");
        input[idx] = '\0';

        //each built in in use
        if (strcmp(input,"pwd")==0){
            getpwd();
        }
        else if (strcmp(input,"help")==0){
            printHelp();
        }
        else if (strcmp(input,"exit")==0){
            xit();
        }

    }

}
