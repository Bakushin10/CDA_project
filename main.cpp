#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atoi */
#include "category_0.h"///for 111 and 000
#include "category_1.h"
#include "category_2.h"
#include "category_3.h"
#include "simulation.h"
#include "ArrayList.h"
using namespace std;

///function prote type
int const inst_size = 32;///instruction size 32 bits
int const category_size = 3;///size of category
bool isEmpty(std::istream& );
void clearArray(char* ,int &j);
char* selectCategory(char*);
int display(ifstream&,int,int,simulation*,ArrayList*);///get the category code and deal with the instruction

int main(int argc,char** argv){

    ifstream myfile,myfile2,myfile3;
    int address = 64;///by default, the program always starts from address 64
    int regSize = 0;
    int arraySize = 0;
    myfile.open(argv[1]);///to get tche number of registers
    myfile2.open(argv[1]);///to obtain the contents of registers
    myfile3.open(argv[1]);

    simulation* sim = new simulation();
    ArrayList* lists;

    if(!isEmpty(myfile))
        regSize = display(myfile,address,0,sim,lists);
        myfile.close();

    sim->setReg(regSize);
    std::cout<<"reg size = "<<regSize<<std::endl;
    if(!isEmpty(myfile2))
        arraySize = display(myfile2,address,-1,sim,lists)+1;
    std::cout<<"array size = "<<arraySize<<std::endl;

    lists = new ArrayList[arraySize];///create the list
    lists->init(arraySize,lists);///set all variables to 0

    if(!isEmpty(myfile3))
        display(myfile3,address,-2,sim,lists);
        
     lists->showVariblesInArray(lists);

    myfile.close();
    myfile2.close();
    myfile3.close();
    std::cout<<"\nEnd "<<std::endl;
    return 0;
}

int display(ifstream& myfile,int address,int regSize,simulation* sim,ArrayList* lists){

    int i = 0;
    char a;
    char* inst = new char[inst_size];
    category_1* cate_1 = new category_1();
    category_2* cate_2 = new category_2();
    category_3* cate_3 = new category_3();
    category_0* cate_0 = new category_0();
    bool reg_increment = false;
    bool isArraySize = false;
    if(regSize == -1)
        isArraySize = true;



    while(!myfile.eof()){

        if(i == inst_size){
            char* category = selectCategory(inst);
            //std::cout<<"atoi : "<<atoi(category)<<"\n";
            switch(atoi(category)){
                case 1:{
                    if(cate_1->getCode(inst,inst_size,address,sim,regSize,lists) && regSize != -2)///for display to work
                        reg_increment = true;
                    break;
                }
                case 10:{///atoi recoganizes 010 as 10
                    cate_2->getCode(inst,inst_size,address,sim,regSize,lists);
                    break;
                }
                case 100:{///when category is 100
                    cate_3->getCode(inst,inst_size,address,sim,regSize,lists);
                    break;
                }
                case 0:{///when category is 000
                    cate_0->getCode(inst,inst_size,address,sim,regSize,isArraySize);
                    break;
                }
                case 111:{///when category is 111
                    cate_0->getCode(inst,inst_size,address,sim,regSize,isArraySize);
                    break;
                }
            }
            clearArray(inst,i);
            address = address+4;///update address
        }


        if(reg_increment && !isArraySize)
            regSize++;///size of the register
        if(!reg_increment && isArraySize)
            regSize++;///size of the instructions

        myfile>>a;
        inst[i] = a;
        i++;
    }

    if(regSize == -2){
        sim->showRegister();
        std::cout<<"\n";
	}
    ///free up memories
    cate_1->~category_1();
    cate_2->~category_2();
    cate_3->~category_3();
    cate_0->~category_0();

    return regSize/32;
}

char* selectCategory(char* inst){

    char* category = new char[category_size];
    for(int i =0;i<3;i++){
        category[i] = inst[i];
    }
    ///returns the category code
   return category;
}

void clearArray(char* arr,int &j){

    for(int i =0;i<inst_size;i++){
        arr[i] = '\0';
    }
     j = 0;
}
bool isEmpty(std::istream& pFile){
    ///checks if the file is empty
    return pFile.peek() == std::ifstream::traits_type::eof();
}

