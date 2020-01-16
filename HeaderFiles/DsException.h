//
// Created by 13592 on 2019/10/31.
//

#ifndef DATASTRUCTURE_DSEXCEPTION_H
#define DATASTRUCTURE_DSEXCEPTION_H

#include <iostream>
#include <ctime>
using namespace std;

//异常基类
class Ex{
public:
    Ex(){}
    virtual void print(){}
};

//下标溢出异常
class IndexOutException: public Ex{
public:
    IndexOutException(){}
    void print(){
        cout << "IndexOutFlow!" << endl;
    }
};

//NoFound异常
class NoFound: public Ex{
public:
    NoFound(){}
    void print(){
        cout << "NoFound!" << endl;
    }
};

//存储溢出异常
class OverFlowException: public Ex{
public:
    OverFlowException(){}
    void print(){
        cout << "OverFlow!" << endl;
    }
};

//未初始化异常
class NullPointer: public Ex{
public:
    NullPointer(){}
    void print(){
        cout << "NullPointer!" << endl;
    }
};

#endif //DATASTRUCTURE_DSEXCEPTION_H