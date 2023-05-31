#ifndef PROCESS_H
#define PROCESS_H
#include<iostream>
#include<queue>
#include<list>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<set>
#include<map>
#include<sstream>
#include"memory.h"

using namespace std;

#define VBLOCKNUM 32
#define PBLOCKNUM 16

struct Process{
    string name;
    int id=-1;
    int pid=-1;//父进程的id
    vector<int> rw;//对虚拟内存的权限
    int line=0;//当前进程执行到哪一行
    vector<string> code;//存储代码
    set<int> allocid;  //alloc_id集合
    struct Memory *mem;
    
    Process(struct Memory* m);
    void displayBlockTable();

    string excute();

    void display();

    void fork(Process* par);
};
#endif