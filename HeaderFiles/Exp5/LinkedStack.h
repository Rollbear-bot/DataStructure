//
// Created by 13592 on 2019/11/6.
/* 链栈：使用单链表实现
 * */

#ifndef DATASTRUCTURE_LINKEDSTACK_H
#define DATASTRUCTURE_LINKEDSTACK_H

#include "../Exp2/List.h"

template <class T>
class LinkedStack{
public:
    //默认构造函数
    LinkedStack(){
        LinkedStack(0);
    }

    //给定栈深来构造
    LinkedStack(int maxLen){
        //最大栈深为maxLen，栈空
        this->maxLen = maxLen;
        List<T> temp(0);
        this->data = temp;
        this->last = data.getLast();
    }

public:
    //进栈
    void push(T item){
        if(data.getLen() + 1 > maxLen)throw OverFlowException();
        data.append(item);
    }

    //出栈，函数返回出栈元素的值
    T pop(){
        if(isEmpty())throw NullPointer();
        T tmp = data.find(data.getLen()-1)->data;
        data.delByIndex(data.getLen() - 1);
        return tmp;
    }

    //判空
    bool isEmpty(){ return data.isEmpty();}

    //判满
    bool isFull(){ return data.find(maxLen) == last;}

    //输出栈
    void printStack(){ data.printList();}

    //栈置空
    void clear(){ data.clear();}

    //获取栈深
    int getMaxLen(){ return maxLen;}

    //获取当前栈中元素个数
    int getEleNum(){ return data.getLen();}

    //修改栈深
    void alterMaxLen(int maxLen){ this->maxLen = maxLen;}

protected:
    List<T> data;
    int maxLen; //栈深
    ListNode<T> *last; //指向栈顶的下一个位置（空位置），为结束标志
};

#endif //DATASTRUCTURE_LINKEDSTACK_H
