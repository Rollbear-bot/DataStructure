// Created by 13592 on 2019/10/31.
/* 2019.11.23 ����˱�ϲ�����add
 * 2019.11.26 �����ӵ�����List����Ĺ��캯��
 * 2019.11.27 �޸�Ԫ�ؽӿ�alter���ڻ��Զ�����βָ��last
 * 2019.11.30 �����ӿڣ�swap���������������ֵ
 * 2019.12.1  �������ڸ������������е���delete�ͷ�data�������Ұָ������
 * */

#ifndef DATASTRUCTURE_LINEARTABLE_H
#define DATASTRUCTURE_LINEARTABLE_H

#define MaxLen 50

#include <iostream>
#include "../DsException.h"
#include "../Exp2/List.h"
using namespace std;

//���Ա��˳��ʵ��
template <class T>
class LinearTable{
public:
    //�±����������
    T &operator[](int index){
        return *find(index);
    }


    //ָ�����Ĺ��캯��
    LinearTable(int maxLen = MaxLen-1){
        if(maxLen >= MaxLen)throw OverFlowException();
        this->max = maxLen;
    }

    //�����鹹��
    LinearTable(int maxLen, int arrLen, T arr[]){
        if(maxLen >= MaxLen)throw OverFlowException();
        if(arrLen>maxLen)throw OverFlowException();
        this->max = maxLen;
        this->last = arrLen;
        for(int index = 0; index < arrLen; index++){
            data[index] = arr[index];
        }
    }


    //�������캯��
    LinearTable(LinearTable& another){
        this->max = another.max;
        this->last = another.last;
        for(int index = 0; index < last; index++){
            this->data[index] = another.data[index];
        }
    }

    //��������
    ~LinearTable(){
        //delete[] data;
    }

public:
    //��˳����е�Ԫ���������Ϊ����
    List<T> toList(){
        List<T> lt(0);
        for(int index = 0; index < this->last; index++){
            lt.append(this->data[index]);
        }
        return lt;
    }

    //׷��һ��Ԫ�ص���β
    void append(T item){
        if(last+1 > max)throw IndexOutException();
        data[last] = item;
        last++;
    }


    //����Ԫ���Ƿ��ڱ���
    bool inTable(T item){
        return locate(item) != -1;
    }


    //�±귽ʽɾ��Ԫ��
    void delByIndex(int index){
        for(int tra = index; tra < last; tra++){
            data[tra] = data[tra+1];
        }
        last--;
    }

    //����Ԫ�أ�����ʧ�ܷ���-1
    int locate(T item){
        for(int index = 0; index <= max; index++){
            if(data[index] == item)return index;
        }
        return -1;
    }

    //ʹ���±����
    T& find(int index){
        if(index > last)throw IndexOutException();
        return data[index];
    }

    //���룺��Ԫ�طŵ�ָ�����±꣬��λ�õ�ԭԪ�ؼ���������Ԫ�غ���һ����λ
    void insert(int index, T value){
        if(last+1 > max)throw IndexOutException();
        for(int temp = last; temp > index; temp--){
            data[temp] = data[temp-1];
        }
        data[index] = value;
        last++;
    }

    //�����
    void printTable(){
        if(isEmpty())cout << "Empty Table!" << endl;
        for(int index = 0; index < last; index++){
            cout << data[index] << " ";
        }
        cout << endl;
    }

    //�ϲ������ڶ������ӵ���ǰ��β�����������±�
    LinearTable<T> &add(LinearTable<T> &another){
        //�±����󳤶�Ϊ������󳤶�֮��
        LinearTable<T> sln(this->max + another.getMax());
        //���Ʊ���Ԫ��ֵ���±�
        for(int index = 0; index < this->length() + another.length(); index++){
            if(index < this->length()) sln.alter(index, this->data[index]);
            else sln.alter(index, another.find(index - this->length()));
        }
        return sln;
    }

    //�޸�ĳ���ֵ
    void alter(int index, T value) {
        data[index] = value;
        if(this->last <= index)last = index + 1;
    }

    //�������������ֵ
    void swap(int indexA, int indexB){
        T temp = find(indexA);
        alter(indexA, find(indexB));
        alter(indexB, temp);
    }

    //��ձ�
    void clear() { this->last = 0;}

    bool isEmpty() { return (last == 0);}
    bool isFull() { return (last == max);}
    int length(){ return this->last;}
    int getMax(){ return this->max;}

protected:
    T data[MaxLen]; //���ݿռ�
    int last = 0; //���һ����Ч���ݵ�Ԫ����һ��λ�ã���Ǳ�β���������Ч����
    int max; //��󳤶�
};

#endif //DATASTRUCTURE_LINEARTABLE_H
