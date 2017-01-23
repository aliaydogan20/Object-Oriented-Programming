/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgram.h
 * Author: Ali
 *
 */


#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<vector>
#include "CPU.h"

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

using namespace std;

class CPUProgram
{
    public:
    	// CPUProgram Functions
        void ReadFile(string filename_);
        CPUProgram();
        CPUProgram(string filename_);
        CPUProgram(int option);
        string operator[](int index);
        
        // + operatoru 2 parametre alamiyor.Almasi icin friend olmasi gerekiyordu.
        // Bu nedenle asagidaki gibi yaptim.
        //friend CPUProgram operator +(const CPUProgram& myProg,const string line);
       
        CPUProgram& operator +(const string line);
        CPUProgram& operator +=(const string line);
        CPUProgram& operator +(CPUProgram& other);
        bool operator==(CPUProgram& other);
        bool operator<=(CPUProgram& other);
        bool operator>(CPUProgram& other);
        bool operator<(CPUProgram& other);
        bool operator>=(CPUProgram& other);
        CPUProgram operator--();
        CPUProgram operator--(int ignore);
        CPUProgram operator()(int x,int y);
        friend ostream& operator<<(ostream &output,const CPUProgram& obj);
        int size();
        // Getters and setters
        string getAnElement(int index)const;
        int getOption()const{return option;}
        void setOption(int op){option=op;}
        string getFilename()const{return filename;}
        void setFileName(string filename_){filename=filename_;}
    
    private:  
        string filename;
        vector <string> str;
        CPU cp;
        int option;
};


#endif /* CPUPROGRAM_H */
