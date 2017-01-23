/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CPU.h"
#include "CPUProgram.h"
// Default constructor
CPU::CPU():R1(0),R2(0),R3(0),R4(0),R5(0),PC(1),halt(0)
{
    
}
// Constructor
CPU::CPU(const int Reg1,const int Reg2,const int Reg3,const int Reg4,const int Reg5,const int PrC,const int halt_)
{
    R1=Reg1;
    R2=Reg2;
    R3=Reg3;
    R4=Reg4;
    R5=Reg5;
    PC=PrC;
    halt=halt_;
}
// Constructor
CPU::CPU(const int Reg1, const int Reg2, const int Reg3, const int Reg4, const int Reg5, const int PrC)
{
    R1=Reg1;
    R2=Reg2;
    R3=Reg3;
    R4=Reg4;
    R5=Reg5;
    PC=PrC;
    halt=0;
}
// Constructor
CPU::CPU(const int Reg1, const int Reg2, const int Reg3, const int Reg4, const int Reg5)
{
    R1=Reg1;
    R2=Reg2;
    R3=Reg3;
    R4=Reg4;
    R5=Reg5;
    PC=1;
    halt=0;
}
// Halted function
bool CPU::halted()
{
    if(getHalted()==1)
        return true;
    else
        return false;
}
// execute function
void CPU::execute(string instruction)
{
    int value=0;
   
    if(parsingFunctionInstruction(instruction)==0)
    {
    	cout<<"Program aborted"<<endl;
    	exit(0);
    }
   // Eger parsing sonucu 1 ise move islemi yap
   if(parsingFunctionInstruction(instruction)==1)			
   {
       
		value=parsingRemainderConstant(instruction,1);
        parsingRemainderRegister(instruction,value,1);
 		setPC(getPC()+1);
    }	
    // Parsing sonucu 2 ise sub islemi yap
    else if(parsingFunctionInstruction(instruction)==2)
    {
        
		value=parsingRemainderConstant(instruction,2);
		parsingRemainderRegister(instruction,value,2);
        setPC(getPC()+1);  
    }
    // Parsing sonucu 3 ise add islemi yap
    else if(parsingFunctionInstruction(instruction)==3)
    {
     	value=parsingRemainderConstant(instruction,3);
	 	parsingRemainderRegister(instruction,value,3);
	 	setPC(getPC()+1);	
    }
    // Parsing sonucu 4 ise jump islemi yap
    else if(parsingFunctionInstruction(instruction)==4)
    {      
    	
        int ret=-1;
        ret=jmpAccordingConstant(instruction);
		if(ret==0)
		{
		value=parsingRemainderConstant(instruction,4);	
        	
    	}
    	setPC(getPC()+1);
    }
    // Parsing sonucu 5 ise prnt islemi yap
    else if(parsingFunctionInstruction(instruction)==5)
    {
       
        printInstruction(instruction);
		setPC(getPC()+1);	
    }
    else if(parsingFunctionInstruction(instruction)==6)
    {
         setPC(getPC()+1);
        setHalted(1);	
        //setPC(getPC()-1);
    }
   
    
}
// Print function
void CPU::print()
{
    cout<<"R1= "<<R1<<","<<"R2= "<<R2<<","<<"R3= "<<R3<<","<<"R4= "<<R4<<","<<"R5= "<<R5<<","<<"PC= "<<PC-1<<endl;
}
// Parsing function
int CPU::parsingFunctionInstruction(string word)
{

	for(int i=0;word[i]!='\0';i++)
	{
		// Instruction belirleme
		if(word[i]=='M'&&word[i+1]=='O'&&word[i+2]=='V')
		return 1;
		if(word[i]=='m'&&word[i+1]=='o'&&word[i+2]=='v')
		return 1;
	
		if(word[i]=='S'&&word[i+1]=='U'&&word[i+2]=='B')
		return 2;
	    if(word[i]=='s'&&word[i+1]=='u'&&word[i+2]=='b')
		return 2;
	
		if(word[i]=='A'&&word[i+1]=='D'&&word[i+2]=='D')
		return 3;
		if(word[i]=='a'&&word[i+1]=='d'&&word[i+2]=='d')
		return 3;
	
		if(word[i]=='J'&&word[i+1]=='M'&&word[i+2]=='P')
		return 4;
	    if(word[i]=='j'&&word[i+1]=='m'&&word[i+2]=='p')
		return 4;
	
	
		if(word[i]=='P'&&word[i+1]=='R'&&word[i+2]=='N')
		return 5;
		if(word[i]=='p'&&word[i+1]=='r'&&word[i+2]=='n')
		return 5;
	
	    if(word[i]=='H'&&word[i+1]=='L'&&word[i+2]=='T')
		return 6;
		if(word[i]=='h'&&word[i+1]=='l'&&word[i+2]=='t')
		return 6;
		
	}
	return 0;
}
// Parsing function Remainder 
int CPU::parsingRemainderConstant(string word, int selection)
{
    int j,flag=0,i=-1,k=0,jmpFlag=0;
    string expr,expr2;
	
		
    for( i=0;word[i]!=',';i++)
    {
	if((word[i]=='R'||word[i]=='r')&&word[i+1]=='1') flag=1;		
	else if((word[i]=='R'||word[i]=='r')&&word[i+1]=='2') flag=2;		
	else if((word[i]=='R'||word[i]=='r')&&word[i+1]=='3') flag=3;		
	else if((word[i]=='R'||word[i]=='r')&&word[i+1]=='4') flag=4;		
	else if((word[i]=='R'||word[i]=='r')&&word[i+1]=='5') flag=5;								
    }
    
    for(j=i+1; word[j]!='\0';j++)
    {
        if(word[j]!=' ')
        {
            expr+=word[j];	
	}
    }
    // eger expression constant ise onunla ilgili islemlere git
    if((expr[0]!='R'||expr[0]!='r')&&selection==1)
    {
        moveCalculateConstant(expr,flag);
    }
    else if((expr[0]!='R'||expr[0]!='r')&&selection==2)
    {
	subCalculateConstant(expr,flag);
    }
    else if((expr[0]!='R'||expr[0]!='r')&&selection==3)
    {
	addCalculateConstant(expr,flag);
    }
    else if((expr[0]!='R'||expr[0]!='r')&&selection==4)
    {
	jmpAccordingRegister(expr,flag);
    }
		
    return flag;			
    
}

void CPU::parsingRemainderRegister(string word,int RegValue,int selection)
{
	int j;
	int i,k=0;
	string expr;
	int expr_flag=0;
	
	for( i=0;word[i]!=',';i++)
	{
	}
	
	for(j=i+1; word[j]!='\0';j++)
	{
		if(word[j]!=' ')
		{
			expr+=word[j];	
		}
	}
	
	if((expr[0]=='R'||expr[0]=='r')&&selection==1)
	{
		moveCalculateRegister(expr,RegValue);
	}
	if((expr[0]=='R'||expr[0]=='r')&&selection==2)
	{
		subCalculateRegister(expr,RegValue);
	}
	if((expr[0]=='R'||expr[0]=='r')&&selection==3)
	{
		addCalculateRegister(expr,RegValue);
	}

}
// Eger move reg, constant bir yapiysa 
void CPU::moveCalculateConstant(string expr,int flag)
{		

    if(flag==1) setR1(myAtoiFunction(expr));
    if(flag==2) {
        setR2(myAtoiFunction(expr));
    }
    if(flag==3) setR3(myAtoiFunction(expr));
    if(flag==4) setR4(myAtoiFunction(expr));
    if(flag==5) setR5(myAtoiFunction(expr));
}
// Eger move reg,reg bir yapiysa
 void CPU::moveCalculateRegister(string expr,int RegValue)
 {
        if(RegValue==1&&expr[1]=='1') setR1(getR1());
	if(RegValue==1&&expr[1]=='2') setR1(getR2());
	if(RegValue==1&&expr[1]=='3') setR1(getR3());
	if(RegValue==1&&expr[1]=='4') setR1(getR4());
	if(RegValue==1&&expr[1]=='5') setR1(getR5());
		
	if(RegValue==2&&expr[1]=='1') setR2(getR1());
	if(RegValue==2&&expr[1]=='2') setR2(getR2());
	if(RegValue==2&&expr[1]=='3') setR2(getR3());
	if(RegValue==2&&expr[1]=='4') setR2(getR4());
	if(RegValue==2&&expr[1]=='5') setR2(getR5());
		
	if(RegValue==3&&expr[1]=='1') setR3(getR1());
	if(RegValue==3&&expr[1]=='2') setR3(getR2());
	if(RegValue==3&&expr[1]=='3') setR3(getR3());
	if(RegValue==3&&expr[1]=='4') setR3(getR4());
	if(RegValue==3&&expr[1]=='5') setR3(getR5());
		
	if(RegValue==4&&expr[1]=='1') setR4(getR1());
	if(RegValue==4&&expr[1]=='2') setR4(getR2());
	if(RegValue==4&&expr[1]=='3') setR4(getR3());
	if(RegValue==4&&expr[1]=='4') setR4(getR4());
	if(RegValue==4&&expr[1]=='5') setR4(getR5());
				
	if(RegValue==5&&expr[1]=='1') setR5(getR1());
	if(RegValue==5&&expr[1]=='2') setR5(getR2());								
	if(RegValue==5&&expr[1]=='3') setR5(getR3());
	if(RegValue==5&&expr[1]=='4') setR5(getR4());
	if(RegValue==5&&expr[1]=='5') setR5(getR5());
 }
// Eger sub reg,constant bir yapiysa
void CPU::subCalculateConstant(string expr,int flag)
{
	if(flag==1) setR1(getR1()-myAtoiFunction(expr)); 
	if(flag==2) setR2(getR2()-myAtoiFunction(expr)); 
	if(flag==3) setR3(getR3()-myAtoiFunction(expr)); 
	if(flag==4) setR4(getR4()-myAtoiFunction(expr)); 
	if(flag==5) setR5(getR5()-myAtoiFunction(expr)); 
}
// Eger sub reg,reg bir yapiysa
void CPU::subCalculateRegister(string expr,int RegValue)
{
    if(RegValue==1&&expr[1]=='1') setR1(getR1()-getR1());
    if(RegValue==1&&expr[1]=='2') setR1(getR1()-getR2());
    if(RegValue==1&&expr[1]=='3') setR1(getR1()-getR3());
    if(RegValue==1&&expr[1]=='4') setR1(getR1()-getR4());
    if(RegValue==1&&expr[1]=='5') setR1(getR1()-getR5());
		
    if(RegValue==2&&expr[1]=='1') setR2(getR2()-getR1());
    if(RegValue==2&&expr[1]=='2') setR2(getR2()-getR2());
    if(RegValue==2&&expr[1]=='3') setR2(getR2()-getR3());
    if(RegValue==2&&expr[1]=='4') setR2(getR2()-getR4());
    if(RegValue==2&&expr[1]=='5') setR2(getR2()-getR5());
		
    if(RegValue==3&&expr[1]=='1') setR3(getR3()-getR1());
    if(RegValue==3&&expr[1]=='2') setR3(getR3()-getR2());
    if(RegValue==3&&expr[1]=='3') setR3(getR3()-getR3());
    if(RegValue==3&&expr[1]=='4') setR3(getR3()-getR4());
    if(RegValue==3&&expr[1]=='5') setR3(getR3()-getR5());
		
    if(RegValue==4&&expr[1]=='1') setR4(getR4()-getR1());
    if(RegValue==4&&expr[1]=='2') setR4(getR4()-getR2());
    if(RegValue==4&&expr[1]=='3') setR4(getR4()-getR3());
    if(RegValue==4&&expr[1]=='4') setR4(getR4()-getR4());
    if(RegValue==4&&expr[1]=='5') setR4(getR4()-getR5());
		
    if(RegValue==5&&expr[1]=='1') setR5(getR5()-getR1());
    if(RegValue==5&&expr[1]=='2') setR5(getR5()-getR2());								
    if(RegValue==5&&expr[1]=='3') setR5(getR5()-getR3());
    if(RegValue==5&&expr[1]=='4') setR5(getR5()-getR4());
    if(RegValue==5&&expr[1]=='5') setR5(getR5()-getR5());
}
// Eger add reg,constant bir yapiysa 
void CPU::addCalculateConstant(string expr,int flag)
{
	if(flag==1) setR1(getR1()+myAtoiFunction(expr)); 
	if(flag==2) setR2(getR2()+myAtoiFunction(expr)); 
	if(flag==3) setR3(getR3()+myAtoiFunction(expr)); 
	if(flag==4) setR4(getR4()+myAtoiFunction(expr)); 
	if(flag==5) setR5(getR5()+myAtoiFunction(expr)); 
}
// Eger add reg,reg bir yapiysa
void CPU::addCalculateRegister(string expr,int RegValue)
{

    if(RegValue==1&&expr[1]=='1') setR1(getR1()+getR1());
    if(RegValue==1&&expr[1]=='2') setR1(getR1()+getR2());
    if(RegValue==1&&expr[1]=='3') setR1(getR1()+getR3());
    if(RegValue==1&&expr[1]=='4') setR1(getR1()+getR4());
    if(RegValue==1&&expr[1]=='5') setR1(getR1()+getR5());
		
    if(RegValue==2&&expr[1]=='1') setR2(getR2()+getR1());
    if(RegValue==2&&expr[1]=='2') setR2(getR2()+getR2());
    if(RegValue==2&&expr[1]=='3') setR2(getR2()+getR3());
    if(RegValue==2&&expr[1]=='4') setR2(getR2()+getR4());
    if(RegValue==2&&expr[1]=='5') setR2(getR2()+getR5());
		
    if(RegValue==3&&expr[1]=='1') setR3(getR3()+getR1());
    if(RegValue==3&&expr[1]=='2') setR3(getR3()+getR2());
    if(RegValue==3&&expr[1]=='3') setR3(getR3()+getR3());
    if(RegValue==3&&expr[1]=='4') setR3(getR3()+getR4());
    if(RegValue==3&&expr[1]=='5') setR3(getR3()+getR5());
		
    if(RegValue==4&&expr[1]=='1') setR4(getR4()+getR1());
    if(RegValue==4&&expr[1]=='2') setR4(getR4()+getR2());
    if(RegValue==4&&expr[1]=='3') setR4(getR4()+getR3());
    if(RegValue==4&&expr[1]=='4') setR4(getR4()+getR4());
    if(RegValue==4&&expr[1]=='5') setR4(getR4()+getR5());
		
    if(RegValue==5&&expr[1]=='1') setR5(getR5()+getR1());
    if(RegValue==5&&expr[1]=='2') setR5(getR5()+getR2());								
    if(RegValue==5&&expr[1]=='3') setR5(getR5()+getR3());
    if(RegValue==5&&expr[1]=='4') setR5(getR5()+getR4());
    if(RegValue==5&&expr[1]=='5') setR5(getR5()+getR5());
}
// Benim atoi fonksiyonum
int CPU::myAtoiFunction(string str)
{
        int val=0;
	int add=0;
	val=str.length();
	
	int lang=0;
	
	for(int j=0;j<val;j++)
	{
		// Eger 12;yorum gibi bir yapiysa sadece 12 alinir.
		  if(str[j]>47&&str[j]<58)
		  {
		  	lang++;
		  }
		  else 
		  break;
		
	}
	int deg=lang; 
	
	for(int i=0;i<lang;i++)
	{ 
	  	
		if(lang!=1)
		add+=(str[i]-'0')*(myPowFunction(10,(deg-1)));
		else if(deg==1)
		{
		add+=(str[i]-'0')*1;
		break;
		}
		deg--;
	}
	
	return add;
}
// Pow fonksiyonumuz
int CPU::myPowFunction(int val1,int val2)
{
	int value=1;
	
	int i=0;
	
	while(i<val2)	
	{
	
		value=value*val1;
		i++;
	}				
	return value;
}
// Yazdirma
void CPU::printInstruction(string word)
{

	int i,j,jmpFlag,x=0;
	string expr;

	for(i=0;word[i]!='\0';i++)
	{	
            if(word[i]=='P'&&word[i+1]=='R'&&word[i+2]=='N')
            jmpFlag=i+3;
            if(word[i]=='p'&&word[i+1]=='r'&&word[i+2]=='n')
            jmpFlag=i+3;
	}
	// Yazdirilacak register expr de tutulur. 
	for(j=jmpFlag;word[j]!='\0';j++)
	{
            if(word[j]!=' ')
            expr+=word[j];	
            else
            {
            if((x!=0)&&(j-x)>1)
            break;
            else
            x=j;
            }
				
        }	
	if((expr[0]=='R'||expr[0]=='r')&&expr[1]=='1') cout<<getR1()<<endl;		  
	else if((expr[0]=='R'||expr[0]=='r')&&expr[1]=='2') cout<<getR2()<<endl;
	else if((expr[0]=='R'||expr[0]=='r')&&expr[1]=='3') cout<<getR3()<<endl;
	else if((expr[0]=='R'||expr[0]=='r')&&expr[1]=='4') cout<<getR4()<<endl;
	else if((expr[0]=='R'||expr[0]=='r')&&expr[1]=='5') cout<<getR5()<<endl;
        else
		{
            cout<<myAtoiFunction(expr)<<endl;
        }
		
}
// Jmp PC ile özdeslestirildi.
int CPU::jmpAccordingConstant(string word)
{
        

	string line,expr;
	int i=0,k=0,x=0,j=0;
	int jmpFlag=0;
	
	for(i=0;word[i]!='\0';i++)
	{	
		if(word[i]=='J'&&word[i+1]=='M'&&word[i+2]=='P')
		{jmpFlag=i+3;}
		else if(word[i]=='j'&&word[i+1]=='m'&&word[i+2]=='p')
		{jmpFlag=i+3;}	
	}
		
	for(j=jmpFlag;word[j]!='\0';j++)
	{
            if(word[j]!=' ')
            expr+=word[j];	
            else
            {
		if((x!=0)&&(j-x)>1)
		break;
		else
		x=j;
            }
	}
        
        if(expr[0]=='R'||expr[0]=='r')
		return 0;	
        
      	setPC(myAtoiFunction(expr)-1);
         
         return 1;
        
}
// Jmp PC ile özdeslestirildi.
void CPU::jmpAccordingRegister(string expr,int flag)
{
    string line;
    int i=0;
			
    if((flag==1&&getR1()==0)||
        (flag==2&&getR2()==0)||
        (flag==3&&getR3()==0)||
        (flag==4&&getR4()==0)||
        (flag==5&&getR5()==0))
    {
          setPC(myAtoiFunction(expr)-1);
    }
    
}
