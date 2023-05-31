#include<iostream>
#include<queue>
#include<list>
#include<algorithm>
#include"memory_manager.h"
#include<stdlib.h>
#include<string.h>
#include<set>
#include<map>
#include<sstream>

using namespace std;

// MemoryManager::MemoryManager(){
//     memset(phy_block,0,sizeof(phy_block));
//     reserve=BLOCK_NUM;
// }

// int FIFOManager::allocOnePage(){
//     if(reserve==0){
//         return -1;
//     }
//     return true;
// }

struct Node{
    Node(){
        phy_id=-1;
    }
    int phy_id;//物理块id 为-1表示没分配
    bool rw=true;//读写权限
};

struct pNode{
    pNode(){
        virid=-1;
        processid=-1;
    }
    int virid;
    int processid;
};

struct PhyMemory{//物理内存
    vector<pNode> phyBlock(16,pNode());//物理内存  对应的virid为-1表示没有
    int remain=16;//剩余物理内存
    queue<int> q;//FIFO队列
};

struct VirMemory{//虚拟内存
    map<int,Node> vritualTable;//虚拟内存表
    
    void destroyVirBlock(int id){//删除一块虚存
        if(id!=-1){
            virtualTable[id].phy_id=-1;
        }
    }
};

struct Process{
    int pid=-1;
    VirMemory vmem;
};

map<int,set<int>> alloc;//alloc id集合   键为alloc id值为分配的虚拟内存id集合
vector<Node> virtualTable(1000,Node());
map<int,set<int>> proc_allocid; //每个进程包含的alloc id
int alloc_id=0;//从0开始
int vir_counter=0;//从0开始
vector<pNode> phyBlock(16,pNode());//物理内存  对应的virid为-1表示没有
int remain=16;//剩余物理内存
queue<int> q;//FIFO队列
vector<vector<string>> code;//进程代码存储
vector<int> codePos;//各进程执行到哪一行
vector<int> parent;//存储进程的父进程
int curProcess=0;//当前进程号

int fifo(){//分配一个fifo块
    int ret=q.front();
    q.pop();
    return ret;
}

int getFreeBlock(){//获取一块空闲物理内存
    for(int i=0;i<phyBlock.size();i++){
        if(phyBlock[i].virid==-1){
            return i;
        }
    }
    return -1;
}

void loadVirBlock(int virid,int phyid){//载入虚存到物理存
    phyBlock[phyid].virid=virid;
}

void releaseVirtualBlock(int virid){
    int phy_id=virtualTable[virid].phy_id;
    virtualTable[virid].phy_id=-1;
    destroyVirBlock(phy_id);//销毁物理内存中的虚拟内存占用
}

void setProcessId(int phyid,int processid){//物理内存所属进程号
    phyBlock[phyid].processid=processid;
}

int getOneBlock(){//物理内存分配
    if(remain==0){//没有空闲就内存调度
        int phyid=fifo();
        int virid=phyBlock[phyid].virid;
        phyBlock[phyid].virid=-1;
        destroyVirBlock(virid);
        return phyid;
    }
    return getFreeBlock();
}

void memory_alloc(int size,int processid){
    for(int i=0;i<size;i++){
        int phy_id=getOneBlock();
        setProcessId(phy_id,processid);
        loadVirBlock(vir_counter++,phy_id);
        alloc[alloc_id].insert(vir_counter);
    }
    proc_allocid[processid].insert(alloc_id);
    alloc_id++;
}

void memory_release(int id){//释放该alloc_id下的所有块
    for(auto it:alloc[id]){
        releaseVirtualBlock(it);
    }
}

bool excute(){//执行完成返回false
    stringstream ss(code[curProcess][codePos[curProcess]]);
    string cmd1;
    ss>>cmd1;
    if(cmd1=="wait"){

    }else if(cmd1=="exit"){
        if(parent[curProcess]==-1){
            return false;
        }else{
            curProcess=parent[curProcess];
        }
    }else{
        string cmd2;
        ss>>cmd2;
        int blockid;
        if(cmd1=="memory_read"){
            ss>>blockid;
            if(virtualTable[blockid].phy_id!=-1){
                cout<<"read ok"<<endl;
            }else{

            }
        }else if(cmd1=="memory_write"){
            
        }else if(cmd1=="memory_allocate"){

        }else if(cmd1=="memory_release"){

        }else{
            cout<<"excute error"<<endl;
            exit(-1);
        }
    }
    return true;
}

void displayVirtualBlock(){
    for(int i=0;i<vir_counter;i++){
        cout<<i<<"  ";
    }
    cout<<endl;
}

void displayPhyBlock(){
    for(int i=0;i<16;i++){
        cout<<phyBlock[i].processid<<"("<<i<<")"<<" ";
    }
    cout<<endl;
}

void displayBlockTable(){
    for(int i=0;i<vir_counter;i++){
        if(virtualTable[i].phy_id==-1){
            cout<<"- ";
        }else{
            cout<<virtualTable[i].phy_id<<" ";
        }
    }
    cout<<endl;
    for(int i=0;i<vir_counter;i++){
        if(virtualTable[i].rw){
            cout<<"W ";
        }else{
            cout<<"R ";
        }
    }
    cout<<endl;
}

void display(){
    displayVirtualBlock();
    displayPhyBlock();
    displayBlockTable();
}

int main(){
    code={//测试代码
        {"memory_allocate 16","fork_and_exec program1","wait","memory_read 10","memory_write 10","memory_read 0","exit"},
        {"memory_read 0","memory_write 0","memory_allocate 2","memory_release 1","memory_allocate 3","memory_release 0","memory_allocate 2","exit"}
    };
    codePos.push_back(0);
    codePos.push_back(0);
    parent.push_back(-1);//-1表示进程未使用或者父进程是init进程，是起始进程
    parent.push_back(-1);
    string str;
    while(excute()){
        display();
    }
    return 0;
}
