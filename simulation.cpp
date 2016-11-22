#include "simulation.h"
#include <iostream>
#include <stdlib.h>     /* atoi */
#include <math.h>       /* pow */
using namespace std;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;

#include<fstream>
using std::ifstream;
using std::ofstream;

simulation::simulation(){

}

simulation::~simulation(){
   delete data;
}

void simulation::setReg(int dataSize){
    this->data = new int[dataSize];
    this->reg_cnt = 0;
    this->dataSize = dataSize;
    this->cycle = 1;///starting at 1
}

void simulation::setdata_starting_address(int num,int address){
	this->data_starting_address = address+num*4;
}

void simulation::updateRegisters(int val){
        data[reg_cnt] = val;
        reg_cnt++;
}

int simulation::getData(int dataAt){
    return this->data[dataAt];
}

void simulation::showData(ofstream& myfile_sim){

    myfile_sim<<"\n\nData";

    int data_incre = data_starting_address;
    for(int i =0; i<this->dataSize; i++) {
        if(i%8 == 0)
            myfile_sim<<"\n"<<data_incre<<":	";
        myfile_sim<<data[i]<<"	";
        data_incre = data_incre+4;
    }
    this->cycle++;
    myfile_sim<<"\n";
}
