/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Computer.h"

CPU Computer::getCpu() const
{
    return cpu;
}
void Computer::setCpu(CPU cpu_)
{
    cpu=cpu_;
}

CPUProgram Computer::getCPUProgram() const
{
    return cpuprog;
}
void Computer::setCPUProgram(CPUProgram cpuprog_)
{
    cpuprog=cpuprog_;
}
Memory Computer::getMemory() const
{
    return mem;
}
void Computer::setMemory(Memory mem_)
{
    mem=mem_;
}
int Computer::getOption() const
{
    return option;
}
void Computer::setOption(int option_)
{
    option_=option;
}
void Computer::execute()
{
    int val=0;
    
     while(!cpu.halted())
    {
        
	
		// Jmp ve Prn icin ozel yazdirma
		if((cpu.parsingFunctionInstruction(cpuprog.getLine(cpu.getPC()))==4
                   ||cpu.parsingFunctionInstruction(cpuprog.getLine(cpu.getPC()))==5
                   ||cpu.parsingFunctionInstruction(cpuprog.getLine(cpu.getPC()))==7)
                         &&cpu.getOption()!=0)
		{
                    cout<<cpuprog.getLine(cpu.getPC())<<"-";
                    cpu.setPC(cpu.getPC()+1);
                    if(cpu.getOption()==1)
                    cpu.print();
                    if(mem.getOption()==2)
                    mem.printAll();    
                    cpu.setPC(cpu.getPC()-1);
                    val=1;
                 }
    		
    		else if(cpu.getOption()!=0)
    		cout<<cpuprog.getLine(cpu.getPC())<<"-";
    	
            cpu.execute(cpuprog.getLine(cpu.getPC()),mem);
            
            
            if((cpu.getOption()==1)&&val==0)
            {
                cpu.print();
            }
            if((mem.getOption()==2)&&val==0)
            {
                mem.printAll();
            }
 			
            val=0;
                        
            
 
    }
}