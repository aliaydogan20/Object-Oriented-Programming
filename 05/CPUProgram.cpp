/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CPUProgram.h"


void CPUProgram::ReadFile(string filename_) 
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
            
            str.push_back(tmp);
            cp.setPC(cp.getPC()+1);
            tmp.clear();
        }
      
                  
     }
    fr.close();
}
CPUProgram::CPUProgram()
{
    option=0;
    //Random filename
    filename="sort.txt";
    ReadFile(filename);
}
CPUProgram::CPUProgram(string filename_)
{
    filename=filename_;
    ReadFile(filename);
    //random filename
    option=0;
}

CPUProgram::CPUProgram(int option_)
{
    option=option_;
    filename="sort.txt";
}

string CPUProgram::operator[](int index)
{ 
    string b[1]={""};
    
    if(size()<=index)
    {
        cout<<"Wrong index error"<<endl;
        return b[0];
    }
    else
        return str[index]; 
}
// Vector size
int CPUProgram::size()
{
    
    return str.size();
}

// + operator overloading
CPUProgram& CPUProgram::operator +(const string line)
{
    
    this->str.push_back(line);

    return *this;    
    
}
// += operator overloading
CPUProgram& CPUProgram::operator +=(const string line)
{
    this->str.push_back(line);
    
    return *this;
}
// + operator overloading for 2 CPUProgram Object
CPUProgram& CPUProgram::operator +(CPUProgram& other)
{
    
    for(int i=0;i<other.size();i++)
    {
        str.push_back(other.str[i]);
    }
    
    return *this;
}
// == operator overloading
bool CPUProgram::operator ==(CPUProgram& other)
{
    if(str.size()==other.str.size())
        return true;
    else
        return false;
}
// <= operator overloading
bool CPUProgram::operator <=(CPUProgram& other)
{
    if(str.size()<=other.str.size())
        return true;
    else
        return false;
}
// > operator overloading
bool CPUProgram::operator >(CPUProgram& other)
{
    if(str.size()>other.str.size())
        return true;
    else
        return false;
}
// < operator overloading
bool CPUProgram::operator <(CPUProgram& other)
{
    if(str.size()<other.str.size())
        return true;
    else
        return false;
}

// >= operator overloading
bool CPUProgram::operator >=(CPUProgram& other)
{
    if(str.size()>=other.str.size())
        return true;
    else
        return false;
}

// -- operator overloading prefix
CPUProgram CPUProgram::operator --()
{
    str.pop_back();
    
    return *this;
}

// -- operator overloaidng postfix
CPUProgram CPUProgram::operator --(int ignore)
{
    CPUProgram temp=*this;
    
    str.pop_back();
    
    return temp;
}

// call operator 2,4 verildiyse 3. satirdan 5. satira kadar dondurur.
CPUProgram CPUProgram::operator ()(int x, int y)
{
    CPUProgram newProg;
    
    newProg.str.clear();
    
    if(x<0 || y>str.size())
    {
        cerr<<"Wrong index error"<<endl;
       
        return newProg;
    }
    
    for(int i=x;i<y+1;i++)
        newProg.str.push_back(str[i]);

    return newProg;
}

// << operator overloading
ostream& operator<<(ostream& output,const CPUProgram& obj)
{
    for(int i=0;i<obj.str.size();i++)
    output<<obj.str[i]<<endl;
    
    return output;
}

// gerekli elemani dondurur. Bir nevi [] operatorunun isini gorur. 
string CPUProgram::getAnElement(int index)const
{
    return str[index];
}
