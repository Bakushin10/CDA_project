#include "ArrayList.h"
#include <math.h>       /* modf */
#include "category_1.h"
#include "category_2.h"
#include "category_3.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ios;

#include<fstream>
using std::ifstream;
using std::ofstream;

ArrayList::ArrayList(){

}

ArrayList::~ArrayList(){
    //dtor
}

void ArrayList::init(int arraySize,ArrayList* lists){

    for(int i =0;i<arraySize;i++){
        lists[i].address = 0;
        lists[i].base = 0;
        lists[i].rt = 0;
        lists[i].offset = 0;
        lists[i].dest = 0;
        lists[i].src1 = 0;
        lists[i].src2 = 0;
        lists[i].immi = 0;
        lists[i].sa = 0;
    }

}

void ArrayList::showVariblesInArray(ArrayList*lists){

    std::cout<<"address\topcode\tbase\trt\toffset\tdest\tsrc1\tsrc2\timmi\tsa\n";
    for(int i = 0;i<= 19;i++){
        std::cout<<lists[i].address<<"\t"<<lists[i].opcode<<"\t"<<lists[i].base<<"\t"<<lists[i].rt<<"\t"<< lists[i].offset<<"\t"<<lists[i].dest<<"\t"<<lists[i].src1<<"\t"<<lists[i].src2
            <<"\t"<<lists[i].immi<<"\t"<<lists[i].sa<<"\n";
    }

}
void ArrayList::createList(string opcode,int base,int rt,int offset,int dest,int src1,int src2, int immi,int sa, ArrayList* lists,int i){

    int addr = i;
    i  = (i-64)/4;
    lists[i].address = addr;
    lists[i].opcode = opcode;

    if(base != 0)
        lists[i].base = base;
    if(rt != 0)
        lists[i].rt = rt;
    if(offset != 0)
        lists[i].offset = offset;
    if(dest != 0)
        lists[i].dest = dest;
    if(src1 != 0)
        lists[i].src1 = src1;
    if(src2 != 0)
        lists[i].src2 = src2;
    if(immi != 0)
        lists[i].immi = immi;
    if(sa != 0)
        lists[i].sa = sa;
}


void ArrayList::executeInstruction(simulation* sim,ArrayList* lists,int adder,ofstream& myfile_sim){

    int const register_size = 32;
    int* registers = new int[register_size];
    for(int i =0;i<register_size;i++)
        registers[i] = 0;

    int array_index = 0;
    int current_address = adder;



    while(lists[array_index].opcode.compare("BREAK") !=0 ){
        myfile_sim<<"\n-----------------";
        myfile_sim<<"\nCycle "<<sim->cycle<<":       "<<current_address<<"   ";
        displayInstruction(lists,array_index,myfile_sim);
        array_index = doExecution(sim,lists,array_index,registers,adder);
        showRegister(registers,register_size,myfile_sim);
        sim->showData(myfile_sim);
        current_address = adder+array_index*4;///get next addrest
    }

    if(lists[array_index].opcode.compare("BREAK") ==0){
        myfile_sim<<"\n-----------------";
        myfile_sim<<"\nCycle "<<sim->cycle<<":       "<<current_address<<"   "<<lists[array_index].opcode<<"\n";
        showRegister(registers,register_size,myfile_sim	);
        sim->showData(myfile_sim);
    }

}

void ArrayList::displayInstruction(ArrayList* lists,int array_index,ofstream& myfile_sim){

        ///category 1
        if(lists[array_index].opcode.compare("NOP")==0){
            myfile_sim<<"NOP"<<"\n";
        }
        if(lists[array_index].opcode.compare("J")==0){
            myfile_sim<<lists[array_index].opcode<<" #"<<lists[array_index].offset*4<<"\n";
        }
        if(lists[array_index].opcode.compare("BEQ")==0 || lists[array_index].opcode.compare("BNE")==0){
            myfile_sim<<lists[array_index].opcode<<" R"<<lists[array_index].base<<", R"<<lists[array_index].rt<<", #"<<lists[array_index].offset<<"\n";
        }
        if(lists[array_index].opcode.compare("BGTZ")==0){
            myfile_sim<<lists[array_index].opcode<<" R"<<lists[array_index].base<<", #"<<lists[array_index].offset<<"\n";
        }
        if(lists[array_index].opcode.compare("SW")==0 || lists[array_index].opcode.compare("LW")==0){
            myfile_sim<<lists[array_index].opcode<<" R"<<lists[array_index].rt<<", "<<lists[array_index].offset<<"(R"<<lists[array_index].base<<")\n";
        }

        ///category 2
        if(lists[array_index].opcode.compare("XOR")==0 || lists[array_index].opcode.compare("MUL")==0 || lists[array_index].opcode.compare("ADD")==0 ||
          lists[array_index].opcode.compare("SUB")==0 || lists[array_index].opcode.compare("AND")==0 || lists[array_index].opcode.compare("OR")==0 ||
          lists[array_index].opcode.compare("ADDU")==0 || lists[array_index].opcode.compare("SUBU")==0){
            myfile_sim<<lists[array_index].opcode<<" R"<<lists[array_index].dest<<", R"<<lists[array_index].src1<<", R"<<lists[array_index].src2<<"\n";
        }

        ///category 3
        if(lists[array_index].opcode.compare("SRL")==0  || lists[array_index].opcode.compare("SRA") == 0 || lists[array_index].opcode.compare("SLL") == 0  ){
        myfile_sim<<lists[array_index].opcode<<" R"<<lists[array_index].dest<<", R"<<lists[array_index].src1<<", #"<<lists[array_index].sa<<"\n";
        }
        if(lists[array_index].opcode.compare("ORI")==0 || lists[array_index].opcode.compare("XORI")==0 || lists[array_index].opcode.compare("ADDI")==0 ||
          lists[array_index].opcode.compare("SUBI")==0 || lists[array_index].opcode.compare("ANDI")==0 ){
            myfile_sim<<lists[array_index].opcode<<" R"<<lists[array_index].dest<<", R"<<lists[array_index].src1<<", #"<<lists[array_index].immi<<"\n";
        }
}

int ArrayList::doExecution(simulation* sim,ArrayList* lists,int array_index,int* registers,int adder){

    int dataAt;///location of data address
    int const array_size = 32;

    ///category 1
    if(lists[array_index].opcode.compare("LW") == 0 ){
        dataAt = lists[array_index].offset+ registers[lists[array_index].base];
        dataAt = (dataAt-sim->data_starting_address)/4;///this 144 needs to be fixed
        registers[lists[array_index].rt] =  sim->getData(dataAt);
    }
    if(lists[array_index].opcode.compare("SW") == 0 ){
        dataAt = (lists[array_index].offset+ registers[lists[array_index].base] - sim->data_starting_address)/4;
        sim->data[dataAt] = registers[lists[array_index].rt];
    }

    if(lists[array_index].opcode.compare("BGTZ") == 0){
        if(registers[lists[array_index].base] > 0 ){
            return array_index+1 + lists[array_index].offset;
        }
    }

    if(lists[array_index].opcode.compare("BNQ") == 0){
        if(registers[lists[array_index].base] != registers[lists[array_index].rt]){
            return array_index+1+lists[array_index].offset;
        }
    }

    if(lists[array_index].opcode.compare("BEQ") == 0){
        if(registers[lists[array_index].base] == registers[lists[array_index].rt]){
            return array_index+1+lists[array_index].offset;
        }
    }

    if(lists[array_index].opcode.compare("J") == 0){

      //  myfile_sim<<"Jumo to "<<((lists[array_index].offset*4) - adder)/4;;
        return ((lists[array_index].offset*4) - adder)/4;
    }

    ///category 2
    if(lists[array_index].opcode.compare("MUL") == 0 ){
        registers[lists[array_index].dest] = registers[lists[array_index].src1]*registers[lists[array_index].src2];
    }
    if(lists[array_index].opcode.compare("XOR") == 0){
        int*a = decimalToBinary(lists,array_index,lists[array_index].src1,array_size);
        int*b = decimalToBinary(lists,array_index,lists[array_index].src2,array_size);
        int result = XORI(a,b,array_size);
        lists[array_index].dest = result;
    }
    if(lists[array_index].opcode.compare("OR") == 0){
        int*a = decimalToBinary(lists,array_index,lists[array_index].src1,array_size);
        int*b = decimalToBinary(lists,array_index,lists[array_index].src2,array_size);
        int result = ORI(a,b,array_size);
        lists[array_index].dest = result;
    }
    if(lists[array_index].opcode.compare("ADD") == 0){
        int data = registers[lists[array_index].src1] +registers[lists[array_index].src2];
        int*a = decimalToBinary(lists,array_index,lists[array_index].src1,array_size);
        int*b = decimalToBinary(lists,array_index,lists[array_index].src2,array_size);
    /*
        if(checkOverflow(a,b)){
            myfile_sim<<"overflow\n";
            break;
        }
    */
        registers[lists[array_index].dest] = data;
    }

    if(lists[array_index].opcode.compare("SUB") == 0){
        int data = registers[lists[array_index].src1] - registers[lists[array_index].src2];
        registers[lists[array_index].dest] = data;
    }
    if(lists[array_index].opcode.compare("AND") == 0){
        int*a = decimalToBinary(lists,array_index,lists[array_index].src1,array_size);
        int*b = decimalToBinary(lists,array_index,lists[array_index].src2,array_size);
        int result = AND(a,b,array_size);
        lists[array_index].dest = result;
    }
    if(lists[array_index].opcode.compare("ADDU") == 0){
        int data = registers[lists[array_index].src1] +registers[lists[array_index].src2];
        registers[lists[array_index].dest] = data;
    }
    if(lists[array_index].opcode.compare("SUBU") == 0){
        int data = registers[lists[array_index].src1] - registers[lists[array_index].src2];
        registers[lists[array_index].dest] = data;
    }
    ///category 3

    if(lists[array_index].opcode.compare("ADDI") == 0 ){
       dataAt = registers[lists[array_index].src1] + lists[array_index].immi;
        registers[lists[array_index].dest] =  dataAt;
    }

    if(lists[array_index].opcode.compare("SUBI") == 0 ){
        dataAt = registers[lists[array_index].src1] - lists[array_index].immi ;
        registers[lists[array_index].dest] =  dataAt;
    }

    if(lists[array_index].opcode.compare("SLL") == 0 ){
        int temp = registers[lists[array_index].src1];
        for(int i=0;i<lists[array_index].sa;i++)
            temp = temp*2;
        registers[lists[array_index].dest] = temp;
    }
    ///these two(SRL SRA) need to be fixed
    if(lists[array_index].opcode.compare("SRL") == 0 ){
        double temp = registers[lists[array_index].src1];
        double intpart,fractpart;
        for(int i =0;i<lists[array_index].sa;i++)
            temp = temp/2;
        fractpart = modf (temp , &intpart);

        if(fractpart != 0){
            if(temp > 0)
                temp++;
            else
                temp = temp -1;
        }
        registers[lists[array_index].dest] =  temp;
    }

    if(lists[array_index].opcode.compare("SRA") == 0 ){
        double temp = registers[lists[array_index].src1];
        double intpart,fractpart;
        int* a = decimalToBinary(lists,array_index,registers[lists[array_index].src1],array_size);
        int result = SRA(a,lists[array_index].sa,array_size);
        registers[lists[array_index].dest] = result;
    }

    if(lists[array_index].opcode.compare("XORI") == 0){
        int* a = decimalToBinary(lists,array_index,lists[array_index].immi,array_size);
        int* b = decimalToBinary(lists,array_index,registers[lists[array_index].src1],array_size);
        int result = XORI(a,b,array_size);
        registers[lists[array_index].dest] = result;
    }

    if(lists[array_index].opcode.compare("ORI") == 0){
        int* a = decimalToBinary(lists,array_index,lists[array_index].immi,array_size);
        int* b = decimalToBinary(lists,array_index,registers[lists[array_index].src1],array_size);
        int result = ORI(a,b,array_size);
    }
    return array_index+1;///if not jump

}


int ArrayList::AND(int*a,int*b,int array_size){
    int* xori_a = new int[array_size];
    int result = 0;
    int j = array_size-1;

    ///find the XOR of two binary string
    for(int i =0;i<array_size;i++){
        if((a[i] == 1 && b[i] ==1)){
            xori_a[i] = 1;
        }else
           xori_a[i] = 0;
    }

    for(int i =0;i<array_size;i++){
        if(xori_a[i] == 1){
            result = result + pow(2,j-i);
        }
    }

    return result;
}

int ArrayList::SRA(int*registers,int shift,int array_size){

    int j =0;

    while(j<shift){
        int* a = new int[array_size];

        for(int i = 0;i<array_size;i++){
            if(i == 0){
                a[i] = registers[i];
            }
            else{
                a[i] = registers[i-1];
            }
        }

        for(int i = 0;i<array_size;i++){
            registers[i] = a[i];
        }

        j++;
    }

    int sum = 0;
    for(int n =0;n<array_size;n++){
        if(registers[n] == 1){
            int b = array_size-1 - n;
            sum = sum+pow(2,b);
        }
    }

    return sum;
}

int ArrayList::ORI(int*a,int*b,int array_size){
    int* xori_a = new int[array_size];
    int result = 0;
    int j = array_size-1;

    ///find the XOR of two binary string
    for(int i =0;i<array_size;i++){
        if((a[i] == 1 || b[i] ==1)){
            xori_a[i] = 1;
        }else
           xori_a[i] = 0;
    }

    for(int i =0;i<array_size;i++){
        if(xori_a[i] == 1){
            result = result + pow(2,j-i);
        }
    }
    ///if its nagative
    if(xori_a[0] == 1)
        result = result *-1;

    return result;
}

int ArrayList::XORI(int*a,int*b,int array_size){
    int* xori_a = new int[array_size];
    int result = 0;
    int j = array_size-1;

    ///find the XOR of two binary string
    for(int i =0;i<array_size;i++){
        if((a[i] == 0 &&b[i] ==1) || (a[i] == 1 &&b[i] ==0)){
            xori_a[i] = 1;
        }else
           xori_a[i] = 0;
    }

    if(xori_a[0] == 0){
        for(int i =0;i<array_size;i++){
            if(xori_a[i] == 1){
                result = result + pow(2,j-i);
            }
        }
    
    }else{
        for(int i =0;i<array_size;i++){
            if(xori_a[i] == 0){
                result = result + pow(2,j-i);
            }
        }
        result++;
        result = result*-1;
    }
/*
    for(int i =0;i<array_size;i++){
        myfile_sim<<a[i];
    }
    

/*
    myfile_sim<<"\n";
        for(int i =0;i<array_size;i++){
        myfile_sim<<b[i];
    }
    myfile_sim<<"\n";
    for(int i =0;i<array_size;i++){
        myfile_sim<<xori_a[i];
    }
    myfile_sim<<"\n";
    ///if its nagative
*/

    return result;
}

///convert
int* ArrayList::decimalToBinary(ArrayList* lists,int array_index,int num,int array_size){
    int* temp_immi = new int[array_size];
    int* reverse_immi = new int[array_size];
    int j = array_size-1;

    ///if the nubmer is negative
    if(num < 0 ) {
                bool flag = true;
        for(int i=0; i<array_size; i++) {
            if(num <= 1 && flag) {
                temp_immi[i] = 1;
                flag = false;
            } else if(num%2 != 0) {
                temp_immi[i] = 1;
            } else
                temp_immi[i] = 0;
            num = num/2;
        }

        for(int i =0; i<array_size; i++) {
            reverse_immi[i] = temp_immi[j];
            j--;
        }
        ///complement of 1
        for(int i =0; i<array_size; i++){
            if(reverse_immi[i] == 0){
                reverse_immi[i] = 1;
            }
            else{
                reverse_immi[i] = 0;
            }
                
        }
        
        ///if the least sig bit is 0, just add 1
        if(reverse_immi[array_size-1] == 0){
            reverse_immi[array_size-1] = 1;
        }else{
            int i = 1;
            while(reverse_immi[array_size-i] == 0){
                reverse_immi[array_size-i] = 0;
                i++;
            }
                reverse_immi[array_size-i] = 1;
        }

    }
    else{///when the number is positive
        bool flag = true;
        for(int i=0; i<array_size; i++) {
            if(num <= 1 && flag) {
                temp_immi[i] = 1;
                flag = false;
            } else if(num%2 != 0) {
                temp_immi[i] = 1;
            } else
                temp_immi[i] = 0;
            num = num/2;
        }

        for(int i =0; i<array_size; i++) {
            reverse_immi[i] = temp_immi[j];
            j--;
        }
    }
    return reverse_immi;
}

void ArrayList::showRegister(int* reg,int regSize,ofstream& myfile_sim){

    myfile_sim<<"\nRegisters";
    for(int i=0;i<regSize;i++){
        if((i%8 == 0&& i>=8) || i == 0){
	    if(i<10)
		myfile_sim<<"\nR0"<<i<<":  ";
	    else
		myfile_sim<<"\nR"<<i<<":  ";
	}
        myfile_sim<<reg[i]<<"    ";

    }
}

