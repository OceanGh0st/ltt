// ltt (LittleTerminalTasks) - Little program to organize tasks

#include "db.h"
#include "sh.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc==1) {
        
        SH id(1);
        id.ltt_loop();

    } else {
        printf("Run ltt without arguments, and type 'h' or 'help' to display help");
        return 1;
    }

    return 0;
}

