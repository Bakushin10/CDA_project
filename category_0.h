#ifndef CATEGORY_0_H
#define CATEGORY_0_H
#include "simulation.h"

class category_0{
    public:
        category_0();
         ~category_0();
         int convertToDecimal_16bits(char* inst);
         void show_category_0(int num, int address);
         void getCode(char* inst,int inst_size,int address,simulation*,int ,bool);


    protected:

    private:
        static int const len = 16;///the len of  bits for deciamal
        char* immi;
};

#endif // CATEGORY_0_H

