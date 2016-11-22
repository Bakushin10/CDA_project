#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stdlib.h>     /* atoi */
#include <string.h>
#include <math.h>       /* pow */
#include <iostream>
#include "simulation.h"
using namespace std;

class ArrayList{
    public:
        ArrayList();
        ~ArrayList();
        void createList(string,int,int,int,int,int,int, int,int, ArrayList*,int);
        void init(int,ArrayList*);
        void showVariblesInArray(ArrayList*lists);
        void executeInstruction(simulation*,ArrayList*,int,ofstream&);
        void showRegister(int*,int,ofstream&);
        int doExecution(simulation*,ArrayList*,int,int*,int);
        int* decimalToBinary(ArrayList* ,int,int,int);
        int XORI(int*,int*,int);
        int ORI(int*,int*,int);
        void displayInstruction(ArrayList*,int,ofstream&);
        int SRA(int*registers,int shift,int);
        int AND(int*a,int*b,int array_size);
    private:
        string opcode;
        int address;
        int base;///for category 1
        int rt;
        int offset;
        int dest;///for category 2 & 3
        int src1;///for category 2 & 3
        int src2;
        int immi;///for category 3
        int sa;
};

#endif // ARRAYLIST_H
