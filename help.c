#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>//For EXIT codes and error handling
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "helpers.h"


void printHelp(){
    printf("Current options for comands.\n");
    printf("1.pwd - Print current working directory \n2.cd 'pathname or ..' - Change the directory, on current working directory, to the directory of choice('pathname') or '..' for parent directory \n3.exit - exit shell \n");
}