/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPUProgram.h
 * Author: Ali
 *
 * Created on 27 Ekim 2016 Perşembe, 01:13
 */


#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include "CPU.h"

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

using namespace std;

class CPUProgram
{
    public:
    	// CPUProgram Functions
        void readFile(string filename_);
        CPUProgram();
        CPUProgram(string filename_);
        CPUProgram(int option);
        string getLine(int PC_);
        int size();
        // Getters and setters
        int getOption()const{return option;}
        void setOption(int op){option=op;}
        int getSize()const{return sizeLine;}
        void setSize(const int sizeLine_){sizeLine=sizeLine_;}
        string getFilename()const{return filename;}
        void setFileName(string filename_){filename=filename_;}
        int getSizeLine()const{return sizeLine;}
        void setSizeLine(const int sizeLine_){sizeLine=sizeLine_;}
    private:  
        string filename;
        string str[200];
        CPU cp;
        int sizeLine;
        int option;
};

#endif /* CPUPROGRAM_H */
