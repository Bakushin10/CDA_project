#include "category_0.h"
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <math.h>       /* pow */
#include <iostream>
using std::cin;
using std::endl;
using std::ios;

#include<fstream>
using std::ifstream;
using std::ofstream;
using namespace std;

category_0::category_0(){
    this->immi = new char[this->len];
}

category_0::~category_0(){
    delete immi;
}

void category_0::getCode(char* inst,int inst_size,int address,simulation* sim,int regSize,bool writeReg,ofstream& mysavefile_inst){

    int immi_count = 0;
    for(int i = 0;i<inst_size;i++){
        if(i>=16){
            immi[immi_count] = inst[i];
            immi_count++;
        }
    }

    int num = convertToDecimal_16bits(inst);

    if(regSize == -2){
	for(int i =0;i<32;i++)
	     mysavefile_inst<<inst[i];
	     mysavefile_inst<<"\t";
        show_category_0(num,address,mysavefile_inst);
      }
    if(writeReg)
        sim->updateRegisters(num);
}

void category_0::show_category_0(int num, int address,ofstream& mysavefile_inst){
    mysavefile_inst<<address<<"\t"<<num<<"\n";
}

int category_0::convertToDecimal_16bits(char* inst){

    int sum = 0;

    if(inst[0] == '1'){
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
