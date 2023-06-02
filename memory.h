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
#include<unordered_map>

using namespace std;

#define VBLOCKNUM 32
#define PBLOCKNUM 16

struct Node{
    Node();
    int phy_id;//物理块id 为-1表示没分配
    int rw=2;//读写权限  0读  1写  2没有权限
    int vid=-1;//虚拟内存id是多少
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
    int remain=16;//剩余物理内存
    map<int,struct Process*> *mpid;

    virtual int getFreeBlock()=0;

    virtual void loadVirBlock(int virid,int phyid,struct Process& proc)=0;
    virtual void setProcessId(int phyid,int processid)=0;

    virtual int getOneBlock()=0;
    virtual void displayPhyBlock()=0;

    virtual void destroyVirBlock(int id)=0;

    virtual int getVirid(int id)=0;

    void releaseVirtualBlock(int virid,struct Process& process);

    void memory_release(int allocid,struct Process& process);

    void memory_alloc(int size,int processid,struct Process& proc);

    void displayVirtualBlock(Process& proc);

    int getFreeVirPos(Process& proc);
};

struct FIFOMemory:Memory{
    queue<int> q;//FIFO队列
    vector<pNode> phyBlock;//物理内存  对应的virid为-1表示没有
    int getFreeBlock();
    int getOneBlock();
    int fifo();
    void loadVirBlock(int virid,int phyid,struct Process& proc);
    void setProcessId(int phyid,int processid);
    void displayPhyBlock();
    void destroyVirBlock(int id);
    int getVirid(int id);
    FIFOMemory();
};


struct LRUMemory:Memory{
    list<pNode> cacheList;  // 双向链表用于维护页面访问顺序
    unordered_map<int, list<pNode>::iterator> cacheMap;  // 哈希表用于快速查找页面
    // int getOneBlock(){
    //     int pblock;
    //     if(cacheList.size()<PBLOCKNUM){
    //         pblock=getFreeBlock();
    //         cacheList.push_front(pblock);
    //         cacheMap[pblock] = cacheList.begin();
    //     }else{
    //         pblock = cacheList.back();
    //         cacheList.pop_back();
    //         cacheMap.erase(pblock);
    //     }
        
    //     // 将页面插入链表头部表示最新访问
    //     cacheList.push_front(pblock);
    //     cacheMap[pblock] = cacheList.begin();
    // }
};

struct LFUMemory:Memory{
    int getOneBlock();
};

struct MFUMemory:Memory{
    int getOneBlock();
};
#endif