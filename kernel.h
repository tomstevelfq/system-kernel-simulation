#ifndef KERNEL_H
#define KERNEL_H
#include"memory.h"
#include"process.h"

struct Kernel{
    Memory* mem;
    Kernel(Memory* m);
    void allocRead(int blockid,Process& proc);
    void allocWrite(int blockid,Process& proc);
    void allocSize(int num,Process& proc);
    void releaseSize(int num,Process& proc);
};
#endif