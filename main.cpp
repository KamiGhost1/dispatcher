#include "main.h"

int main(int argc, char **argv){
    dispatcher task_manger;
    task_manger.start(argc, argv);
    return 0;
}
