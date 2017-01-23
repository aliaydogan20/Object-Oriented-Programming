/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alico
 *
 * Created on 27 Ekim 2016 Perşembe, 20:42
 */

#include <cstdlib>
#include <cstring>
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "Computer.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    int val=0;

    // Eger hatali arguman girildiyse
    if(argc!=3||((argv[2][0]!='0'&&argv[2][0]!='1'&&argv[2][0]!='2')||argv[2][1]>0))
    {
        cerr<<"Hatali giris yaptiniz"<<endl;	
	return 0;
    }
    string filename=argv[1];
    int option=atoi(argv[2]);
    
    ///////////////////////TESTLER/////////////////////////////////////
    Memory myMemory(option);
    
     //index,value
     myMemory.setMem(0,100);
     cout<<"myMemory.getMem(0) ="<<myMemory.getMem(0)<<endl;
    
     //Memory values
     myMemory.printAll();
    
     CPU myCpu(option);
     
     myCpu.execute("MOV #0, R1",myMemory);
     myCpu.execute("MOV R1, #1",myMemory);
     
     myCpu.print();
     myMemory.printAll();
   
    
     
     CPUProgram myCpuProgram(option);
   
     myCpuProgram.readFile(filename);

     cout<<"İlk satir instruction ="<<myCpuProgram.getLine(1)<<endl;
     cout<<"Son satir instruction ="<<myCpuProgram.getLine(myCpuProgram.size())<<endl;
 		    
 	   
     Computer myComputer1(myCpu,myCpuProgram,myMemory,option);
     Computer myComputer2(option);
    
     myComputer1.setCpu(myComputer2.getCpu());
     myComputer1.setCPUProgram(myComputer2.getCPUProgram());
     myComputer1.setMemory(myComputer2.getMemory());
     
     myComputer2.execute();
     
    return 0;
}
