#ifndef KERNEL_H
#define KERNEL_H
#include"memory.h"
#include"process.h"
#include"cycle.h"
#include<map>

struct Kernel{
    int cycleCounter=0;
    struct Memory* mem;
    int state=0;
    Kernel(struct Memory* m);
    void allocRead(int blockid,struct Process& proc);
    void allocWrite(int blockid,struct Process& proc);
    void allocSize(int num,struct Process& proc);
    void releaseSize(int num,struct Process& proc);
    // void boot(Process& proc);
    // void syscall();
    // void schedule();
    // void idle();
    void kernelPrint(int counter,struct Process &proc,struct Cycle& cycle);
};
#endif