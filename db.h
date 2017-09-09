#include <string>

#ifndef _db_H
#define _db_H

class DB {
private:
    int id;

public:
    DB(int id);
    int display_all();
    int display_list(const char* list);
    int move_task(const char* task_t, const char* list);
    int add_list(const char* new_list);
    int add_task(const char* new_task, const char* list);
    int remove_all();
    int remove_list(const char* list);
    int remove_task(const char* task);
    int clear_list(const char* list);
};

#endif
