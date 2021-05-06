#include "main.h"

int main(int argc, char **argv){
    dispatcher task_manger;                 // создаем объект класса диспетчер 
    task_manger.start(argc, argv);          //передаем параметры в метод start()
    return 0;
}
