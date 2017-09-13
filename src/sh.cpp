#include "sh.h"
#include "db.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <exception>
#include <sys/wait.h>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp" // to use <<

#define ARG_BUFSIZE 64
#define ARG_DELIM " \t\r\n\a"

// function dectarations for builtin shell commands
int ltt_help(char **args);
int ltt_exit(char **args);
int ltt_da(char **args);
int ltt_dl(char **args);
int ltt_mv(char **args);
int ltt_al(char **args);
int ltt_at(char **args);
int ltt_ra(char **args);
int ltt_rl(char **args);
int ltt_rt(char **args);
int ltt_cl(char **args);

// list of builtin commands, followed by their corresponsing functions
char *builtin_str[] = {
    "h",
    "help",
    "exit",
    "da",
    "dl",
    "mv",
    "al",
    "at",
    "ra",
    "rl",
    "rt",
    "cl"
};

int (*builtin_func[]) (char **) = {
    &ltt_help,
    &ltt_help,
    &ltt_exit,
    &ltt_da,
    &ltt_dl,
    &ltt_mv,
    &ltt_al,
    &ltt_at,
    &ltt_ra,
    &ltt_rl,
    &ltt_rt,
    &ltt_cl
};

int SH::ltt_num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

SH::SH(int id) { }


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

    printf("\n		___	___	___\n");
    printf("	       /  /    /  /    /  /\n");
    printf("	      /  /  __/  /____/  /__\n");
    printf("	     /  / /__   ___/__   ___/\n");
    printf("	    /  /    /  /     /  /\n");
    printf("	   /  /	   /  /     /  /\n");
    printf("	  /  /___ /  /_____/  /\n");
    printf("	 /_______/__/_____/__/\n");
    printf("\n\nltt - LittleTerminalTasks\n");
    
    printf("\nUSAGE: ltt [options] [task/list name/ID]\n\n");
    printf("\th, help prints out help\n");

    printf("displaying options\n");
    printf("\tda\tdisplay all lists\n");
    printf("\tdl ^\tdisplay list\n");

    printf("moving options\n");
    printf("\tmv * ^  move task to list\n");

    printf("adding options\n");
    printf("\tal ^\tadd list\n");
    printf("\tat * ^  add task to list\n");

    printf("removing options\n");
    printf("\tra\tremove all lists\n");
    printf("\trl ^\tremove list\n");
    printf("\trt *\tremove task\n");
    printf("\tcl ^\tclean list\n\n");

    return 1;

}

int ltt_exit(char **args) { return 0; }

int ltt_da(char **args) {
    DB database(1);
    database.display_all();
    return 1;
}

int ltt_dl(char **args) {
    DB database(1);
    database.display_list(args[1]);
    return 1;
}

int ltt_mv(char **args) {
    DB database(1);
    if (args[3] != NULL) {
        char arg1[100];
        char arg2[100];

        strcpy(arg1, args[1]);
        strcat(arg1, " ");
        strcat(arg1, args[2]);

        strcpy(arg2, args[3]);
        strcat(arg2, " ");
        strcat(arg2, args[4]);
    
        database.move_task(arg1, arg2);
    } else {
        database.move_task(args[1], args[2]);
    }
    return 1;
}

int ltt_al(char **args) {
    DB database(1);

    if (args[2] != NULL) {
        char arg1[100];

        strcpy(arg1, args[1]);
        strcat(arg1, " ");
        strcat(arg1, args[2]);
        database.add_list(arg1);
    } else {
        database.add_list(args[1]);
    }

    return 1;
}

int ltt_at(char **args) {
    DB database(1);
    if (args[3] != NULL) {
        char arg1[100];
        char arg2[100];

        strcpy(arg1, args[1]);
        strcat(arg1, " ");
        strcat(arg1, args[2]);

        strcpy(arg2, args[3]);
        strcat(arg2, " ");
        strcat(arg2, args[4]);
    
        database.move_task(arg1, arg2);
    } else {
        database.move_task(args[1], args[2]);
    }
    return 1;
}

int ltt_ra(char **args) {
    DB database(1);
    database.remove_all();
    return 1;
}

int ltt_rl(char **args) {
    DB database(1);
    if (args[2] != NULL) {
        char arg1[100];

        strcpy(arg1, args[1]);
        strcat(arg1, " ");
        strcat(arg1, args[2]);
        database.remove_list(arg1);
    } else {
        database.remove_list(args[1]);
    }
    return 1;
}

int ltt_rt(char **args) {
    DB database(1);
    if (args[2] != NULL) {
        char arg1[100];

        strcpy(arg1, args[1]);
        strcat(arg1, " ");
        strcat(arg1, args[2]);
        database.remove_task(arg1);
    } else {
        database.remove_task(args[1]);
    }
    return 1;
}

int ltt_cl(char **args) {
    DB database(1);
    if (args[2] != NULL) {
        char arg1[100];

        strcpy(arg1, args[1]);
        strcat(arg1, " ");
        strcat(arg1, args[2]);
        database.clear_list(arg1);
    } else {
        database.clear_list(args[1]);
    }
    return 1;
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

