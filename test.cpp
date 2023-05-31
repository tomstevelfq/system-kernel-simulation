#include<iostream>
#include<vector>
#include"memory.h"
#include"process.h"

using namespace std;
int main(){
    Memory mem;
    map<string,vector<string>> mp;
    map<int,string> m2;
    map<int,Process*> mpid;
    mp["init"]={"memory_allocate 16","fork_and_exec program1","wait","memory_read 10","memory_write 10","memory_read 0","exit"};
    mp["program1"]={"memory_read 0","memory_write 0","memory_allocate 2","memory_release 1","memory_allocate 3","memory_release 0","memory_allocate 2","exit"};
    Memory mem;
    Process proc1(&mem);
    int curprocessid=0;
    proc1.id=curprocessid++;
    proc1.pid=-1;
    Process *p=&proc1;
    mpid.insert({curprocessid,&proc1});
    while(true){
      string ret=p->excute();
      if(ret==""){//程序正常退出
        if(p->pid==-1){
          cout<<"执行完毕"<<endl;
          break;
        }else{
          p=mpid[p->pid];
        }
      }else{//执行新的程序
        Process* pro=new Process(&mem);
        pro->pid=p->id;
        pro->code=mp[ret];
        pro->id=curprocessid++;
        mpid.insert({curprocessid,pro});
        p=pro;
      }
    }

    //展示内存情况
    mem.displayPhyBlock();
    mem.displayVirtualBlock();
    p->displayBlockTable();
    return 0;
}