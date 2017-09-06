#include <string>

#ifndef _sh_H
#define _sh_H

class SH {
private:
    int id;


public:
    SH(int id);
    int ltt_loop();
    char* ltt_readline();
    char** ltt_splitline(char *line);
    int ltt_execute(char **args);
    int ltt_launch(char **args);
    int ltt_help(char **args);
    char *buildin_str[];
    int ltt_num_builtins();

};
#endif
