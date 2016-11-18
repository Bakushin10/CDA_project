#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stdlib.h>     /* atoi */
#include <string.h>
#include <math.h>       /* pow */
#include <iostream>
using namespace std;

class ArrayList{
    public:
        ArrayList();
        ~ArrayList();
        void createList(string opcode,int base,int rt,int offset,int dest,int src1,int src2, int immi,int sa, ArrayList* lists,int i);
        void init(int,ArrayList*);
        void showVariblesInArray(ArrayList*lists);

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

