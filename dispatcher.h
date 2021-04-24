//
// Created by ghost on 24.04.2021.
//

#ifndef CRC_DISPATCHER_H
#define CRC_DISPATCHER_H

#include "task.h"
#include "main.h"
#include <cstring>
class dispatcher {
public:
    void start(int C, char **V);
private:
    void opener();
    void help();
    int check_param(int C, char **V);
    void read_task(char *file_name);
    char *strToChar(string m);
    vector<task> tasks_array;
};


#endif //CRC_DISPATCHER_H
