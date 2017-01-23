/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: alico
 *
 * Created on 06 Kasım 2016 Pazar, 16:38
 */
#include<iostream>



#ifndef MEMORY_H
#define MEMORY_H

using namespace std; 

class Memory
{
    public:
        Memory();
        Memory(int option_);
        int getOption();
        void setOption(int option_);
        unsigned int getMem(int addressCount);
        void setMem(int addressCount,int value);
        void printAll();
        
    private:
        unsigned int memoryAddresses[50];
        int option;
};


#endif /* MEMORY_H */

