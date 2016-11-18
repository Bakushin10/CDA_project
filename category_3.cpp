#include "category_3.h"
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <math.h>       /* pow */
#include <string>
using namespace std;


category_3::category_3(){
    this->dest = new char[5];
    this->src1 = new char[5];
    this->opCode = new char[3];
    this->immi = new char[16];
    this->sa = new char[5];
}

category_3::~category_3(){
    delete dest;
    delete src1;
    delete immi;
    delete opCode;
    delete sa;
}

void category_3::getCode(char* inst,int inst_size,int address,simulation* sim, int writeReg,ArrayList* lists){

    int dest_count = 0;
    int src1_count = 0;
    int immi_count =0;
    int opCode_count = 0;
    int sa_count = 0;

    for(int i = 0;i<inst_size;i++){
        if(i>=27){
            this->sa[sa_count] =  inst[i];
            sa_count++;
        }
        if(i>=16){
            immi[immi_count] = inst[i];
            immi_count++;
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
    int immi_result = convertToDecimal_16bits(opcode_result);
    int sa_result = convertToDecimal(this->sa);

    if(writeReg == -2){
        lists->createList(opcode_result,0,0,0,dest_result,src1_result,0,immi_result,sa_result,lists,address);
        show_category3(opcode_result,dest_result,src1_result,immi_result,address,sa_result);
    }
}

void category_3::show_category3(string opcode_result, int dest_result,int src1_result,int immi_result,int address,int sa_result){
    std::cout<<address<<"\t";

    if(opcode_result.compare("SRL")==0  || opcode_result.compare("SRA") == 0 || opcode_result.compare("SLL") == 0  ){
        std::cout<<opcode_result<<" R"<<dest_result<<", R"<<src1_result<<", #"<<sa_result<<"\n";
    }else
        std::cout<<opcode_result<<" R"<<dest_result<<", R"<<src1_result<<", #"<<immi_result<<"\n";

}

int category_3::convertToDecimal_16bits(string opcode_result){

    int sum = 0;
    int const len = 16;
    bool isXORI = true;

    if(opcode_result.compare("XORI") == 0)
        isXORI = false;

    if(immi[0] == '1'&& isXORI){
        for(int i =0;i<len;i++){
            if(immi[i] == '0'){
                int a = len - 1 -i;
                sum = sum + pow(2,a);
            }
        }
        sum = sum+1;
        sum = sum*-1;
    }else{
        for(int i =0;i<len;i++){
            if(immi[i] == '1'){
                int a = len - 1 -i;
                sum = sum + pow(2,a);
            }
        }
    }

    return sum;

}

int category_3::convertToDecimal(char* arr){

    int sum = 0;
    for(int i =0;i<r_len;i++){

        if(arr[i] == '1'){
            int b = r_len-1 - i;
            sum = sum+pow(2,b);
        }
    }
    return sum;
}///end of convertToDeciaml


string category_3::getOpcode(char* opcode){

    switch(atoi(opcode)){
        case 0 :{
            return "ORI";
        }
        case 1:{
            return "XORI";
        }
        case 10:{
            return "ADDI";
        }
        case 11:{
            return "SUBI";
        }
        case 100:{
            return  "ANDI";
        }
        case 101:{
            return "SRL";
        }
        case 110:{
            return "SRA";
        }
        case 111:{
            return "SLL";
        }

    }
}///end of getOpcode



