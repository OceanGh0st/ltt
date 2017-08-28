// ltt (LittleTerminalTasks) - Little program to organize tasks

#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc==1) {
        printf("You are in interactive mode!\n");
    } else {
        if(strcmp(argv[1],"-h") || strcmp(argv[1],"--help")) {
            printf("Run ltt without arguments to enter interactive mode\n");
            printf("Use the same commands only without '-' or '--'\n\n");
            printf("\t-h, --help\tprints out help\n");

            printf("adding options\n");

            printf("displaying options\n");

            printf("output options\n");
        }

    }




    return 0;
}

