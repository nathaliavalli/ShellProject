#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>//For EXIT codes and error handling
#include "helpers.h"

void builtIn (char * input){
    if (strncmp(input, "cd", 2) == 0) {
        changeDir(input);
    }
        //each built in in use
    else if (strcmp(input,"pwd")==0){
        getpwd();
    }
    else if (strcmp(input,"help")==0){
        printHelp();
    }
    else if (strcmp(input,"exit")==0){
        xit();
    }
    else if (strcmp(input, "wait")==0){
        wait_command();
    }
    
}