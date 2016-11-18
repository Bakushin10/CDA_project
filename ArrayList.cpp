#include "ArrayList.h"

ArrayList::ArrayList(){

}

ArrayList::~ArrayList(){
    //dtor
}

void ArrayList::init(int arraySize,ArrayList* lists){

    for(int i =0;i<arraySize;i++){
        lists[i].address = 0;
        lists[i].base = 0;
        lists[i].rt = 0;
        lists[i].offset = 0;
        lists[i].dest = 0;
        lists[i].src1 = 0;
        lists[i].src2 = 0;
        lists[i].immi = 0;
        lists[i].sa = 0;
    }

}


void ArrayList::showVariblesInArray(ArrayList*lists){

    std::cout<<"address\topcode\tbase\trt\toffset\tdest\tsrc1\tsrc2\timmi\tsa\n";
    for(int i = 0;i<= 19;i++){
        std::cout<<lists[i].address<<"\t"<<lists[i].opcode<<"\t"<<lists[i].base<<"\t"<<lists[i].rt<<"\t"<< lists[i].offset<<"\t"<<lists[i].dest<<"\t"<<lists[i].src1<<"\t"<<lists[i].src2
            <<"\t"<<lists[i].immi<<"\t"<<lists[i].sa<<"\n";
    }

}
void ArrayList::createList(string opcode,int base,int rt,int offset,int dest,int src1,int src2, int immi,int sa, ArrayList* lists,int i){
    
    int addr = i;
    i  = (i-64)/4;
    lists[i].address = addr;
    lists[i].opcode = opcode;
    

    if(base != 0)
        lists[i].base = base;
    if(rt != 0)
        lists[i].rt = rt;
    if(offset != 0)
        lists[i].offset = offset;
    if(dest != 0)
        lists[i].dest = dest;
    if(src1 != 0)
        lists[i].src1 = src1;
    if(src2 != 0)
        lists[i].src2 = src2;
    if(immi != 0)
        lists[i].immi = immi;
    if(sa != 0)
        lists[i].sa = sa;
}

