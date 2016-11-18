#ifndef SIMULATION_H
#define SIMULATION_H


class simulation{
    public:
        simulation();
        ~simulation();
        void setReg(int);
        void updateRegisters(int);
        void showRegister();

    protected:

    private:
        int cycle;///keep track of cycle count
        int* registers;///32 bits register
        int reg_cnt;
        int regSize;

};

#endif // SIMULATION_H

