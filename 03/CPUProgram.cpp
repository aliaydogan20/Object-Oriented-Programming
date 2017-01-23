/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CPUProgram.h"

void CPUProgram::readFile(string filename_) 
{
    ifstream fr;
    int i,PC=1;
    fr.open(filename_.c_str());
    string line,tmp;
    
    filename=filename_.c_str();
    
    
            
    while(!fr.eof())
    {
        
        if(getline(fr,line,'\n'))
        {
    
            for(i=0;i<line.length();i++)
	    {	 
		if(line[i]=='\n'||line[i]==';')
		{
	           break;
	        }
                tmp+=line[i];
		
	    }
            str[cp.getPC()]=tmp;
            cp.setPC(cp.getPC()+1);
            
            tmp.clear();
        }
        sizeLine=cp.getPC()-1;
                  
     }
    fr.close();
}
CPUProgram::CPUProgram(string filename_)
{
    readFile(filename_);
    
}
string CPUProgram::getLine(int PC_)
{
    return str[PC_];
}
int CPUProgram::size()
{
    return sizeLine;
}
