#ifndef helpers_h
#define helpers_h

char** parse(char* line, const char delim[]);
void builtIn (char * input);
void getpwd();
void printHelp();
void xit ();
void changeDir(char * input);
void programExec (char * path);
void stdinandout (char * input);
char* mainTuls (int argc, char *argv[]);
void wait_command();
void execute_pipeline(char *commands[]);



#endif /* helpers_h */