#include "sh.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARG_BUFSIZE 64
#define ARG_DELIM " \t\r\n\a"

// function dectarations for builtin shell commands
int ltt_help(char **args);

// list of builtin commands, followed by their corresponsing functions
char *builtin_str[] = {
    "h",
};

int (*builtin_func[]) (char **) = {
    &ltt_help,
};

int SH::ltt_num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

SH::SH(int id) { printf("print id: %i", id); }


char* SH::ltt_readline() {

    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

char** SH::ltt_splitline(char *line) {
    
    int bufsize = ARG_BUFSIZE, position = 0;
    char **arguments = (char**)malloc(bufsize *sizeof(char*)); // (char**) - need to cast the return of the function in c++
    char *argument;
    
    if (!arguments) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    argument = strtok(line, ARG_DELIM);
    while (argument != NULL) {
        arguments[position] = argument;
        position++;

        if (position >= bufsize) {
            bufsize += ARG_BUFSIZE;
            arguments = (char**)realloc(arguments, bufsize * sizeof(char*)); // (char**) - need to cast the return of the function in c++
        
            if (!arguments) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        argument = strtok(NULL, ARG_DELIM);
    }
    
    arguments[position] = NULL;
    return arguments;
}

int SH::ltt_launch(char **args) {

    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("ltt");
        }
    } else if (pid < 0) {
        // Error forking
        perror("ltt");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int SH::ltt_execute(char **args) {
    
    int i;
    if (args[0] == NULL) {
        exit(EXIT_FAILURE);
    }

    for (i=0; i<ltt_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return ltt_launch(args);
}

        

int ltt_help(char **args) {
    
    printf("\nUSAGE: ltt [options] [task/list name/ID]\n\n");
    printf("\th\tprints out help\n");

    printf("displaying options\n");
    printf("\tda\tdisplay all lists\n");
    printf("\tdl *\tdisplay list(s)\n");
    printf("\tdt *\tdisplay task(s)\n");

    printf("moving options\n");
    printf("\tmvt * ^  move task to list\n");

    printf("adding options\n");
    printf("\trl *\tadd list(s)\n");
    printf("\trt *\tadd task(s)\n");

    printf("removing options\n");
    printf("\tra\tremove all lists\n");
    printf("\trl *\tremove list(s)\n");
    printf("\trt *\tremove task(s)\n\n");

    return 0;

}



int SH::ltt_loop() {

    // Read, Parse (separate the command string into a program and arguments), and Execute commands

    char *line;
    char **args;
    int status;

    do {
        printf("(ltt) ");
        line = ltt_readline();
        args = ltt_splitline(line);
        status = ltt_execute(args);
        
        free(line);
        free(args);
    } while (status);

    return 0;
}

