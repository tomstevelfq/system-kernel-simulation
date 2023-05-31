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

Node::Node(){
    phy_id=-1;
}

pNode::pNode(){
    virid=-1;
    processid=-1;
}

Memory::Memory(){
    phyBlock=vector<pNode>(PBLOCKNUM,pNode());//物理块到虚拟块的映射
    virtualTable=vector<int>(VBLOCKNUM,-1);//虚拟块到物理块的映射 为-1表示没有
}

int Memory::fifo(){//分配一个fifo块
    int ret=q.front();
    q.pop();
    return ret;
}

int Memory::getFreeBlock(){//获取一块空闲物理内存
    for(int i=0;i<phyBlock.size();i++){
        if(phyBlock[i].virid==-1){
            return i;
        }
    }
    return -1;
}

void Memory::loadVirBlock(int virid,int phyid){//载入虚存到物理存
    phyBlock[phyid].virid=virid;
    virtualTable[virid]=phyid;
}
void Memory::setProcessId(int phyid,int processid){//物理内存所属进程号
    phyBlock[phyid].processid=processid;
}

int Memory::getOneBlock(){//物理内存分配
    if(remain==0){//没有空闲就内存调度
        int phyid=fifo();
        int virid=phyBlock[phyid].virid;
        phyBlock[phyid].virid=-1;
        destroyVirBlock(virid);
        return phyid;
    }
    return getFreeBlock();
}
void Memory::displayPhyBlock(){
    for(int i=0;i<16;i++){
        cout<<phyBlock[i].processid<<"("<<i<<")"<<" ";
    }
    cout<<endl;
}

void Memory::destroyVirBlock(int id){//删除一块虚存
    if(id!=-1){
        phyBlock[id].virid=-1;//清除占用
    }
}

void Memory::releaseVirtualBlock(int virid){
    int phy_id=virtualTable[virid];
    virtualTable[virid]=-1;
    destroyVirBlock(phy_id);//销毁物理内存中的虚拟内存占用
}

void Memory::memory_release(int id){//释放该alloc_id下的所有块
    for(auto it:alloc[id]){
        releaseVirtualBlock(it);
    }
}

void Memory::memory_alloc(int size,int processid,Process& proc){
    for(int i=0;i<size;i++){
        int phy_id=getOneBlock();
        setProcessId(phy_id,processid);
        loadVirBlock(vir_counter++,phy_id);
        alloc[alloc_id].insert(vir_counter);
    }
    proc.allocid.insert(alloc_id);
    alloc_id++;
}

void Memory::displayVirtualBlock(){
    for(int i=0;i<vir_counter;i++){
        cout<<i<<"  ";
    }
    cout<<endl;
}

// void display(){
//     displayVirtualBlock();
//     displayPhyBlock();
//     displayBlockTable();
// }

