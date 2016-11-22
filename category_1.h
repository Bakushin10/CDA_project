#ifndef CATEGORY_1_H
#define CATEGORY_1_H
#include <iostream>
#include "simulation.h"
#include "ArrayList.h"
using namespace std;


class category_1{
    public:
        category_1();
        ~category_1();
        bool getCode(char*,int,int,simulation* sim,int,ArrayList*,ofstream&);
        string getOpcode(char* opcode);
        int getBase(char*base);
        int getOffset(char* offset);
        void show_category1(string ,int,int,int,int,ofstream&);

    private:
        char* opCode;
        char* base;
        char* rt;
        char* offset;
};

#endif // CATEGORY_1_H
