//
// Created by 13592 on 2019/11/22.
/* ���е�����ʵ��
 * */

#ifndef DATASTRUCTURE_LINKEDQUEUE_H
#define DATASTRUCTURE_LINKEDQUEUE_H

#include "../Exp2/List.h"

template <class T>
class LinkedQueue{
public:
    //���������г�������
    LinkedQueue(int maxLen){
        this->maxLen = maxLen;
        //��ʼ��ʱ����Ϊ��
        this->data = List<T>(0);
    }

    //�����鹹��
    LinkedQueue(int maxLen, T arr[], int lenOfArr){
        //���ڳ�ʼ�������鳤�ȴ��ڶ��г���ʱ�������
        if (lenOfArr > maxLen)throw OverFlowException();
        this->maxLen = maxLen;
        T temp;
        for(int index = 0; index < lenOfArr; index++){
            temp = arr[index];
            this->data.alter(index, temp);
        }
    }

    //�������캯��
    LinkedQueue(LinkedQueue<T> &another){
        this->maxLen = another.maxLen;
        //������List�Ŀ������캯���Ѷ��壬����ǰ�ȫ�����ݸ���
        this->data = another.data;
    }

public:
    //������
    void enter(T item){
        if(isFull())throw OverFlowException();
        data.append(item);
    }

    //�����У����س��ӵ�Ԫ��ֵ
    T& quit(){
        if(isEmpty())throw NullPointer();
        T temp = this->data.find(0);
        this->data.delByIndex(0);
        return temp;
    }

    //�п�
    bool isEmpty(){ return data.isEmpty();}

    //����
    bool isFull(){ return data.find(maxLen) == data.getLast();}

    //�������
    void printQueue(){ data.printList();}

    //�������
    void clear(){ data.clear();}

protected:
    List<T> data; //ʹ�õ��������洢����
    int maxLen; //�����г�
};

#endif //DATASTRUCTURE_LINKEDQUEUE_H
