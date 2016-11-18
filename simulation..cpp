#include "simulation.h"

simulation::simulation(){

}

simulation::~simulation()
{
    //dtor
}

void simulation::setReg(int regSize){
    this->registers = new int[regSize];
}

