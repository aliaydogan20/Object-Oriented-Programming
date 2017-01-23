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
        CPU cpu_(option_);
        CPUProgram cpuprog_(option_);
        Memory mem_(option_);
        
        cpu.setPC(cpu_.getPC());
        cpu.setR1(cpu_.getR1());
        cpu.setR2(cpu_.getR2());
        cpu.setR3(cpu_.getR3());
        cpu.setR4(cpu_.getR4());
        cpu.setR5(cpu_.getR5());
        cpu.setHalted(cpu_.getHalted());
        cpu.setOption(cpu_.getOption());
        cpuprog.setFileName(cpuprog_.getFilename());
        cpuprog.setSize(cpuprog_.getSize());
        cpuprog.setSizeLine(cpuprog_.getSizeLine());
        for(int i=0;i<50;i++)
        {
        mem.setMem(mem_.getMem(i),0);
        mem.setOption(mem_.getOption());
        }
         
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