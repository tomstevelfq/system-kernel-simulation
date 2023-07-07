#include"cycle.h"
#include<fstream>
#include <filesystem>

Cycle::Cycle(string path,string replace){
  this->path=path;
  if(replace=="fifo"){
    mem=new FIFOMemory();
  }else if(replace=="lru"){
    mem=new LRUMemory();
  }else if(replace=="lfu"){
    mem=new LFUMemory();
  }else{
    mem=new MFUMemory();
  }
    mem=new MFUMemory();
    kernel=new Kernel(mem);
    process=new Process(mem);
    mem->mpid=&mpid;
}

void Cycle::init(){
  //读文件里面的代码
  //string path="test";
  for(const auto& file:filesystem::directory_iterator(path)){
    ifstream ifile(file.path());
    string name=file.path().filename().string();
    string line;
    vector<string> v;
    while(getline(ifile,line)){
      v.push_back(line);
    }
    mp[name]=v;
  }
  return;
}

void Cycle::start(){
    init();
    process->pid=0;
    process->name="init";
    process->code=mp["init"];
    q.push(process);
    mpid.insert({process->id,process});
    Process* p;
    while(!q.empty()){
      if(cycleCounter==38){
        cout<<"df"<<endl;
      }
      p=q.front();
      if(p->isDead()){
        q.pop();
        continue;
      }
      if(state){
        kernel->kernelPrint(cycleCounter,*p,*this);
      }else{
        auto ret=p->excute(cycleCounter);
        if(ret.first==""){
          cycleCounter++;
          continue;
        }else if(ret.first=="exit"){
          if(p->pid==0){
            cycleCounter++;
            kernel->state=1;
            kernel->kernelPrint(cycleCounter,*p,*this);
            cout<<"执行完毕"<<endl;
            q.pop();
            break;
          }else{
            q.pop();
            state=1;
            kernel->state=1;
          }
        }else if(ret.first=="read"){
          kernel->allocRead(ret.second,*p);
          state=1;
          kernel->state=4;
        }else if(ret.first=="write"){
          kernel->allocWrite(ret.second,*p);
          state=1;
          kernel->state=4;
        }else if(ret.first=="alloc"){
          kernel->allocSize(ret.second,*p);
          state=1;
          kernel->state=1;
        }else if(ret.first=="release"){
          kernel->releaseSize(ret.second,*p);
          state=1;
          kernel->state=1;
        }else if(ret.first=="wait"){
          state=1;
          kernel->state=1;
          q.push(p);
          q.pop();
        }else{//执行新的程序
          Process* pro=new Process(mem);
          pro->name=ret.first;
          pro->code=mp[ret.first];
          mpid.insert({pro->id,pro});
          pro->fork(p);
          p=pro;
          state=1;
          kernel->state=1;
          q.push(p);
          q.push(pro);
        }
      }
      cycleCounter++;
    }
}

void Cycle::cyclePrint(Process& proc){
    if(state){
        kernel->kernelPrint(cycleCounter,proc,*this);
    }else{
        proc.processPrint(cycleCounter);
    }
}