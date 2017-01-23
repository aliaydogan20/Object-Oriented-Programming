/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myMain.cpp
 * Author: alico
 *
 */


#include "requiredIncs.h"


int main(int argc, char** argv) 
{
    string filename=argv[1];
    int option=atoi(argv[2]);
    
     
     CPUProgram myCPUProgram(option);
     myCPUProgram.ReadFile(filename);
    	
     CPUProgram myCPUProgram2(option);
    	
     cout<<"İlk satir ";	
     cout<<myCPUProgram[0]<<endl;
     cout<<"Son satir ";
     cout<<myCPUProgram[myCPUProgram.size()-1]<<endl;
     
     myCPUProgram2=(myCPUProgram+ "JMP 12");
     
     cout<<"+ isleminden sonra myCPUProgram2 son satir "<<myCPUProgram2[myCPUProgram2.size()-1]<<endl;
     
     myCPUProgram2+=("JPN #4,12");
     
     cout<<"+= isleminden sonra myCPUProgram2 son satir "<<myCPUProgram2[myCPUProgram2.size()-1]<<endl;
     
     --myCPUProgram2;
     
     cout<<"Prefix -- isleminden sonra myCPUProgram2 son satir "<<myCPUProgram2[myCPUProgram2.size()-1]<<endl;
     	
     myCPUProgram2--;	
     
     cout<<"Postfix -- isleminden sonra myCPUProgram2 son satir "<<myCPUProgram2[myCPUProgram2.size()-1]<<endl;
     
  	 myCPUProgram--;	
     
     cout<<"myCPUProgram size "<<myCPUProgram.size()<<endl;
     cout<<"myCPUProgram2 size "<<myCPUProgram2.size()<<endl;
     
     cout<<"Karsilastirma isleminin sonucu ";
     cout<< (myCPUProgram == myCPUProgram2 ? "DONE" : "FAIL") << endl;
     
     cout<<"call operator sonucu"<<endl<< myCPUProgram(2,7)<<endl;
     
     cout<<"index operator sonucu myCPUProgram[6] 7. satir"<<myCPUProgram[6]<<endl; 	
     
     cout<<"myCPUProgram2 << operator"<<endl<<myCPUProgram2;
    
    return 0;
}
