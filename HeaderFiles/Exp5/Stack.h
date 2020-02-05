//
// Created by 13592 on 2019/11/1.
/* 栈：使用顺序表实现
 * */

#pragma once
#include<iostream>
#include "../Exp1/LinearTable.h"

using namespace std;

template <class T>
class Stack{
public:
    //无参的构造函数
    Stack(){ Stack(0);}

    //指定栈深来构造
    Stack(int maxLen){
        LinearTable<T> temp(maxLen);
        this->data = temp;
    }

    //拷贝构造函数
    Stack(const Stack<T> &another){
        this->data = another.data;
    }

public:
    //出栈
    T pop(){
        T tmp = data.find(data.getLast() - 1);
        data.delByIndex(data.getLast() - 1);
        return tmp;
    }

    //入栈
    void push(T item){ data.append(item);}

    //输出栈的元素
    void printStack(){ data.printTable();}

    //检索
    T& find(int index){ return data.find(index);}

    //判空
    bool isEmpty(){ return data.isEmpty();}

    //判满
    bool isFull(){ return data.isFull();}

    //清空栈
    void clear(){ data.clear();}

    //定位元素的下标，未找到则返回-1
    int locate(T item){ return data.locate(item);}

    //获取栈深
    int getMaxLen(){ return data.getMax();}

    //获取当前栈中元素个数
    int getEleNum(){ return data.getLast();}

    //将栈中的元素序列输出为链表
    List<T> toList(){
        return this->data.toList();
    }

    //获取栈顶
    T getTop(){
        return find(getEleNum()-1);
    }

protected:
    LinearTable<T> data;
};