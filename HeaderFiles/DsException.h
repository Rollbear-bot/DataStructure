//
// Created by 13592 on 2019/10/31.
//

#ifndef DATASTRUCTURE_DSEXCEPTION_H
#define DATASTRUCTURE_DSEXCEPTION_H

#include <iostream>
#include <ctime>
using namespace std;

//其他异常
class Ex{
public:
    Ex(){}
    Ex(string info): info(info){}
    void print(){}
    void printInfo(){
        cout << "Exception: ";
        cout << info << endl; }

private:
    string info;
};

//下标溢出异常
class IndexOutException{
public:
    IndexOutException(){}
    void print(){
        cout << "IndexOutFlow!" << endl;
    }
};

//NoFound异常
class NoFound{
public:
    NoFound(){}
    void print(){
        cout << "NoFound!" << endl;
    }
};

//存储溢出异常
class OverFlowException{
public:
    OverFlowException(){}
    void print(){
        cout << "OverFlow!" << endl;
    }
};

//未初始化异常
class NullPointer{
public:
    NullPointer(){}
    void print(){
        cout << "NullPointer!" << endl;
    }
};

#endif //DATASTRUCTURE_DSEXCEPTION_H