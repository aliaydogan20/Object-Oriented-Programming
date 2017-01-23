/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Memory.h"
#define MEMSIZE 50

Memory::Memory()
{
     option=0;
    
    for(int i=0;i<MEMSIZE;i++)
    {
        memoryAddresses[i]=0;
    }
}


Memory::Memory(int option_)
{
    option=option_;
    
    for(int i=0;i<MEMSIZE;i++)
    {
        memoryAddresses[i]=0;
    }
}

int Memory::getOption() 
{
    return option;
}
void Memory::setOption(int option_)
{
    option=option_;
}

unsigned int Memory::getMem(int addressCount)
{
    return memoryAddresses[addressCount];
}

void Memory::setMem(int addressCount, int value)
{
    memoryAddresses[addressCount]=value;
}
void Memory::printAll()
{
    
       cout<<"Memory values: "<<endl; 
       for(int i=0;i<MEMSIZE;i++)
       {
           cout<<"["<<memoryAddresses[i]<<"]"<<endl;
       }  
         
}