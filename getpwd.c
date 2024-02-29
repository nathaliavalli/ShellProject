#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>//For EXIT codes and error handling
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "helpers.h"


void getpwd (){
    char cwd [1024];
    if (getcwd (cwd, sizeof(cwd))!=NULL){
        printf("Current working directory is:%s\n", cwd);
    }
    else{
        perror("getcwd() error");
    }
}