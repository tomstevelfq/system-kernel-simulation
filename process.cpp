#include"process.h"

Process::Process(Memory* m){
    rw=vector<int>(1000,2);//初始化都没有权限
    virtualId=vector<int>(VBLOCKNUM,-1);
    virtualTable=vector<Node>(VBLOCKNUM,Node());
    mem=m;
    id=idcounter++;
}

int Process::idcounter=1;

void Process::displayBlockTable(){
    cout<<"6.page table:"<<endl;
    for(int i=0;i<VBLOCKNUM;i++){
        if(rw[i]==2){
            cout<<"- ";
        }else{
            if(i==mem->getVirid(virtualTable[i].phy_id)){
                cout<<virtualTable[i].phy_id<<" ";
            }else{
                cout<<"- ";
            }
        }
        if((i+1)%4==0){
            cout<<"|";
        }
    }
    cout<<endl;
    for(int i=0;i<VBLOCKNUM;i++){
        if(rw[i]==2||virtualTable[i].phy_id==-1){
            cout<<"- ";
        }else{
            if(rw[i]==0){
                cout<<"R ";
            }else if(rw[i]==1){
                cout<<"W ";
                // if(mem->phyBlock[virtualTable[i].phy_id].processid==id){
                //     cout<<"W ";
                // }else{
                //     cout<<"- ";
                // }
            }else{
                cout<<"- ";
            }
        }
        if((i+1)%4==0){
            cout<<"|";
        }
    }
    cout<<endl;
}

pair<string,int> Process::excute(int counter){//执行完成返回false
    if(line>=code.size()){
        return {"exit",-1};
    }
    while(line<code.size()){//循环执行指令
        processPrint(counter);//输出打印
        stringstream ss(code[line++]);
        string cmd1;
        ss>>cmd1;
        if(cmd1=="exit"){
            state=5;
            destroyStorage();
            return {"exit",-1};
        }else{
            int blockid;
            int num;
            string program;
            if(cmd1=="memory_read"){
                ss>>blockid;
                int phid=virtualTable[blockid].phy_id;
                if(rw[blockid]!=2&&phid!=-1&&mem->getVirid(phid)==blockid){
                    cout<<"read ok"<<endl;
                    mem->access(phid);
                    break;
                }else{
                    // int phy_id=mem->getOneBlock();
                    // mem->setProcessId(phy_id,id);
                    // mem->loadVirBlock(blockid,phy_id,*this);
                    // cout<<"分配读物理内存"<<endl;
                    // rw[blockid]=1;
                    cout<<"fenpeidu"<<endl;
                    return {"read",blockid};
                }
            }else if(cmd1=="memory_write"){
                ss>>blockid;
                if(rw[blockid]==1){
                    int phid=virtualTable[blockid].phy_id;
                    mem->access(phid);
                    cout<<"write ok"<<endl;
                    break;
                }else{
                    // int phy_id=mem->getOneBlock();
                    // mem->setProcessId(phy_id,id);
                    // mem->loadVirBlock(blockid,phy_id,*this);
                    // cout<<"分配写物理内存"<<endl;
                    // rw[blockid]=1;
                    return {"write",blockid};
                }
            }else if(cmd1=="memory_allocate"){
                ss>>num;
                // mem->memory_alloc(num,id,*this);
                // cout<<"分配内存"<<endl;
                return {"alloc",num};
            }else if(cmd1=="memory_release"){
                ss>>num;
                // mem->memory_release(num,*this);
                // cout<<"释放内存"<<endl;
                return {"release",num};
            }else if(cmd1=="fork_and_exec"){
                ss>>program;
                cout<<"调用程序"<<endl;
                return {program,-1};
            }else if(cmd1=="wait"){
                return {"wait",-1};
            }else{
                cout<<"excute error"<<endl;
                exit(-1);
                return {"error",-1};
            }
        }
    }
    return {"",-1};
}

void Process::display(){
    //展示内存情况
    mem->displayPhyBlock();
    mem->displayVirtualBlock(*this);
    displayBlockTable();
}

void Process::fork(Process* par){
    pid=par->id;
    allocid=par->allocid;
    virtualTable=par->virtualTable;//继承虚函数表
    virtualId=par->virtualId;
    for(auto it:allocid){
        for(auto itt:mem->alloc[it]){
            rw[itt]=0;//继承为读权限
        }
    }
}

void Process::processPrint(int counter){
    cout<<"[cycle #"<<counter<<"]"<<endl;
    cout<<"1.mode: user"<<endl;
    cout<<"2.comand: "<<code[line]<<endl;
    cout<<"3.running: "<<id<<"("<<name<<","<<pid<<")"<<endl;
    display();
}

bool Process::isDead(){
    return state==5;
}

void Process::destroyStorage(){
    for(int i=0;i<VBLOCKNUM;i++){
        if(rw[i]==1){
            mem->destroyVirBlock(virtualTable[i].phy_id);
        }
    }
}