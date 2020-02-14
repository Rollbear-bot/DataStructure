// ��С�ѣ�����ʵ��
// Created by rollbear on 2020/1/16.

#ifndef DATASTRUCTURE_HEAP_H
#define DATASTRUCTURE_HEAP_H

#include <iostream>
using namespace std;

#define MaxHeapDepth 50

template <class T>
class Heap{
public:
    Heap(T arr[], int len){ build(arr, len); }

public:
    //��������������С���е�Ԫ��
    void printLayerOrder(){ for(T it: data) cout << it << endl; }

protected:
    //������С��
    void build(T arr[], int len){
        //���Ƚ�����ȫ����������������Ԫ����䵽������������
        this->last = len-1;
        for(int index = 0; index < len; index++){
            this->data[index] = arr[index];
        }
        //ʹ�û����㷨������С��
        int start = last/2; //�ҵ����һ���ڵ�ĸ��ڵ�
        while(start != 0){
            slide(start);
            start--;
        }
    }

    //�����㷨���������Ϊparent��λ���Ƿ���Ҫ�»�����
    void slide(int parent){
        //�Ѿ�����ѵף��˳��ݹ�
        if(parent/2 + 1 > MaxHeapDepth-1 || parent > MaxHeapDepth-1) return;
        //todo::������������
        //�ݹ��ж��Ƿ���Ҫ������ֱ���ѵ�
        if(data[parent] > data[parent/2]) {
            //�������ڵ�͸��ӽڵ��ֵ
            swap(parent, parent/2);
            //ָ���ƶ���ԭ�����ӽڵ��λ�ã���������Ƿ���Ҫ����
            slide(parent/2);
        }
        if(data[parent] > data[parent/2 + 1]) {
            //�������ڵ�͸��ӽڵ��ֵ
            swap(parent, parent/2 + 1);
            //ָ���ƶ���ԭ�����ӽڵ��λ�ã���������Ƿ���Ҫ����
            slide(parent/2 + 1);
        }
    }

    //��������λ�õ�����ֵ
    void swap(int indexA, int indexB){
        T temp = data[indexA];
        data[indexA] = data[indexB];
        data[indexB] = temp;
    }

    T data[MaxHeapDepth]; //������
    int last; //ָ����С�ѵ����һ����Чλ��
};

#endif //DATASTRUCTURE_HEAP_H
