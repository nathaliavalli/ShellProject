
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>//For EXIT codes and error handling
#include "helpers.h"

void xit (){
   exit(EXIT_SUCCESS);
}