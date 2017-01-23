/*
    File: myCpu.cpp
	Author: 101044054 Ali Aydoğan
	HW1 Cpu Programming
		
    make komutuyla binary dosyalar olusturulur.
    
    Calistirilma sekli 
    
    ./myCpu add.txt 1 
    vey 
    ./myCpu add.txt 0
    
    seklindedir.

*/
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// Registers
struct Registers
{
	int R1;
	int R2;
	int R3;
	int R4;
	int R5;
};

// Function Prototypes
void init(Registers *reg);
void debugModePrint(string str,Registers *Reg);
int parsingFunctionInstruction(string word);
int parsingRemainderConstant(string word,Registers *Reg,int select,ifstream *fr);
void parsingRemainderRegister(string word,Registers *Reg,int value,int select,ifstream *fr);
void moveCalculateConstant(string expr,Registers *Reg,int flag);
void moveCalculateRegister(string expr,Registers *Reg,int regValue);
void subCalculateConstant(string expr,Registers *Reg,int flag);
void subCalculateRegister(string expr,Registers *Reg,int regValue);
void addCalculateConstant(string expr,Registers *Reg,int flag);
void addCalculateRegister(string expr,Registers *Reg,int regValue);
void jmpAccordingRegister(string expr,Registers *Reg,int flag,ifstream *fr);
int jmpAccordingConstant(string expr,Registers *Reg,ifstream *fr);
int myAtoiFunction(string str);
int myPowFunction(int val1,int val2);
void printRegister(string expr,Registers *Reg);


int main(int argc,char* argv[])
{
	ifstream fr;
	struct Registers Reg;
	int value=0,i;
	string str,line;
	
	fr.open(argv[1]); 
	init(&Reg);
	
	// Eger hatali arguman girildiyse
	if(argc!=3||(argv[2][0]!='0'&&argv[2][0]!='1'||argv[2][1]>0))
	{
		cerr<<"Hatali giris yaptiniz"<<endl;	
		return 0;
	}
	
	// Dosya sonuna kadar gitme
	while(!fr.eof())
	{
		//fr.seekg(0, ios::beg );
		if(getline(fr,line,'\n'))
		{	
			// ; ya da \n gorene kadar yapilacak islemi yazdirmak icin
			for(i=0;i<line.length();i++)
			{	
			  
				if(line[i]=='\n'||line[i]==';')
				{
			   	break;
			    }
			    str+=line[i];
		
			}
			
			// Eger parsing sonucu 1 ise move islemi yap
			if(parsingFunctionInstruction(line)==1)
			{
				value=parsingRemainderConstant(line,&Reg,1,&fr);
				parsingRemainderRegister(line,&Reg,value,1,&fr);
				if(argv[2][0]=='1')
				{
					debugModePrint(str,&Reg);			
				}
			}	
			// Parsing sonucu 2 ise sub islemi yap
			else if(parsingFunctionInstruction(line)==2)
			{
			value=parsingRemainderConstant(line,&Reg,2,&fr);
			parsingRemainderRegister(line,&Reg,value,2,&fr);
				if(argv[2][0]=='1')
				{
					debugModePrint(str,&Reg);		
				}
			}
			//// Parsing sonucu 3 ise add islemi yap
			else if(parsingFunctionInstruction(line)==3)
			{
			value=parsingRemainderConstant(line,&Reg,3,&fr);
			parsingRemainderRegister(line,&Reg,value,3,&fr);
				if(argv[2][0]=='1')
				{
					debugModePrint(str,&Reg);
				}
			}
			// Parsing sonucu 4 ise jump islemi yap
			else if(parsingFunctionInstruction(line)==4)
			{
			int ret=-1;
			ret=jmpAccordingConstant(line,&Reg,&fr);
			if(ret==0)
			value=parsingRemainderConstant(line,&Reg,4,&fr);	
				if(argv[2][0]=='1')
				{
					debugModePrint(str,&Reg);
				}
			}
			// Parsing sonucu 2 ise prnt islemi yap
			else if(parsingFunctionInstruction(line)==5)
			{
			printRegister(line,&Reg);
				if(argv[2][0]=='1')
				{
					debugModePrint(str,&Reg);
				}
			}
			// Parsing sonucu 2 ise halt islemi yap
			else if(parsingFunctionInstruction(line)==6)
			{
				if(argv[2][0]=='1')
				{
					debugModePrint(str,&Reg);
			}
			//halt
			 fr.close();
			 // Programi bitir
			 return -1;
			 
			}
			str.clear();
			line.clear();
		}
		
	}	
	fr.close();
	return 0;
	

}
//Register initialize
void init(Registers *reg)
{
	reg->R1=0;
	reg->R2=0;
	reg->R3=0;
	reg->R4=0;
	reg->R5=0;
}

int parsingFunctionInstruction(string word)
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
// Eger instruction reg,constant tarzindaysa bu fonksiyon islem yapar.
int parsingRemainderConstant(string word,Registers *Reg,int selection,ifstream *fr)
{
	int j,flag=0,i=-1,k=0,jmpFlag=0,x=0,y=0;
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
			moveCalculateConstant(expr,Reg,flag);
		}
		else if((expr[0]!='R'||expr[0]!='r')&&selection==2)
		{
			subCalculateConstant(expr,Reg,flag);
		}
		else if((expr[0]!='R'||expr[0]!='r')&&selection==3)
		{
			addCalculateConstant(expr,Reg,flag);
		}
		else if((expr[0]!='R'||expr[0]!='r')&&selection==4)
		{
			jmpAccordingRegister(expr,Reg,flag,fr);
		}
		
		
	return flag;			
}
// Eger instruction reg,reg tarzi bir yapiysa bu fonksiyon devreye girer.
void parsingRemainderRegister(string word,Registers *Reg,int RegValue,int selection,ifstream *fr)
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
		moveCalculateRegister(expr,Reg,RegValue);
	}
	if((expr[0]=='R'||expr[0]=='r')&&selection==2)
	{
		subCalculateRegister(expr,Reg,RegValue);
	}
	if((expr[0]=='R'||expr[0]=='r')&&selection==3)
	{
		addCalculateRegister(expr,Reg,RegValue);
	}

}
// Eger move reg, constant bir yapiysa 
void moveCalculateConstant(string expr,Registers *Reg,int flag)
{
		
	
		if(flag==1) Reg->R1=myAtoiFunction(expr);
		if(flag==2) Reg->R2=myAtoiFunction(expr);
		if(flag==3) Reg->R3=myAtoiFunction(expr);
		if(flag==4) Reg->R4=myAtoiFunction(expr);
		if(flag==5) Reg->R5=myAtoiFunction(expr);
		
		
}
// Eger move reg,reg bir yapiysa
void moveCalculateRegister(string expr,Registers *Reg,int RegValue)
{
		if(RegValue==1&&expr[1]=='1') Reg->R1=Reg->R1;
		if(RegValue==1&&expr[1]=='2') Reg->R1=Reg->R2;
		if(RegValue==1&&expr[1]=='3') Reg->R1=Reg->R3;
		if(RegValue==1&&expr[1]=='4') Reg->R1=Reg->R4;
		if(RegValue==1&&expr[1]=='5') Reg->R1=Reg->R5;
		
		if(RegValue==2&&expr[1]=='1') Reg->R2=Reg->R1;
		if(RegValue==2&&expr[1]=='2') Reg->R2=Reg->R2;
		if(RegValue==2&&expr[1]=='3') Reg->R2=Reg->R3;
		if(RegValue==2&&expr[1]=='4') Reg->R2=Reg->R4;
		if(RegValue==2&&expr[1]=='5') Reg->R2=Reg->R5;
		
		if(RegValue==3&&expr[1]=='1') Reg->R3=Reg->R1;
		if(RegValue==3&&expr[1]=='2') Reg->R3=Reg->R2;
		if(RegValue==3&&expr[1]=='3') Reg->R3=Reg->R3;
		if(RegValue==3&&expr[1]=='4') Reg->R3=Reg->R4;
		if(RegValue==3&&expr[1]=='5') Reg->R3=Reg->R5;
		
		if(RegValue==4&&expr[1]=='1') Reg->R4=Reg->R1;
		if(RegValue==4&&expr[1]=='2') Reg->R4=Reg->R2;
		if(RegValue==4&&expr[1]=='3') Reg->R4=Reg->R3;
		if(RegValue==4&&expr[1]=='4') Reg->R4=Reg->R4;
		if(RegValue==4&&expr[1]=='5') Reg->R4=Reg->R5;
		
				
		if(RegValue==5&&expr[1]=='1') Reg->R5=Reg->R1;
		if(RegValue==5&&expr[1]=='2') Reg->R5=Reg->R2;								
		if(RegValue==5&&expr[1]=='3') Reg->R5=Reg->R3;
		if(RegValue==5&&expr[1]=='4') Reg->R5=Reg->R4;
		if(RegValue==5&&expr[1]=='5') Reg->R5=Reg->R5;
}
// Eger sub reg,constant bir yapiysa
void subCalculateConstant(string expr,Registers *Reg,int flag)
{
		if(flag==1) Reg->R1=Reg->R1-myAtoiFunction(expr);
		if(flag==2) Reg->R2=Reg->R2-myAtoiFunction(expr);
		if(flag==3) Reg->R3=Reg->R3-myAtoiFunction(expr);
		if(flag==4) Reg->R4=Reg->R4-myAtoiFunction(expr);
		if(flag==5) Reg->R5=Reg->R5-myAtoiFunction(expr);
}
// Eger sub reg,reg bir yapiysa
void subCalculateRegister(string expr,Registers *Reg,int RegValue)
{
		if(RegValue==1&&expr[1]=='1') Reg->R1=(Reg->R1)-(Reg->R1);
		if(RegValue==1&&expr[1]=='2') Reg->R1=Reg->R1-(Reg->R2);
		if(RegValue==1&&expr[1]=='3') Reg->R1=Reg->R1-(Reg->R3);
		if(RegValue==1&&expr[1]=='4') Reg->R1=Reg->R1-(Reg->R4);
		if(RegValue==1&&expr[1]=='5') Reg->R1=Reg->R1-(Reg->R5);
		
		if(RegValue==2&&expr[1]=='1') Reg->R2=Reg->R2-(Reg->R1);
		if(RegValue==2&&expr[1]=='2') Reg->R2=Reg->R2-(Reg->R2);
		if(RegValue==2&&expr[1]=='3') Reg->R2=Reg->R2-(Reg->R3);
		if(RegValue==2&&expr[1]=='4') Reg->R2=Reg->R2-(Reg->R4);
		if(RegValue==2&&expr[1]=='5') Reg->R2=Reg->R2-(Reg->R5);
		
		if(RegValue==3&&expr[1]=='1') Reg->R3=Reg->R3-(Reg->R1);
		if(RegValue==3&&expr[1]=='2') Reg->R3=Reg->R3-(Reg->R2);
		if(RegValue==3&&expr[1]=='3') Reg->R3=Reg->R3-(Reg->R3);
		if(RegValue==3&&expr[1]=='4') Reg->R3=Reg->R3-(Reg->R4);
		if(RegValue==3&&expr[1]=='5') Reg->R3=Reg->R3-(Reg->R5);
		
		if(RegValue==4&&expr[1]=='1') Reg->R4=Reg->R4-(Reg->R1);
		if(RegValue==4&&expr[1]=='2') Reg->R4=Reg->R4-(Reg->R2);
		if(RegValue==4&&expr[1]=='3') Reg->R4=Reg->R4-(Reg->R3);
		if(RegValue==4&&expr[1]=='4') Reg->R4=Reg->R4-(Reg->R4);
		if(RegValue==4&&expr[1]=='5') Reg->R4=(Reg->R4)-(Reg->R5);
		
				
		if(RegValue==5&&expr[1]=='1') Reg->R5=Reg->R5-(Reg->R1);
		if(RegValue==5&&expr[1]=='2') Reg->R5=Reg->R5-(Reg->R2);								
		if(RegValue==5&&expr[1]=='3') Reg->R5=Reg->R5-(Reg->R3);
		if(RegValue==5&&expr[1]=='4') Reg->R5=(Reg->R5)-(Reg->R4);
		if(RegValue==5&&expr[1]=='5') Reg->R5=Reg->R5-(Reg->R5);
}
// Eger add reg,constant bir yapiysa 
void addCalculateConstant(string expr,Registers *Reg,int flag)
{
		if(flag==1) Reg->R1=Reg->R1+myAtoiFunction(expr);
		if(flag==2) Reg->R2=Reg->R2+myAtoiFunction(expr);
		if(flag==3) Reg->R3=Reg->R3+myAtoiFunction(expr);
		if(flag==4) Reg->R4=Reg->R4+myAtoiFunction(expr);
		if(flag==5) Reg->R5=Reg->R5+myAtoiFunction(expr);
}
// Eger add reg,reg bir yapiysa
void addCalculateRegister(string expr,Registers *Reg,int RegValue)
{
		if(RegValue==1&&expr[1]=='1') Reg->R1=(Reg->R1)+(Reg->R1);
		if(RegValue==1&&expr[1]=='2') Reg->R1=Reg->R1+(Reg->R2);
		if(RegValue==1&&expr[1]=='3') Reg->R1=Reg->R1+(Reg->R3);
		if(RegValue==1&&expr[1]=='4') Reg->R1=Reg->R1+(Reg->R4);
		if(RegValue==1&&expr[1]=='5') Reg->R1=Reg->R1+(Reg->R5);
		
		if(RegValue==2&&expr[1]=='1') Reg->R2=Reg->R2+(Reg->R1);
		if(RegValue==2&&expr[1]=='2') Reg->R2=Reg->R2+(Reg->R2);
		if(RegValue==2&&expr[1]=='3') Reg->R2=Reg->R2+(Reg->R3);
		if(RegValue==2&&expr[1]=='4') Reg->R2=Reg->R2+(Reg->R4);
		if(RegValue==2&&expr[1]=='5') Reg->R2=Reg->R2+(Reg->R5);
		
		if(RegValue==3&&expr[1]=='1') Reg->R3=Reg->R3+(Reg->R1);
		if(RegValue==3&&expr[1]=='2') Reg->R3=Reg->R3+(Reg->R2);
		if(RegValue==3&&expr[1]=='3') Reg->R3=Reg->R3+(Reg->R3);
		if(RegValue==3&&expr[1]=='4') Reg->R3=Reg->R3+(Reg->R4);
		if(RegValue==3&&expr[1]=='5') Reg->R3=Reg->R3+(Reg->R5);
		
		if(RegValue==4&&expr[1]=='1') Reg->R4=Reg->R4+(Reg->R1);
		if(RegValue==4&&expr[1]=='2') Reg->R4=Reg->R4+(Reg->R2);
		if(RegValue==4&&expr[1]=='3') Reg->R4=Reg->R4+(Reg->R3);
		if(RegValue==4&&expr[1]=='4') Reg->R4=Reg->R4+(Reg->R4);
		if(RegValue==4&&expr[1]=='5') Reg->R4=(Reg->R4)+(Reg->R5);
		
				
		if(RegValue==5&&expr[1]=='1') Reg->R5=Reg->R5+(Reg->R1);
		if(RegValue==5&&expr[1]=='2') Reg->R5=Reg->R5+(Reg->R2);								
		if(RegValue==5&&expr[1]=='3') Reg->R5=Reg->R5+(Reg->R3);
		if(RegValue==5&&expr[1]=='4') Reg->R5=(Reg->R5)+(Reg->R4);
		if(RegValue==5&&expr[1]=='5') Reg->R5=Reg->R5+(Reg->R5);
}
// Eger jmp reg,constant bir yapiysa
void jmpAccordingRegister(string expr,Registers *Reg,int flag,ifstream *fr)
{
		
		string line;
		int i=0;
		

		
		if((flag==1&&Reg->R1==0)||
			(flag==2&&Reg->R2==0)||
			(flag==3&&Reg->R3==0)||
			(flag==4&&Reg->R4==0)||
			(flag==5&&Reg->R5==0))
		{
			(*fr).seekg(0, ios::beg );
		
			while(i<(myAtoiFunction(expr)-1))
			{
				getline((*fr),line,'\n');
				i++;
			}
		
		}
		
	
}
// Eger jmp,constant bir yapiysa
int jmpAccordingConstant(string word,Registers *Reg,ifstream *fr)
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

		(*fr).seekg(0, ios::beg);
		

		while(k<(myAtoiFunction(expr)-1))
		{
			getline((*fr),line,'\n');
			k++;
		}	
		return 1;
		
}
// Benim atoi fonksiyonum
int myAtoiFunction(string str)
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
int myPowFunction(int val1,int val2)
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
void printRegister(string word,Registers *Reg)
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
			
		  if(expr[0]=='R'||expr[0]=='r'&&expr[1]=='1') cout<<(Reg->R1)<<endl;		  
		  else if(expr[0]=='R'||expr[0]=='r'&&expr[1]=='2') cout<<(Reg->R2)<<endl;
		  else if(expr[0]=='R'||expr[0]=='r'&&expr[1]=='3') cout<<(Reg->R3)<<endl;
		  else if(expr[0]=='R'||expr[0]=='r'&&expr[1]=='4') cout<<(Reg->R4)<<endl;
		  else if(expr[0]=='R'||expr[0]=='r'&&expr[1]=='5') cout<<(Reg->R5)<<endl;
          else
		  {
		     cout<<myAtoiFunction(expr)<<endl;
		  }
		
}
void debugModePrint(string str,Registers *Reg)
{
	cout<<str<<"-";
	cout<<"R1= "<<Reg->R1<<","<<"R2= "<<Reg->R2<<","<<"R3= "<<Reg->R3<<","<<"R4= "<<Reg->R4<<","<<"R5= "<<Reg->R5<<endl;
}
