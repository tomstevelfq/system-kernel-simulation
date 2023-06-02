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
#include"cycle.h"

using namespace std;

#define VBLOCKNUM 32
#define PBLOCKNUM 16

struct Process{
    static int idcounter;
    int state=1;//进程状态  1 2 3 4 5
    string name;
    int id=-1;
    int pid=-1;//父进程的id
    vector<int> rw;//对虚拟内存的权限
    int line=0;//当前进程执行到哪一行
    vector<string> code;//存储代码
    set<int> allocid;  //alloc_id集合
    vector<int> virtualId;//进程中virtualtable pos到虚存id的映射
    struct Memory *mem;
    vector<struct Node> virtualTable;
    
    Process(struct Memory* m);
    void displayBlockTable();

    pair<string,int> excute(int counter);

    void display();

    void fork(Process* par);

    void processPrint(int counter);

    bool isDead();

    void destroyStorage();
};
#endif