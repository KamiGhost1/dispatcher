//
// Created by ghost on 24.04.2021.
//

#ifndef DISPATCHER_H
#define DISPATCHER_H


#include "main.h"                               // подключаем заголовок main. в нем содержится все необхъодимое для работы

class dispatcher {                              //
public:                                         //-------------------------------------------------------
    void start(int C, char **V);                // публичный метод, для старта работы
private:                                        //-------------------------------------------------------
    void opener();                              // просто красивое превью, которое нужно просто как метка автора. т.е моя 
    void help();                                // меню помощи 
    int check_param(int C, char **V);           // функиця проверки параметров 
    void read_task(char *file_name);            // функция для чтения файла, в котором содержатся задачи
    char *strToChar(string m);                  // функиця перевода строки в массив символов, возвращает указатель
    void main_cycle_SRT();                      // основной цикл функции SRT
    void main_cycle_SJN();                      // основной цикл функции SJN
    void init();                                // инициализация. выставления начальных настроек
    void reset();                               // сброс. отчистка всех динамических данных из памяти
    int foundMinTime();                         // функция поиска минимального заказного времени 
    void foundMaxTime();                        // функция поиска максмального заказного времени
    void life_step(int id);                     // функция имитации выполнения задачи
    void life_step_SJN(int id);                     // функция имитации выполнения задачи
    int count_not_served_task();                // функция поиска задач, у которых отсавшееся время > 0
    void write_dataFiles();                     // функция записи данных в файл. тут происходит перебор задач и отправка в дочернюю ф.
    void create_dataFiles(task elem);           // дочерняя функция. создает файл и записывает
    void draw_graphs();                         // функция отрисовки данных
    void buildQueue();
    void queue_sort();
    string print_queue(string name);
    int global_timer;                           // глобальный счетчик тактов
    int max_time;                               // максимальное заказное время 
    bool foundTask;                             // флаг, показывающий, что задача для выполнения есть 
    vector<task> tasks_array;                   // динамическая память для задач
    vector<string> graph_names;                 // динамическая память для имен графиков
    vector<task> queue;
};


#endif //DISPATCHER_H
