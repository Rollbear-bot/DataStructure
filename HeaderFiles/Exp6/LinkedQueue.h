//
// Created by 13592 on 2019/11/22.
/* 队列的链接实现
 * */

#ifndef DATASTRUCTURE_LINKEDQUEUE_H
#define DATASTRUCTURE_LINKEDQUEUE_H

#include "../Exp2/List.h"

template <class T>
class LinkedQueue{
public:
    //给定最大队列长来构造
    LinkedQueue(int maxLen){
        this->maxLen = maxLen;
        //初始化时队列为空
        this->data = List<T>(0);
    }

    //从数组构造
    LinkedQueue(int maxLen, T arr[], int lenOfArr){
        //用于初始化的数组长度大于队列长度时数据溢出
        if (lenOfArr > maxLen)throw OverFlowException();
        this->maxLen = maxLen;
        T temp;
        for(int index = 0; index < lenOfArr; index++){
            temp = arr[index];
            this->data.alter(index, temp);
        }
    }

    //拷贝构造函数
    LinkedQueue(LinkedQueue<T> &another){
        this->maxLen = another.maxLen;
        //单链表List的拷贝构造函数已定义，因此是安全的数据复制
        this->data = another.data;
    }

public:
    //进队列
    void enter(T item){
        if(isFull())throw OverFlowException();
        data.append(item);
    }

    //出队列：返回出队的元素值
    T& quit(){
        if(isEmpty())throw NullPointer();
        T temp = this->data.find(0);
        this->data.delByIndex(0);
        return temp;
    }

    //判空
    bool isEmpty(){ return data.isEmpty();}

    //判满
    bool isFull(){ return data.find(maxLen) == data.getLast();}

    //输出队列
    void printQueue(){ data.printList();}

    //队列清空
    void clear(){ data.clear();}

protected:
    List<T> data; //使用单链表来存储数据
    int maxLen; //最大队列长
};

#endif //DATASTRUCTURE_LINKEDQUEUE_H
