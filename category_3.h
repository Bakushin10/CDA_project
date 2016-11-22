#ifndef CATEGORY_3_H
#define CATEGORY_3_H
#include <iostream>
#include "simulation.h"
#include "ArrayList.h"
using namespace std;

class category_3{
    public:
        category_3();
        ~category_3();
        int convertToDecimal(char* arr);
        void getCode(char*,int,int,simulation*,int,ArrayList*,ofstream&);
        string getOpcode(char*);
        int convertToDecimal_16bits(string);
        void show_category3(string,int,int,int,int,int,ofstream&);

    private:
        static int const r_len = 5;
        char* dest;
        char* src1;
        char* immi;
        char* opCode;
        char* sa;
};

#endif // CATEGORY_3_H
