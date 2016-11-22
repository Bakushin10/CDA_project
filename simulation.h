#ifndef SIMULATION_H
#define SIMULATION_H
#include <iostream>
using namespace std;

class simulation{
    friend class ArrayList;
    public:
        simulation();
        ~simulation();
        void setReg(int);
        void updateRegisters(int);
        void showData(ofstream&);
        int getData(int dataAt);
	void setdata_starting_address(int num,int address);

    protected:

    private:
        int cycle;///keep track of cycle count
        int* data;///32 bits register
        int reg_cnt;
        int dataSize;
        int data_starting_address;

};

#endif // SIMULATION_H
