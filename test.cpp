#include<iostream>
#include<vector>
#include"cycle.h"

using namespace std;
// int main(){
//     Memory mem;
//     map<string,vector<string>> mp;
//     map<int,string> m2;
//     map<int,Process*> mpid;
//     mp.insert({"init",{"memory_allocate 16","fork_and_exec program1","wait","memory_read 10","memory_write 10","memory_read 0","exit"}});
//     mp["program1"]={"memory_read 0","memory_write 0","memory_allocate 2","memory_release 1","memory_allocate 3","memory_release 0","memory_allocate 2","exit"};
//     Process proc1(&mem);
//     proc1.pid=-1;
//     proc1.code=mp["init"];
//     Process *p=&proc1;
//     mpid.insert({proc1.id,&proc1});
//     Kernel kernel(&mem);
//     while(true){
//       auto ret=p->excute();
//       if(ret.first==""){//程序正常退出
//         continue;
//       }else if(ret.first=="exit"){
//         if(p->pid==-1){
//           cout<<"执行完毕"<<endl;
//           break;
//         }else{
//           p=mpid[p->pid];
//         }
//       }else if(ret.first=="read"){
//         kernel.allocRead(ret.second,*p);
//       }else if(ret.first=="write"){
//         kernel.allocWrite(ret.second,*p);
//       }else if(ret.first=="alloc"){
//         if(p->pid==-1){
//           cout<<"执行完毕"<<endl;
//           break;
//         }else{
//           p=mpid[p->pid];
//         }
//       }else if(ret.first=="release"){
//         if(p->pid==-1){
//           cout<<"执行完毕"<<endl;
//           break;
//         }else{
//           p=mpid[p->pid];
//         }
//       }else{//执行新的程序
//         Process* pro=new Process(&mem);
//         pro->code=mp[ret.first];
//         mpid.insert({pro->id,pro});
//         pro->fork(p);
//         p=pro;
//       }
//     }

//     p->display();
//     return 0;
// }

int main(){
  Cycle cycle;
  cycle.start();
  return 0;
}