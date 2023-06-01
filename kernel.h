#ifndef KERNEL_H
#define KERNEL_H
#include"memory.h"
#include"process.h"
#include"cycle.h"

struct Kernel{
    int cycleCounter=0;
    Memory* mem;
    int state=0;
    Kernel(Memory* m);
    void allocRead(int blockid,Process& proc);
    void allocWrite(int blockid,Process& proc);
    void allocSize(int num,Process& proc);
    void releaseSize(int num,Process& proc);
    // void boot(Process& proc);
    // void syscall();
    // void schedule();
    // void idle();
    void kernelPrint(int counter,Process &proc,Cycle& cycle);
};
#endif