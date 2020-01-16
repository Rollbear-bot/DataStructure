//
// Created by 13592 on 2019/10/31.
/* 队列：使用线性表实现
 * 2019.11.23 添加了队列清空接口clear
 * */

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

#include "../Exp1/LinearTable.h"

//队列的线性表实现
template <class T>
class Queue{
public:
    Queue(){ Queue(0);}

    //指定队列长度的构造函数
    Queue(int maxLen){
        LinearTable<T> temp(maxLen);
        this->data = temp;
    }

public:
    //从队头出队
    T quit(){
        T temp = data.find(0);
        data.delByIndex(0);
        return temp;
    }

    //从队尾入队
    void enter(T item){ data.append(item);}

    //输出队
    void printQueue(){ data.printTable();}

    //判空
    bool isEmpty(){ return data.isEmpty();}

    //判满
    bool isFull(){ return data.isFull();}

    //检索
    T &find(int index){ return data.find(index);}

    //清空队列
    void clear(){ this->data.clear();}

    //将队列中的元素序列输出为链表
    List<T> toList(){
        return this->data.toList();
    }

protected:
    LinearTable<T> data;
};

#endif //DATASTRUCTURE_QUEUE_H
