#ifndef CATEGORY_2_H
#define CATEGORY_2_H
#include <iostream>
#include "simulation.h"
#include "ArrayList.h"
using namespace std;

class category_2{
    public:
        category_2();
        ~category_2();
        string getOpcode(char*);
        void getCode(char* ,int,int,simulation*,int,ArrayList*,ofstream&);
        int convertToDecimal(char*);
        void show_category2(string, int,int,int,int,ofstream&);

    private:
        static int const r_len = 5;///len of dest, src1 and src2
        char* dest;
        char* src1;
        char* src2;
        char* opCode;
	char name;
};

#endif // CATEGORY_2_H
