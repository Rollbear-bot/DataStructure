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
    //����ջ��������
    LinkedStack(int maxLen = MaxLen-1){
        //���ջ��ΪmaxLen��ջ��
        this->maxLen = maxLen;
        List<T> temp(0);
        this->data = temp;
        this->last = data.getLast();
    }

public:
    //��ջ
    void push(T item){
        if(data.length() + 1 > maxLen)throw OverFlowException();
        data.append(item);
    }

    //��ջ���������س�ջԪ�ص�ֵ
    T pop(){
        if(isEmpty())throw NullPointer();
        //����һ���ռ��ݴ��ջ��Ԫ��
        T tmp = data.find(data.length() - 1)->data;
        data.removeByIndex(data.length() - 1); //�ͷſռ�
        return tmp; //����ջ��Ԫ�ط���
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
    int getEleNum(){ return data.length();}

    //�޸�ջ��
    void alterMaxLen(int ml){ this->maxLen = ml;}

protected:
    List<T> data;
    int maxLen; //ջ��
    ListNode<T> *last; //ָ��ջ������һ��λ�ã���λ�ã���Ϊ���н�����־
};

#endif //DATASTRUCTURE_LINKEDSTACK_H
