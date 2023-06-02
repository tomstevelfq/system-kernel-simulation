#include"kernel.h"

Kernel::Kernel(Memory* m){
    mem=m;
}

void Kernel::allocRead(int blockid,Process& proc){
    int phy_id=mem->getOneBlock();
    mem->setProcessId(phy_id,proc.id);
    mem->loadVirBlock(blockid,phy_id,proc);
    cout<<"分配读物理内存"<<endl;
    proc.rw[blockid]=1;
}

void Kernel::allocWrite(int blockid,Process& proc){
    int phy_id=mem->getOneBlock();
    mem->setProcessId(phy_id,proc.id);
    mem->loadVirBlock(blockid,phy_id,proc);
    cout<<"分配写物理内存"<<endl;
    proc.rw[blockid]=1;
}

void Kernel::allocSize(int num,Process& proc){
    mem->memory_alloc(num,proc.id,proc);
    cout<<"分配内存"<<endl;
}

void Kernel::releaseSize(int num,Process& proc){
    mem->memory_release(num,proc);
    cout<<"释放内存"<<endl;
}

// void Kernel::boot(Process& proc){
//     state=1;
//     cout<<"boot"<<endl;
//     cout<<"3.running: none"<<endl;
//     proc.mem->displayPhyBlock();
// }

// void Kernel::syscall(){
//     cout<<"syscall"<<endl;
// }

// void Kernel::idle(){
//     cout<<"idle"<<endl;
// }

// void Kernel::schedule(){
//     cout<<"schedule"<<endl;
// }

void Kernel::kernelPrint(int counter,Process& proc,Cycle& cycle){
    cout<<"[cycle #"<<counter<<"]"<<endl;
    cout<<"1.mode: kernel"<<endl;
    cout<<"2.command: ";
    if(state==0){
        state=2;
        cout<<"boot"<<endl;
        cout<<"3.running: none"<<endl;
        proc.mem->displayPhyBlock();
    }else if(state==1){
        state=2;
        cout<<"system call"<<endl;
        cout<<"3.running: none"<<endl;
        proc.mem->displayPhyBlock();
    }else if(state==2){
        cycle.state=0;//回到用户态
        cout<<"schedule"<<endl;
        cout<<"running: "<<proc.id<<"("<<proc.name<<","<<proc.pid<<")"<<endl;
        proc.display();
    }else if(state==3){
        cout<<"idle"<<endl;
    }else if(state==4){
        state=2;
        cout<<"fault"<<endl;
        cout<<"3.running: none"<<endl;
        proc.mem->displayPhyBlock();
    }
}