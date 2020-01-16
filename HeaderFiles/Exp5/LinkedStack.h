//
// Created by 13592 on 2019/11/6.
/* ��ջ��ʹ�õ�����ʵ��
 * */

#ifndef DATASTRUCTURE_LINKEDSTACK_H
#define DATASTRUCTURE_LINKEDSTACK_H

#include "../Exp2/List.h"

template <class T>
class LinkedStack{
public:
    //Ĭ�Ϲ��캯��
    LinkedStack(){
        LinkedStack(0);
    }

    //����ջ��������
    LinkedStack(int maxLen){
        //���ջ��ΪmaxLen��ջ��
        this->maxLen = maxLen;
        List<T> temp(0);
        this->data = temp;
        this->last = data.getLast();
    }

public:
    //��ջ
    void push(T item){
        if(data.getLen() + 1 > maxLen)throw OverFlowException();
        data.append(item);
    }

    //��ջ���������س�ջԪ�ص�ֵ
    T pop(){
        if(isEmpty())throw NullPointer();
        T tmp = data.find(data.getLen()-1)->data;
        data.delByIndex(data.getLen() - 1);
        return tmp;
    }

    //�п�
    bool isEmpty(){ return data.isEmpty();}

    //����
    bool isFull(){ return data.find(maxLen) == last;}

    //���ջ
    void printStack(){ data.printList();}

    //ջ�ÿ�
    void clear(){ data.clear();}

    //��ȡջ��
    int getMaxLen(){ return maxLen;}

    //��ȡ��ǰջ��Ԫ�ظ���
    int getEleNum(){ return data.getLen();}

    //�޸�ջ��
    void alterMaxLen(int maxLen){ this->maxLen = maxLen;}

protected:
    List<T> data;
    int maxLen; //ջ��
    ListNode<T> *last; //ָ��ջ������һ��λ�ã���λ�ã���Ϊ������־
};

#endif //DATASTRUCTURE_LINKEDSTACK_H
