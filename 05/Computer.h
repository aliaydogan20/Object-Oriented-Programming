/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.h
 * Author: alico
 *
 * Created on 08 Kasım 2016 Salı, 18:49
 */
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"


#ifndef COMPUTER_H
#define COMPUTER_H

class Computer
{
    public:
    
    Computer(int option_)
    {
        option=option_;
        
    }
    Computer(CPU cpu_,CPUProgram cpuprog_,Memory mem_,int option_)
    {
        cpuprog=cpuprog_; 
        cpu=cpu_;
        mem=mem_;
        option=option_;
    }
    
    
    void setCpu(CPU cpu_);
    CPU getCpu()const;
    void setCPUProgram(CPUProgram cpuprog_);
    CPUProgram getCPUProgram()const;
    void setMemory(Memory mem_);
    Memory getMemory()const;
    void setOption(int option);
    int getOption()const;
    void execute();
    
    private:
         CPU cpu;
         CPUProgram cpuprog;
         Memory mem;
         int option;
    
};

#endif /* COMPUTER_H */