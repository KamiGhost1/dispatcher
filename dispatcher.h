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
    void main_cycle();
    void init();
    int foundMinTime();
    void foundMaxTime();
    void life_step(int id);
    int count_not_served_task();
    void write_dataFiles();
    void create_dataFiles(task elem);
    int global_timer;
    int max_time;
    bool foundTask;
    vector<task> tasks_array;
};


#endif //CRC_DISPATCHER_H
