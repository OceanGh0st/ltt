// ltt (LittleTerminalTasks) - Little program to organize tasks

#include "db.h"
#include "sh.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc==1) {
        
        // load config files
        // load xml file

        // run command loop
        // open new shell
        // ltt_loop()

        // perform any shutdown/cleanup
        // close shell
        // close xml file


        printf("You are in interactive mode!\n");

        SH id(1);
        id.ltt_loop();
        printf("After");





/*
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
*/
    } else {
        printf("Run ltt without arguments, and type 'h' or 'help' to display help");
        return 1;
    }


    return 0;
}

