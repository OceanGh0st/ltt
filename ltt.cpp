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

    } else {
        printf("Run ltt without arguments, and type 'h' or 'help' to display help");
        return 1;
    }


    return 0;
}

