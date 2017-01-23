/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: Ali
 *
 * Created on 27 Ekim 2016 Perşembe, 00:31
 */


#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "Memory.h"

#ifndef CPU_H
#define CPU_H

using namespace std;

class CPU
{
    public:
    	//Constructors
        CPU();
        CPU(int option_);
        CPU(const int Reg1,const int Reg2,const int Reg3,const int Reg4,const int Reg5,const int PrC,const int halted_,int option_);
        CPU(const int Reg1,const int Reg2,const int Reg3,const int Reg4,const int Reg5,const int PrC);
        CPU(const int Reg1,const int Reg2,const int Reg3,const int Reg4,const int Reg5);
        
        // Getter
        int getR1()const{return R1;}
        int getR2()const{return R2;}
        int getR3()const{return R3;}
        int getR4()const{return R4;}
        int getR5()const{return R5;}
        int getPC()const{return PC;}
        int getHalted()const{return halt;}
        int getOption()const{return option;};
        
        //Setter
        void setR1(const int Reg1){R1=Reg1;}
        void setR2(const int Reg2){R2=Reg2;}
        void setR3(const int Reg3){R3=Reg3;}
        void setR4(const int Reg4){R4=Reg4;}
        void setR5(const int Reg5){R5=Reg5;}
        void setPC(const int PrC){PC=PrC;}
        void setHalted(const int halt_){halt=halt_;}
        void setOption(const int option_){option=option_;}

        bool halted();
        void print();
        void execute(string instruction, Memory& myMemory);
        //Other functions for execute
        int parsingFunctionInstruction(string word);
        int parsingRemainderConstant(string word,int selection);
        void parsingRemainderRegister(string word,int RegValue,int selection);
        // New functions
        /* MOV address,reg tarzi bir yapiysa */
        void parsingAddressToRegisterOrConstant(string word,Memory& myMemory);
        // Eger instruction reg,address tarzi bir yapiysa bu fonksiyon devreye girer.
        int  parsingRemainderAddress(string word,int value,int selection,Memory& myMemory);
        // Eger move reg,adres bir yapiysa
        void moveCalculateRegisterToAddress(string word,int flag,Memory& myMemory);
        // Eger move address,reg tarzi bir yapiysa
        void moveCalculateAddressToRegister(string expr,string expr2,Memory& myMemory);
        // Eger move address,constant bir yapiysa 
        void moveCalculateAddressToConstant(string expr,string expr2,Memory& myMemory);
        // Eger sub reg,address bir yapiysa
        void subCalculateRegisterToAddress(string word,int flag,Memory& myMemory);
        // Eger add reg,address bir yapiysa
        void addCalculateRegisterToAddress(string word,int flag,Memory& myMemory);
        // Yeni instruction  jpn R1,32 eger R1 0 dan kucuk veya esitse 32 ye git 
        void jpnInstruction(string expr,int flag);
        
        void moveCalculateConstant(string expr,int flag);
        void moveCalculateRegister(string expr,int flag);
        void subCalculateConstant(string expr,int flag);
        void subCalculateRegister(string expr,int flag);
        void addCalculateConstant(string expr,int flag);
        void addCalculateRegister(string expr,int flag);
        void jmpAccordingRegister(string expr,int flag);
        int jmpAccordingConstant(string expr);
        void printInstruction(string expr,Memory &myMemory);
        
        // My math library
        int myAtoiFunction(string str);
        int myPowFunction(int val1,int val2);
        
    private:
        int R1,R2,R3,R4,R5;
        int PC;
        int option;
        int halt;
};

#endif /* CPU_H */
