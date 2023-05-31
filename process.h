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

struct Process{
    Process(Memory* m){
        rw=vector<int>(1000,2);//初始化都没有权限
        mem=m;
    }
    int id=-1;
    int pid=-1;//父进程的id
    vector<int> rw;//对虚拟内存的权限
    int line=0;//当前进程执行到哪一行
    vector<string> code;//存储代码
    set<int> allocid;  //alloc_id集合
    Memory *mem;
    
    void displayBlockTable();

    void excute();
};