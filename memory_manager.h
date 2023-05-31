#include<iostream>
#include<list>
using namespace std;

#define BLOCK_NUM 16

class MemoryManager{
    public:
        bool phy_block[BLOCK_NUM];//物理内存
        MemoryManager();
        virtual int allocOnePage()=0;//获取一页内存
        int reserve;
};

class FIFOManager:public MemoryManager{
    public:
        FIFOManager(){};
        int allocOnePage();
        list<int> q;//实现FIFO的物理页队列
};