#include "category_1.h"
#include <stdlib.h>     /* atoi */
#include <string.h>
#include <math.h>       /* pow */
#include <iostream>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;

#include<fstream>
using std::ifstream;
using std::ofstream;
using namespace std;

category_1::category_1(){
    this->opCode = new char[3];
    this->base = new char[5];
    this->rt = new char[5];
    this->offset = new char[16];
}
category_1::~category_1(){
    delete opCode;
    delete base;
    delete rt;
    delete offset;
}


bool category_1::getCode(char* inst,int inst_size,int address,simulation* sim, int writeReg,ArrayList* lists,ofstream& mysavefile_inst){

    int op_count = 0;
    int base_count = 0;
    int rt_count = 0;
    int offset_count = 0;

    ///this for loops will assign
    for(int i = 0;i<inst_size;i++){
        if(i>=16){
            offset[offset_count] = inst[i];
            offset_count++;
        }
        if(i>=11 && i<=15){
            rt[rt_count] = inst[i];
            rt_count++;
        }
        if(i>=6 && i<=10){
            base[base_count] = inst[i];
            base_count++;
        }
        if(i>=3 && i<=5){
            opCode[op_count] = inst[i];
            op_count++;
        }
    }

    string opcode_result = getOpcode(opCode);
    int base_total = getBase(base);
    int rt_result = getBase(rt);///same as get base function
    int offset_result = getOffset(offset);
     //mysavefile_inst<<"inst    : "<<inst<<"\n";
   // mysavefile_inst<<"opcode  : "<<opCode<<" : "<<opcode_result<<"\n";
    //mysavefile_inst<<"base    : "<<base<<" : "<<base_total<<"\n";
    //mysavefile_inst<<"rt      : "<<rt<<" : "<<rt_result<<"\n";
   // mysavefile_inst<<"offset  : "<<offset_result<<"\n\n";
    ///getOpcode

    if(writeReg == -2){
	for(int i =0;i<32;i++)
	     mysavefile_inst<<inst[i];
	     mysavefile_inst<<"\t";
        lists->createList(opcode_result,base_total,rt_result,offset_result,0,0,0,0,0,lists,address);
        show_category1(opcode_result,base_total,rt_result,offset_result,address,mysavefile_inst);
    }

    if(opcode_result.compare("BREAK") == 0)
        return true;

        return false;

}

void category_1::show_category1(string opcode_result,int base_result, int rt_result,int offset_result,int address,ofstream& mysavefile_inst){

        int const nextAdder = 4;
        mysavefile_inst<<address<<"\t";///show current address

        switch(atoi(this->opCode)){
        case 0 :{
            mysavefile_inst<<"NOP"<<"\n";
            break;
        }
        case 1:{
            int jumpTo = nextAdder*offset_result;
            mysavefile_inst<<opcode_result<<" #"<<jumpTo<<"\n";
            break;
        }
        case 10:{
            mysavefile_inst<<opcode_result<<" R"<<base_result<<", R"<<rt_result<<", #"<<offset_result<<"\n";
            break;
        }
        case 11:{
            mysavefile_inst<<opcode_result<<" R"<<base_result<<", R"<<rt_result<<", #"<<offset_result<<"\n";
            break;
        }
        case 100:{
            mysavefile_inst<<opcode_result<<" R"<<base_result<<", #"<<offset_result<<"\n";
            break;
        }
        case 101:{
            mysavefile_inst<<opcode_result<<" R"<<rt_result<<", "<<offset_result<<"(R"<<base_result<<")\n";
            break;
        }
        case 110:{
            mysavefile_inst<<opcode_result<<" R"<<rt_result<<", "<<offset_result<<"(R"<<base_result<<")\n";
            break;
        }
        case 111:{
            mysavefile_inst<<"BREAK\n";
        }

    }


}

int category_1::getOffset(char* offset){
    int const offset_len = 16;
    int sum = 0;

    if(offset[0] == '0'){
        for(int i =0;i<offset_len;i++){
            if(offset[i] == '1'){
                int b =  (offset_len-1) - i;
                sum = sum+pow(2,b);
            }
        }
    }else{
        ///when its negative take a 2's comp
        for(int i =0;i<offset_len;i++){
            if(offset[i] == '0'){
                int b =  (offset_len-1) - i;
                sum = sum+pow(2,b);
            }
        }
        sum++;///2's complement
        sum = sum*-1;
    }

    return sum;
}

int category_1::getBase(char*base){

    ///get the len of the char* base
///    size_t temp_len = strlen(base);
///    int len =  static_cast<int>(temp_len);
    int const len = 5;///size of the base 5 bits
    int sum = 0;

    for(int i=0;i<len;i++){
        if(base[i] == '1'){
            int b =  (len-1) - i;
            sum = sum+pow(2,b);
        }
    }
    return sum;
}

string category_1::getOpcode(char* opcode){

    switch(atoi(opcode)){
        case 0 :{
            return "NOP";
        }
        case 1:{
            return "J";
        }
        case 10:{
            return "BEQ";
        }
        case 11:{
            return "BNE";
        }
        case 100:{
            return "BGTZ";
        }
        case 101:{
            return  "SW";
        }
        case 110:{
            return "LW";
        }
        case 111:{
            return "BREAK";
        }

    }
}///end of getOpcode
