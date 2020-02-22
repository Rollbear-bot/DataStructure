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
    //给定栈深来构造
    LinkedStack(int maxLen = MaxLen-1){
        //最大栈深为maxLen，栈空
        this->maxLen = maxLen;
        List<T> temp(0);
        this->data = temp;
        this->last = data.getLast();
    }

public:
    //进栈
    void push(T item){
        if(data.length() + 1 > maxLen)throw OverFlowException();
        data.append(item);
    }

    //出栈，函数返回出栈元素的值
    T pop(){
        if(isEmpty())throw NullPointer();
        //先用一个空间暂存出栈的元素
        T tmp = data.find(data.length() - 1)->data;
        data.removeByIndex(data.length() - 1); //释放空间
        return tmp; //将出栈的元素返回
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
    int getEleNum(){ return data.length();}

    //修改栈深
    void alterMaxLen(int ml){ this->maxLen = ml;}

protected:
    List<T> data;
    int maxLen; //栈深
    ListNode<T> *last; //指向栈顶的下一个位置（空位置），为序列结束标志
};

#endif //DATASTRUCTURE_LINKEDSTACK_H
