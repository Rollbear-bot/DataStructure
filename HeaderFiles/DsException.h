//
// Created by 13592 on 2019/10/31.
//

#ifndef DATASTRUCTURE_DSEXCEPTION_H
#define DATASTRUCTURE_DSEXCEPTION_H

#include <iostream>
#include <ctime>
#include <exception>
using namespace std;

//其他异常
class Ex: public exception{
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
class IndexOutException: public exception{
public:
    IndexOutException(){}
    /*
    void print(){
        cout << "IndexOutFlow!" << endl;
    }
     */
    const char * what() const throw(){
        return "IndexOutOfRange!";
    }
};

//NoFound异常
class NoFound: public exception{
public:
    NoFound(){}
    /*
    void print(){
        cout << "NoFound!" << endl;
    }
     */
    const char *what() const throw(){
        return "NoFound!";
    }
};

//存储溢出异常
class OverFlowException: public exception{
public:
    OverFlowException(){}
    /*
    void print(){
        cout << "OverFlow!" << endl;
    }
     */
    const char *what() const throw(){
        return "OverFlow!";
    }
};

//未初始化异常
class NullPointer: public exception{
public:
    NullPointer(){}
    /*
    void print(){
        cout << "NullPointer!" << endl;
    }
     */
    const char *what() const throw(){
        return "NullPointer!";
    }
};

#endif //DATASTRUCTURE_DSEXCEPTION_H