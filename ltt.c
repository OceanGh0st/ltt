// ltt (LittleTerminalTasks) - Little program to organize tasks

#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc==1) {
        printf("You are in interactive mode!\n");
    } else {
        if(strcmp(argv[1],"-h")==0) {
            printf("\nRun ltt without arguments to enter interactive mode\n");
            printf("Use the same commands only without '-'\n\n");
            printf("\nUSAGE: ltt [options] [task/list name/ID]\n\n");
            printf("\t-h\tprints out help\n");

            printf("displaying options\n");
            printf("\t-da\tdisplay all lists\n");
            printf("\t-dl *\tdisplay list(s)\n");
            printf("\t-dt *\tdisplay task(s)\n");

            printf("moving options\n");
            printf("\t-mvt * ^  move task to list\n");

            printf("adding options\n");
            printf("\t-rl *\tadd list(s)\n");
            printf("\t-rt *\tadd task(s)\n");

            printf("removing options\n");
            printf("\t-ra\tremove all lists\n");
            printf("\t-rl *\tremove list(s)\n");
            printf("\t-rt *\tremove task(s)\n\n");

        }

    }




    return 0;
}

