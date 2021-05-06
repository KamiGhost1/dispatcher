//
// Created by ghost on 24.04.2021.
//

#ifndef CRC_TASK_H
#define CRC_TASK_H

#include "main.h"

class task {                     // класс задачи. имеет все публичные поля
public:                          // 
    string name;                 // имя задачи
    int init_time, work_time;    // время инициализации, заказное время задачи
    vector<int> statistic;       // динамические данные статистики выполнения задачи
};                               // 


#endif //TASK_H
