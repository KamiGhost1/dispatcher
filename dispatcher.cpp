//

// Created by ghost on 24.04.2021.
//
#include "dispatcher.h"


void dispatcher::start(int C, char **V) {
    int mode;                             // переменная режима работы
    mode = this->check_param(C, V);       // проверка параметров запуска. например ./exec -i task.txt
    if(mode == 1){                        //
        this->main_cycle_SRT();               // запуск основного цикла
        this->write_dataFiles();          // запись данный в файлы                
        this->draw_graphs();              // отрисока графиков
    }
    if(mode == 2){
        this->main_cycle_SRT();
        this->write_dataFiles();
    }
    if(mode == 3){
        this->main_cycle_SJN();
        this->write_dataFiles();
    }
    if(mode == 4){
        this->main_cycle_SJN();            // запуск основного цикла
        this->write_dataFiles();          // запись данный в файлы
        this->draw_graphs();              // отрисока графиков
    }
    this->reset();                        // отчистка памяти и сброс настроек до начальных
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
    if(C == 1){                                                   // если было передано только назание программы
        this->opener();
        cout<<"\n\tthis program modelling task manager\n"<<endl;
        exit(0);
    }
    if(C==2){
        if(!strcmp(V[1],"-h")){                                   // если был флаг -h, то отрисовать меню помощи 
            help();
            exit(0);
        }
    }
    if(C == 3){
        if(!strcmp(V[1],"-i")){                                   // если был флаг -i и потом еще одно значение, попробовать открыть файл
            this->read_task(V[2]);                                // чтение файла 
            return 1;
        }
    }
    if(C == 4){
        if(!strcmp(V[1],"-i") && !strcmp(V[3],"--no-draw") ){     // запуск работы без отрисовки 
            this->read_task(V[2]);
            return 2;
        }
        if(!strcmp(V[1],"-i") && !strcmp(V[3],"-sjn") ){
            this->read_task(V[2]);
            return 4;
        }
    }
    if(C == 5){
        if(!strcmp(V[1],"-i") && !strcmp(V[3],"--no-draw") && !strcmp(V[4],"-sjn")){ // запуск работы без отрисовки
            this->read_task(V[2]);
            return 3;
        }
    }
    cout<<"unknown parameters. use -h for more info."<<endl;
    return -1;
}

void dispatcher::help() {
    cout<<"\tHELP MENU"<<endl;
    cout<<"-h - help"<<endl;
    cout<<"-i < task file > - open task list from file"<<endl;
    cout<<"-i < task file > -sjn - open task list from file and SJN mode"<<endl;
    cout<<"-i < task file > --no-draw - open task list from file and no draw graphs"<<endl;
    cout<<"-i < task file > --no-draw -sjn - open task list from file and no draw graphs and SJN mode"<<endl;
}

void dispatcher::read_task(char *file_name) {
    ifstream file;
    file.open(file_name);                                    // попробовать открыть файл
    if(!file){                                               // если файл не открыт, 
        cout<<"File "<<file_name<<" not found!"<<endl;       // тогда уведомиь пользователя 
        exit(2);
    }                                                        //иначе 
    string str;
    char *sep = " ;";                                        // создаем массиф фильтруемых значений
    char *c;                                                 // указатель на тип char 
    task list;                                               // тип задачи 
    while (getline(file, str)){                              // считываем строку 
        c = strToChar(str);                                  // превращаем строку в массив символов 
        list.name = strtok(c,sep);                           // до первой ; - имя
        list.init_time = atoi(strtok(NULL,sep));             // до второй - время инициализации
        list.work_time = atoi(strtok(NULL,sep));             // до третей - время выполнения
        delete c;                                            // удаляем выделенную память символов 
        tasks_array.push_back(list);                         // добавляем задачу в массив задач
    }
    file.close();                                            // закрываем поток
}

char* dispatcher::strToChar(string m) {
    char *mes = new char[m.length()];                        // выделяем память по длинне строки 
    for(int i=0;i<m.length();i++){
        mes[i]=m[i];                                         // копируем строку в массив символов 
    }
    return mes;                                              // возвращаем указатель на массив
}

int dispatcher::count_not_served_task() {
    int count = 0;
    for(int i = 0; i < this->tasks_array.size();i++){
        if(this->tasks_array[i].work_time>0){                 // если время выполнения задачи > 0 
            count++;                                          // счетчик + 1
        }
    }
    return count;                                             // вернуть счетчик
}
 
void dispatcher::init() {
    this->global_timer = 0;                                   // установить глобальный счетчик в 0
    this->foundTask = false;                                  // флаг найденной задачи поставить в 0
    this->max_time = 0;                                       // максимальное заказное время в 0 
    this->foundMaxTime();                                     // поиск максимального по задачам, если они есть
}

void dispatcher::reset() {
    this->init();                                             // восстановление исхдного состояния
    this->graph_names.clear();                                // отчистить динамический массив имен 
    for(int i = 0; i<this->tasks_array.size();i++){           // в каждой динамической задаче
        this->tasks_array[i].statistic.clear();               // удаляем динамическую статистику
    }
    this->tasks_array.clear();                                // отчищаем динамический массив задач
    this->queue.clear();
}

void dispatcher::life_step(int id) {
    this->tasks_array[id].work_time = this->tasks_array[id].work_time - 1;       // уменньшаем на 1 заказное время
    this->tasks_array[id].statistic.push_back(this->global_timer);               // добавляем в статистику данные, что ззадача выполнена на этом шаге
    this->global_timer++;                                                        // глобальный счетчик + 1
}

void dispatcher::life_step_SJN(int id) {
    string log;
    while(this->tasks_array[id].work_time>0){
        this->buildQueue(this->tasks_array[id].name);
        log = this->print_queue();
        cout<<this->global_timer<<" ; cpu: 100 ; "<< "task: "<<tasks_array[id].name<<"; queue: "<<log<<endl;
        this->tasks_array[id].work_time = this->tasks_array[id].work_time - 1;
        this->tasks_array[id].statistic.push_back(this->global_timer);
        this->global_timer++;
    }
}

int dispatcher::foundMinTime() {
    int id = 0;                                                                               // идентификатор задачи
    int min = this->max_time + 1;                                                             // сначала присвоим максимум
    for(int i = 0; i < this->tasks_array.size();i++){
        if(this->global_timer >= this->tasks_array[i].init_time){                             // задача уже прошла момент инициализации???
            if(min > this->tasks_array[i].work_time && this->tasks_array[i].work_time > 0){   // заказное время > 0 && оно < min ??
                min = this->tasks_array[i].work_time;                                         // минимальное заказное время
                id = i;                                                                       // id задачи
                this->foundTask = true;                                                       // задача для выполнения есть 
            }
        }
    }
    return id;
}

void dispatcher::foundMaxTime() {
    for(int i = 0; i<this->tasks_array.size();i++){
        if(this->max_time < this->tasks_array[i].work_time)               // максимальное время < зазного времени этой задачи?
            this->max_time = this->tasks_array[i].work_time;              // максимальное время = зазному времени этой задачи
    }
}



void dispatcher::main_cycle_SRT() {
    this->init();                                                                          // инициализация 
    int id = 0;
    string log;
    if(this->tasks_array.size() > 0){                                                      //задачи есть??
        cout<<"task to served: "<<this->tasks_array.size()<<endl;
        while(this->count_not_served_task() > 0){                                          // пока есть не обслужанные задачи
            this->foundTask = false;                                                       // обнуляем флаг
            id = foundMinTime();// ищем задачу с минимальным заказным времеем
            this->buildQueue(this->tasks_array[id].name);
            log = this->print_queue();
            if(this->foundTask == 1){                                                      // задача есть ?
                cout<<this->global_timer<<" ; cpu: 100 ; "<< "task: "<<tasks_array[id].name<<"; queue: "<<log<<endl;
                this->life_step(id);                                                       // имитация выполнения задачи
            }else{                                                                         // иначе
                cout<<this->global_timer<<" ; cpu 0 ; "<<endl;
                this->global_timer++;                                                      // просто +1 к глобалному счетчику
            }
        }                                                                                  //--------------------------------
        this->global_timer++;                                                              // финальный +1 к глобалному счетчику
        cout<<"end served"<<endl;
    }else{
        cout<<"no task in work";
        exit(0);
    }
}

void dispatcher::main_cycle_SJN() {
    this->init();                                                                          // инициализация
    int id = 0;
    if(this->tasks_array.size() > 0){                                                      //задачи есть??
        cout<<"task to served: "<<this->tasks_array.size()<<endl;
        while(this->count_not_served_task() > 0){
            this->foundTask = false;
            id = foundMinTime();
            if(this->foundTask == 1){
                this->life_step_SJN(id);
            }else{
                cout<<this->global_timer<<" ; cpu 0 ; "<<endl;
                this->global_timer++;
            }
        }
        this->global_timer++;
        cout<<"end served"<<endl;
    }else{
        cout<<"no task in work";
        exit(0);
    }
}

void dispatcher::create_dataFiles(task elem) {
    ofstream file, stat;                                  // создание потока на запись 
    bool found;                                           // флаг, что задача выполняляась в этот момент времени
    string str = "data/"+elem.name+".data.txt";           // имя записываемого файла
    this->graph_names.push_back(str);                     // добавить в массив имен 
    file.open(str);                                       // открыть поток
    stat.open("data/"+elem.name+".csv");                  // открыт поток записи статистики в csv
    int last = 0;
    for(int i = 0; i < this->global_timer;i++){
        found = false;                                    // обнуление
        for(int j = 0; j<elem.statistic.size();j++){
            if(elem.statistic[j] == i)                    // проврека статистики задачи в этот момент времени
                found = true;                             // если она активна, то присваиваем 1 
        }
        if(found){                                        // если была активна
            file<<i<<" "<<10<<endl;                       // запись данных для графика
            stat<<i<<";"<<elem.name<<endl;                // запись статистики
        }else{                                            //иначе 
            file<<i<<" "<<0<<endl;                        // -//-, значение 0
            stat<<i<<";"<<0<<endl;                        // -//-, значение 0
        }
    }
    file.close();                                         // закрыть поток
    stat.close();                                         // закрыть поток 
}

void dispatcher::write_dataFiles() {
    for(int i = 0; i < this->tasks_array.size();i++){
        this->create_dataFiles(this->tasks_array[i]);     // перебор всех задач и передача их на запись в файл
    }
}

void dispatcher::draw_graphs() {
    FILE *gp = popen("gnuplot -persist","w");       // открыть процесс gnuplot
    string cmd = "plot ";                                          // строка, которую мы передадим в процесс 
    if(!gp){                                                       // если процесс на открыт
        cout<<"Error"<<endl;                                       // ошибка
        exit(1);
    }else{                                                         //иначе 
        for(int i=0;i<graph_names.size();i++){                     //пока есть имена в маассиве имен 
            cmd += '"'+graph_names[i]+'"'+" with filledcurves, ";  // добавлем эти графики к выполнению 
        }
        cmd+='\n';                                                 // добавляем enter 
        char *gpcmd;
        gpcmd = strToChar(cmd);                                    // переводим стринг в массив символов
        fprintf(gp, gpcmd);                                        // пишем в поток 
        delete(gpcmd);                                             // отчищаем память 
        pclose(gp);                                                // закрываем процесс
    }
}

void dispatcher::buildQueue(string name) {
    if(this->queue.size()>0)
        this->queue.clear();
    char *name1, *name2;
    name1 = this->strToChar(name);
    if(tasks_array.size()>0){
        for(int i = 0;i<this->tasks_array.size();i++){
            name2 = this->strToChar(this->tasks_array[i].name);
            if(this->global_timer >= this->tasks_array[i].init_time){
                if(this->tasks_array[i].work_time > 0 && strcmp(name1,name2))
                    this->queue.push_back(this->tasks_array[i]);
            }
            delete name2;
        }
        if(this->queue.size()>1){
            this->queue_sort();
        }
    }
}



void dispatcher::queue_sort(){
    sort(queue.begin(), queue.end(), [](task a, task  b){
        return a.work_time < b.work_time;
    });
}


string dispatcher::print_queue() {
    string str;
    if(queue.size()>1){
        str = queue[1].name;
        if(queue.size()>2){
            for(int i = 2;i < queue.size();i++){
                str+="; "+queue[i].name;
            }
        }
    }else{
        str = "0";
    }
    return str;
}