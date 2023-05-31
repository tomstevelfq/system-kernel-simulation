#ifndef MEMORY_H
#define MEMORY_H
#include<iostream>
#include<queue>
#include<list>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<set>
#include<map>
#include<sstream>
#include"process.h"

using namespace std;

#define VBLOCKNUM 32
#define PBLOCKNUM 16

struct Node{
    Node();
    int phy_id;//物理块id 为-1表示没分配
    int rw=1;//读写权限  0读  1写  2没有权限
};

struct pNode{
    pNode();
    int virid;
    int processid;
};

struct Memory{//内存管理结构体
    int alloc_id=0;//从0开始
    int vir_counter=0;//从0开始
    int curProcess=0;//当前进程号
    map<int,set<int>> alloc;//alloc id集合   键为alloc id值为分配的虚拟内存id集合
    vector<int> virtualTable;//虚拟内存表
    vector<pNode> phyBlock;//物理内存  对应的virid为-1表示没有
    int remain=16;//剩余物理内存
    queue<int> q;//FIFO队列

    Memory();
    
    int fifo();

    int getFreeBlock();

    void loadVirBlock(int virid,int phyid);
    void setProcessId(int phyid,int processid);

    int getOneBlock();
    void displayPhyBlock();

    void destroyVirBlock(int id);

    void releaseVirtualBlock(int virid,struct Process& process);

    void memory_release(int allocid,struct Process& process);

    void memory_alloc(int size,int processid,struct Process& proc);

    void displayVirtualBlock();
};
#endif