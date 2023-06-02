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

FIFOMemory::FIFOMemory(){
    phyBlock=vector<pNode>(PBLOCKNUM,pNode());//物理块到虚拟块的映射
}

int FIFOMemory::fifo(){//分配一个fifo块
    int ret=q.front();
    q.pop();
    return ret;
}

int FIFOMemory::getFreeBlock(){//获取一块空闲物理内存
    for(int i=0;i<phyBlock.size();i++){
        if(phyBlock[i].virid==-1){
            return i;
        }
    }
    return -1;
}

void FIFOMemory::loadVirBlock(int virid,int phyid,Process& proc){//载入虚存到物理存
    phyBlock[phyid].virid=virid;
    proc.virtualTable[virid].phy_id=phyid;
}
void FIFOMemory::setProcessId(int phyid,int processid){//物理内存所属进程号
    phyBlock[phyid].processid=processid;
}

void FIFOMemory::displayPhyBlock(){
    cout<<"4.physical memory:"<<endl;
    for(int i=0;i<16;i++){
        if(phyBlock[i].virid==-1){
            cout<<"- ";
        }else{
            cout<<phyBlock[i].processid<<"("<<(*mpid)[phyBlock[i].processid]->virtualId[phyBlock[i].virid]<<")"<<" ";
        }
        if((i+1)%4==0){
            cout<<"|";
        }
    }
    cout<<endl;
}

void FIFOMemory::destroyVirBlock(int id){//删除一块虚存
    if(id!=-1){
        phyBlock[id].virid=-1;//清除占用
    }
}

int FIFOMemory::getVirid(int id){
    return phyBlock[id].virid;
}

void Memory::releaseVirtualBlock(int virid,struct Process& process){
    int phy_id=process.virtualTable[virid].phy_id;
    process.virtualTable[virid].phy_id=-1;
    process.virtualId[virid]=-1;
    if(process.rw[virid]==1){//拥有控制权
        destroyVirBlock(phy_id);//销毁物理内存中的虚拟内存占用
    }
}

void Memory::memory_release(int allocid,struct Process& process){//释放该alloc_id下的所有块
    for(auto it:alloc[allocid]){
        if(process.rw[it]==1){
            releaseVirtualBlock(it,process);
        }
        process.rw[it]=2;
    }
}

void Memory::memory_alloc(int size,int processid,Process& proc){
    for(int i=0;i<size;i++){
        int phy_id=getOneBlock();
        setProcessId(phy_id,processid);
        int virpos=getFreeVirPos(proc);
        proc.virtualId[virpos]=vir_counter++;
        proc.rw[virpos]=1;//权限W
        alloc[alloc_id].insert(virpos);
        loadVirBlock(virpos,phy_id,proc);
    }
    proc.allocid.insert(alloc_id);
    alloc_id++;
}

void Memory::displayVirtualBlock(Process& proc){
    cout<<"5.virtual memory:"<<endl;
    for(int i=0;i<VBLOCKNUM;i++){
        if(proc.rw[i]!=2){
            cout<<proc.virtualId[i]<<"  ";
        }else{
            cout<<"- ";
        }
        if((i+1)%4==0){
            cout<<"|";
        }
    }
    cout<<endl;
}

int Memory::getFreeVirPos(Process& proc){//虚表中的空闲位置
        for(int i=0;i<VBLOCKNUM;i++){
            if(proc.rw[i]==2){
                return i;
            }
        }
        return -1;
    }

int FIFOMemory::getOneBlock(){
    int freeblock=getFreeBlock();
    if(freeblock==-1){//没有空闲就内存调度
        int phyid=fifo();
        int virid=phyBlock[phyid].virid;
        phyBlock[phyid].virid=-1;//清物理表
        //virtualTable[virid]=-1;//清虚表
        q.push(phyid);
        return phyid;
    }
    q.push(freeblock);
    return freeblock;
}

