#ifndef CYCLE_H
#define CYCLE_H
#include"process.h"
#include"memory.h"
#include"kernel.h"

struct Cycle{//调度器
    int cycleCounter=0;
    Memory *mem;
    Kernel *kernel;
    Process *process;
    map<string,vector<string>> mp;
    map<int,Process*> mpid;
    int state=0;//0用户态  1kernel态
    Cycle();
    void start();
    void init();
    void cyclePrint(Process& proc);
};

#endif