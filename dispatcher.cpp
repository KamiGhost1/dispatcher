//

// Created by ghost on 24.04.2021.
//
#include "dispatcher.h"


void dispatcher::start(int C, char **V) {
    int mode;
    mode = this->check_param(C, V);
    if(mode == 1){
        main_cycle();
    }
}

void dispatcher::opener() {
    cout<<endl;
    cout<<"\t__    __      ______ "<<endl;
    cout<<"\t| |  / /   / /______\\ \\   | | \\  / | |   | |"<<endl;
    cout<<"\t| | / /    | |      | |   | |\\ \\/ /| |   | |"<<endl;
    cout<<"\t| |/ /     | |      | |   | |  --  | |   | |"<<endl;
    cout<<"\t| |\\ \\     | |      | |   | |      | |   | |"<<endl;
    cout<<"\t| | \\ \\    | |      | |   | |      | |   | |"<<endl;
    cout<<"\t| |  \\ \\   | |______| \\   | |      | |   | |"<<endl;
    cout<<"\t| |   \\ \\  \\ \\______| \\\\  | |      | |   | |"<<endl;
    cout<<"\n\n\tK@mi soft\n\tgithub.com:kamighost1\n"<<endl;
}

int dispatcher::check_param(int C, char **V) {
    if(C == 1){
        this->opener();
        cout<<"\n\tthis program modelling task manager\n"<<endl;
        exit(0);
    }
    if(C==2){
        if(!strcmp(V[1],"-h")){
            help();
            exit(0);
        }
    }
    if(C == 3){
        if(!strcmp(V[1],"-i")){
            this->read_task(V[2]);
            return 1;
        }
    }
    cout<<"unknown parameters. use -h for more info."<<endl;
    return -1;
}

void dispatcher::help() {
    cout<<"\tHELP MENU"<<endl;
    cout<<"-h - help"<<endl;
    cout<<"-i < task file > - open task list from file"<<endl;
//    cout<<"-h - help"<<endl;
//    cout<<"-h - help"<<endl;
}

void dispatcher::read_task(char *file_name) {
    ifstream file;
    file.open(file_name);
    if(!file){
        cout<<"File "<<file_name<<" not found!"<<endl;
        exit(2);
    }
    string str;
    char *sep = " ;";
    char *c;
    task list;
    while (getline(file, str)){
        c = strToChar(str);
        list.name = strtok(c,sep);
        list.init_time = atoi(strtok(NULL,sep));
        list.work_time = atoi(strtok(NULL,sep));
        delete c;
        tasks_array.push_back(list);
    }
    file.close();
}

char* dispatcher::strToChar(string m) {
    char *mes = new char[m.length()];
    for(int i=0;i<m.length();i++){
        mes[i]=m[i];
    }
    return mes;
}

int dispatcher::count_not_served_task() {
    int count = 0;
    for(int i = 0; i < this->tasks_array.size();i++){
        if(this->tasks_array[i].work_time>0){
            count++;
        }
    }
    return count;
}

void dispatcher::init() {
    this->global_timer = 0;
    this->foundTask = false;
    this->max_time = 0;
    this->foundMaxTime();
}

void dispatcher::life_step(int id) {
    this->tasks_array[id].work_time = this->tasks_array[id].work_time - 1;
    this->tasks_array[id].statistic.push_back(this->global_timer);
    this->global_timer++;
}

int dispatcher::foundMinTime() {
    int id = 0;
    int min = this->max_time + 1;
    for(int i = 0; i < this->tasks_array.size();i++){
        if(this->global_timer >= this->tasks_array[i].init_time){
            if(min > this->tasks_array[i].work_time && this->tasks_array[i].work_time > 0){
                min = this->tasks_array[i].work_time;
                id = i;
                this->foundTask = true;
            }
        }
    }
    return id;
}

void dispatcher::foundMaxTime() {
    for(int i = 0; i<this->tasks_array.size();i++){
        if(this->max_time<this->tasks_array[i].work_time)
            this->max_time = this->tasks_array[i].work_time;
    }
}



void dispatcher::main_cycle() {
    this->init();
    int id = 0;
    int check_timer = 0;
    if(this->tasks_array.size() > 0){
        cout<<"task to served: "<<this->tasks_array.size()<<endl;
        while(this->count_not_served_task() > 0){
            cout<<this->global_timer<<endl;
            this->foundTask = false;
            id = foundMinTime();
            if(this->foundTask == 1){
                cout<<"this: "<< id <<" and found: "<<foundTask<<endl;
                this->life_step(id);
            }else{
                this->global_timer++;
            }
        }
        cout<<"end served"<<endl;
    }else{
        cout<<"no task in work";
        exit(0);
    }
}