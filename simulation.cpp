#include "simulation.h"
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <math.h>       /* pow */
using namespace std;

simulation::simulation(){

}

simulation::~simulation(){
   delete registers;
}

void simulation::setReg(int regSize){
    this->registers = new int[regSize];
    this->reg_cnt = 0;
    this->regSize = regSize;
}

void simulation::updateRegisters(int val){
        registers[reg_cnt] = val;
        reg_cnt++;
}

void simulation::showRegister(){

    for(int i =0; i<this->regSize; i++) {
        if(i%8 == 0)
            std::cout<<"\n";
        std::cout<<registers[i]<<"	";
    }
}

