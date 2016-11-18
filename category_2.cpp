#include "category_2.h"
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <math.h>       /* pow */

using namespace std;

category_2::category_2(){
    this->dest = new char[5];
    this->src1 = new char[5];
    this->src2 = new char[5];
    this->opCode = new char[3];
}

category_2::~category_2(){
    delete dest;
    delete src1;
    delete src2;
    delete opCode;
}

void category_2::getCode(char* inst,int inst_size,int address,simulation* sim, int writeReg,ArrayList* lists){

    int dest_count = 0;
    int src1_count = 0;
    int src2_count = 0;
    int opCode_count = 0;

    for(int i = 0;i<inst_size;i++){
        if(i>=16 && i<=20){
            src2[src2_count] = inst[i];
            src2_count++;
        }
        if(i>=11 && i<=15){
            src1[src1_count] = inst[i];
            src1_count++;
        }
        if(i>=6 && i<=10){
            dest[dest_count] = inst[i];
            dest_count++;
        }
        if(i>=3 && i<=5){
            opCode[opCode_count] = inst[i];
            opCode_count++;
        }
    }

    string opcode_result = getOpcode(opCode);///return the coresponding opCod
    int dest_result = convertToDecimal(this->dest);
    int src1_result = convertToDecimal(this->src1);
    int src2_result = convertToDecimal(this->src2);

    if(writeReg == -2){
        lists->createList(opcode_result,0,0,0,dest_result,src1_result,src2_result,0,0,lists,address);
        show_category2(opcode_result,dest_result,src1_result,src2_result,address);
    }
}

void category_2::show_category2(string opcode_result, int dest_result,int src1_result,int src2_result,int address){
    std::cout<<address<<"\t";
    std::cout<<opcode_result<<" R"<<dest_result<<", R"<<src1_result<<", R"<<src2_result<<"\n";
}

int category_2::convertToDecimal(char* arr){

    int sum = 0;
    for(int i =0;i<r_len;i++){

        if(arr[i] == '1'){
            int b = r_len-1 - i;
            sum = sum+pow(2,b);
        }
    }
    return sum;
}///end of convertToDeciaml


string category_2::getOpcode(char* opcode){

    switch(atoi(opcode)){
        case 0 :{
            return "XOR";
        }
        case 1:{
            return "MUL";
        }
        case 10:{
            return "ADD";
        }
        case 11:{
            return "SUB";
        }
        case 100:{
            return "AND";
        }
        case 101:{
            return  "OR";
        }
        case 110:{
            return "ADDU";
        }
        case 111:{
            return "SUBU";
        }

    }
}///end of getOpcode

