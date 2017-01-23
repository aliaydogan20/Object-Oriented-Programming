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
#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
	int val=0;

	// Eger hatali arguman girildiyse
	if(argc!=3||(argv[2][0]!='0'&&argv[2][0]!='1'||argv[2][1]>0))
	{
		cerr<<"Hatali giris yaptiniz"<<endl;	
		return 0;
	}

    CPUProgram cp(argv[1]);
    CPU myCp,myCp2(10,12,15,24,25,12,0);
    
    cout<<"İlk ödevde yazdigimiz bizim add square fonksiyonumuz:"<<endl; 
    cout<<"######################################################"<<endl;
    while(!myCp.halted())
    {
    	if(argv[2][0]=='1')
		{
			// Jmp ve Prn icin ozel yazdirma
			if(myCp.parsingFunctionInstruction(cp.getLine(myCp.getPC()))==4)
			{
    			cout<<cp.getLine(myCp.getPC())<<"-";
    			myCp.setPC(myCp.getPC()+1);
    			myCp.print();
    			myCp.setPC(myCp.getPC()-1);
    			val=1;
    		}
    		else if(myCp.parsingFunctionInstruction(cp.getLine(myCp.getPC()))==5)
			{
				cout<<cp.getLine(myCp.getPC())<<"-";
    			myCp.setPC(myCp.getPC()+1);
    			myCp.print();
    			myCp.setPC(myCp.getPC()-1);
    			val=1;
			}	
    		else
    		cout<<cp.getLine(myCp.getPC())<<"-";
    	}
    	
        myCp.execute(cp.getLine(myCp.getPC()));
        if(argv[2][0]=='1')
		{
			if(val==0)
 			{
 			myCp.print();
 			}
 			
 			val=0;
 		}
 
    }
     cout<<"######################################################"<<endl;
     cout<<"Diger TESTLER "<<endl;
     cout<<"######################################################"<<endl;
     cout<<"R2= "<<myCp2.getR2()<<endl;
     cout<<"R3= "<<myCp2.getR3()<<endl;
     cout<<"R5= "<<myCp2.getR5()<<endl;	 
     cout<<"PC= "<<myCp2.getPC()<<endl;
     myCp2.execute("ADD R3,33");
     cout<<"ADD R3,33 execute islemi sonucu ";
     cout<<"R3= "<<myCp2.getR3()<<endl; 
     cout<<"PRN R2 islemi sonucu ";
     myCp2.execute("PRN R2");
     cout<<"add.txt GetLine 11 ";
     cout<<(cp.getLine(11))<<endl; 
     cout<<"add.txt GetLine 13 ";
     cout<<(cp.getLine(13))<<endl; 
    
    return 0;
}

