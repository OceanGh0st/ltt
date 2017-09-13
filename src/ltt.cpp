// ltt (LittleTerminalTasks) - Little program to organize tasks

#include "db.h"
#include "sh.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

inline bool is_file(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

int main(int argc, char *argv[]) {

    // check if datafile exists, if not create it
    if (is_file("data.xml") == 0) {
        FILE* f;
        f = fopen("data.xml", "wb+");
        fprintf(f, "<tasks>\n");
        fprintf(f, "</tasks>\n");
        fclose(f);
    }
        
    
    if(argc==1) {
        
        SH id(1);
        id.ltt_loop();

    } else {
        printf("Run ltt without arguments, and type 'h' or 'help' to display help");
        return 1;
    }

    return 0;
}

