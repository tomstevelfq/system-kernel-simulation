#include"process.h"

Process::Process(Memory* m){
    rw=vector<int>(1000,2);//初始化都没有权限
    mem=m;
}

void Process::displayBlockTable(){
    for(int i=0;i<VBLOCKNUM;i++){
        if(rw[i]==2){
            cout<<"- ";
        }else{
            cout<<i<<" ";
        }
    }
    cout<<endl;
    for(int i=0;i<VBLOCKNUM;i++){
        if(rw[i]==0){
            cout<<"R ";
        }else if(rw[i]==1){
            cout<<"W ";
        }else{
            cout<<"- ";
        }
    }
    cout<<endl;
}

string Process::excute(){//执行完成返回false
    while(line<code.size()){//循环执行指令
        display();//展示内存情况
        stringstream ss(code[line++]);
        string cmd1;
        ss>>cmd1;
        if(cmd1=="wait"){
            cout<<"wait"<<endl;
        }else if(cmd1=="exit"){
            if(pid==-1){
                break;
            }
        }else{
            int blockid;
            int num;
            string program;
            if(cmd1=="memory_read"){
                ss>>blockid;
                if(rw[blockid]!=2&&mem->virtualTable[blockid]!=-1){
                    cout<<"read ok"<<endl;
                }else{
                    int phy_id=mem->getOneBlock();
                    mem->setProcessId(phy_id,id);
                    mem->loadVirBlock(blockid,phy_id);
                    cout<<"分配读物理内存"<<endl;
                    rw[blockid]=1;
                }
            }else if(cmd1=="memory_write"){
                ss>>blockid;
                if(rw[blockid]==0){
                    cout<<"write ok"<<endl;
                }else{
                    int phy_id=mem->getOneBlock();
                    mem->setProcessId(phy_id,id);
                    mem->loadVirBlock(blockid,phy_id);
                    cout<<"分配写物理内存"<<endl;
                    rw[blockid]=1;
                }
            }else if(cmd1=="memory_allocate"){
                ss>>num;
                mem->memory_alloc(num,id,*this);
                cout<<"分配内存"<<endl;
            }else if(cmd1=="memory_release"){
                ss>>num;
                mem->memory_release(num);
                cout<<"释放内存"<<endl;
            }else if(cmd1=="memory_release"){
                ss>>num;
                mem->memory_release(num);
                cout<<"释放内存"<<endl;
            }else if(cmd1=="fork_and_exec"){
                ss>>program;
                cout<<"调用程序"<<endl;
                return program;
            }else if(cmd1=="exit"){
                return "";
            }else{
                cout<<"excute error"<<endl;
                exit(-1);
            }
        }
    }
    return "";
}

void Process::display(){
    //展示内存情况
    mem->displayPhyBlock();
    mem->displayVirtualBlock();
    displayBlockTable();
}