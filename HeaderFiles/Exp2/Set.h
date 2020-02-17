// Created by @rollbear on 2020/2/17.
// ���ϣ�����ʵ��

#ifndef DATASTRUCTURE_SET_H
#define DATASTRUCTURE_SET_H

#include "List.h"

template <class T>
class Set: public List<T>{
public:
    Set(): List<T>(){}

public:
    //��д���뺯��������������ظ���Ԫ��
    void append(T item){
        if(List<T>::inList(item)) return;
        else List<T>::append(item);
    }
};

#endif //DATASTRUCTURE_SET_H
