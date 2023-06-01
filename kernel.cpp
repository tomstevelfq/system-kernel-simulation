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

}

void Kernel::releaseSize(int num,Process& proc){

}