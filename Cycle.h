#ifndef CYCLE_H
#define CYCLE_H
#include"process.h"
#include"memory.h"
#include"kernel.h"
#include<queue>
#include<map>

using namespace std;

struct Cycle{//调度器
    int cycleCounter=0;
    struct Memory *mem;
    struct Kernel *kernel;
    struct Process *process;
    map<string,vector<string>> mp;
    map<int,struct Process*> mpid;
    queue<Process*> q;//就绪队列
    int state=1;//0用户态  1kernel态
    Cycle();
    void start();
    void init();
    void cyclePrint(struct Process& proc);
};

#endif