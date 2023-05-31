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

void Process::excute(){//执行完成返回false
    stringstream ss(code[line++]);
    string cmd1;
    ss>>cmd1;
    if(cmd1=="wait"){

    }else if(cmd1=="exit"){
        if(pid==-1){
            return;
        }
    }else{
        string cmd2;
        ss>>cmd2;
        int blockid;
        if(cmd1=="memory_read"){
            ss>>blockid;
            if(rw[blockid]!=2&&mem->virtualTable[blockid]!=-1){
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
    return;
}