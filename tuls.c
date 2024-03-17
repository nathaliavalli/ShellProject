#include <dirent.h> //file system
#include <sys/stat.h> //check if file or not
#include <stdio.h>
#include <errno.h>//For EXIT codes and error handling
#include <stdlib.h>
#include <string.h> 
#include <limits.h>//use PATH_MAX for memory allocation
#include  "helpers.h"


char *printNoArgs (char * basepath);
char *printDirRecur (char * path, int t);
int isDirectory(const char *path); 
int isHiddenFile(const char *filename);
void printTabs(int numTabs); 


char * mainTuls (int argc, char *argv[]){
    char *path;
    
    if (argc > 1){
        path = argv[1];
        printDirRecur(path,0);
    }
    else{ //if no arguments path is current directory
        path = ".";
        printf ("%s",printNoArgs(path));
    }
    
    
}

char * printNoArgs (char * basepath ){ //function printing with no argument

    DIR *dir = opendir(basepath);
    struct dirent *namelist;
    int n = 0;
    char * str = malloc(1);
    str[0]='\0';

    if (dir == NULL){
        perror ("directory not found");
        exit(EXIT_FAILURE);
    }
    while ((namelist = readdir(dir) )!= NULL){
        if ( isHiddenFile(namelist ->d_name)){ //not printing files starting with "." 
            continue;   
        }
        else {
            int curLen = strlen((namelist->d_name)) ;
            n += curLen + 2 ; 
            str = realloc(str, n);
            strcat(str, (namelist->d_name)) ;
            strcat(str, "\n") ;
            
        }
    }
    closedir(dir);
    return str;
}    

  


char * printDirRecur (char *path, int t){ //printing directories recursevely
      
    struct dirent **dirname;
    int num;
    num = scandir(path,&dirname,NULL,alphasort);
    char * str = malloc(1);
    str[0]='\0';
    int n=0;


    if (num<0){
        perror("Scandir");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<num; i++){
        
        struct dirent *namelist = dirname[i]; //create a new struct to work with each directory 
        char *newpath = malloc(PATH_MAX);//allocation to a new path for directories found with scandir

         // Check if memory allocation was successful
        if (newpath == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        snprintf(newpath, PATH_MAX, "%s/%s", path, namelist->d_name);//store a string in a buffer to use as new path ----> the current path + / + directory name (namelist -> d_name)

        if (!isDirectory(newpath)&& !isHiddenFile(namelist->d_name)){
            printTabs(t);
            int curLen = strlen((namelist->d_name)) ;
            n += curLen + 2 ; 
            str = realloc(str, n);
            strcat(str, (namelist->d_name)) ;
            strcat(str, "\n") ;
            return str;
            
        }
        else if(isDirectory(newpath) && strcmp(namelist->d_name, ".") != 0 && strcmp(namelist->d_name, "..") != 0 && !isHiddenFile(namelist->d_name)){
            printTabs(t);
            int curLen = strlen((namelist->d_name)) ;
            n += curLen + 2 ; 
            str = realloc(str, n);
            strcat(str, (namelist->d_name)) ;
            strcat(str, "\n") ;
            return str;
            
            
        }    
    }
    free(dirname);
    return str;
}

int isDirectory(const char *path) {
    struct stat st;

    // getting information about the file
    if (lstat(path, &st) == 0) {
        // USE MACRO to Check if it is a directory
        return S_ISDIR(st.st_mode);
    } else {
        // Handle error (e.g., file not found)
        perror("lstat");
        return -1; 
    }
}

int isHiddenFile(const char *filename) {
    // Check if the filename starts with a dot
    return (filename[0] == '.');
}

void printTabs(int numTabs) {
    for (int i = 0; i < numTabs; ++i) {
        printf("\t");
    }
}
