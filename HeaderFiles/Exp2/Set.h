// Created by @rollbear on 2020/2/17.
// 集合：链表实现

#ifndef DATASTRUCTURE_SET_H
#define DATASTRUCTURE_SET_H

#include "List.h"

template <class T>
class Set: public List<T>{
public:
    Set(): List<T>(){}

public:
    //重写插入函数：不允许添加重复的元素
    void append(T item){
        if(List<T>::inList(item)) return;
        else List<T>::append(item);
    }
};

#endif //DATASTRUCTURE_SET_H
