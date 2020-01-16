//
// Created by 13592 on 2019/11/13.
// ��С�ѣ��α�p236

#ifndef DATASTRUCTURE_MINHEAP_H
#define DATASTRUCTURE_MINHEAP_H

#define DefaultSize 10

#include "../Exp6/PQueue.h"
#include<iostream>
using namespace std;

//��С������
template <class T>
class MinHeap{
public:
    //���캯���������ն�
    MinHeap(int sz = DefaultSize);

    //���캯����ͨ��һ�����齨��
    MinHeap(T arr[], int n);

    //��������
    ~MinHeap(){delete []heap;}

public:
    //��x���뵽��С����
    bool Insert(const T &x);

    //ɾ���Ѷ��ϵ���СԪ��
    bool RemoveMin(T &x);

    //�п�
    bool IsEmpty()const{
        return currentSize == 0;
    }

    //����
    bool IsFull()const{
        return currentSize == maxHeapSize;
    }

    //�ÿն�
    void MakeEmpty(){
        currentSize = 0;
    }

    //�����
    void printHeap(){
        cout << "�ѵ�����Ϊ��" << endl;
        for(int index = 0; index < currentSize; index++){
            cout << heap[index] << " ";
        }
        cout << endl;
    }

    //�޸Ľ���ֵ���������ղ�������
    void alter(int index, T value){
        heap[index] = value;
    }

private:
    T *heap; //�����С����Ԫ�ص�����
    int currentSize; //��С���е�ǰԪ�صĸ���
    int maxHeapSize; //��С�����������Ԫ�ظ���
    void siftDown(int start, int m); //��start��m�»�������Ϊ��С��
    void siftUp(int start); //��start��0�ϻ�������Ϊ��С��
};

//------------------------���ⶨ��-----------------------------

//���캯����ͨ��һ�����齨��
template <class T>
MinHeap<T>::MinHeap(T *arr, int n) {
    maxHeapSize = (DefaultSize < n)? n: DefaultSize;
    heap = new T[maxHeapSize];
    if(heap == nullptr){
        cerr << "�Ѵ洢����ʧ�ܣ�" << endl;
        exit(1);
    }
    for(int i = 0; i < n; i++){
        heap[i] = arr[i];
    }
    //���ƶ����飬������ǰ��С
    currentSize = n;

    //���������λ�ã�����֧���
    int currentPos = (currentSize - 2)/2;

    //�Ե������������γɶ�
    while(currentPos >= 0){
        siftDown(currentPos, currentSize - 1); //�ֲ����������»�����
        currentPos--; //����ǰ��һ����֧���
    }
}

//��С�ѵ��»������㷨
template <class T>
void MinHeap<T>::siftDown(int start, int m) {
    //˽�к������ӽ��start��ʼ��mΪֹ���������±Ƚϣ������Ů��ֵС�ڸ��ڵ��ֵ��
    //��ؼ���С���ϸ����������²�Ƚϣ�������һ�����Ͼֲ�����Ϊ��С��
    //j��i������Ůλ��
    int i = start;
    int j = 2 * i + 1;
    T temp = heap[i];

    //����Ƿ����λ��
    while(j <= m){
        //��jָ������Ů�е�С��
        if(j < m && heap[j] > heap[j+1]) j++;

        //С��������
        if(temp <= heap[j])break;

            //����С�����ƣ�i��j�½�
        else{
            heap[i] = heap[j];
            i = j;
            j = 2* j +1;
        }
        //�ط�temp���ݴ��Ԫ��
        heap[i] = temp;
    }
}

//��С�ѵ��ϻ������㷨
template <class T>
void MinHeap<T>::siftUp(int start) {
    //˽�к������ӽ��start��ʼ�����0Ϊֹ���������ϱȽϣ������Ů��ֵС�ڸ��ڵ��ֵ
    //���ཻ�����������������µ���Ϊ��С�ѣ��ؼ���ȽϷ�"<="��T�ж���
    int j = start;
    int i = (j-1)/2;
    T temp = heap[j];

    //�ظ��ڵ�·������ֱ����
    while(j > 0){
        if(heap[i] <= temp)break; //���ڵ�ֵС��������
        else{
            //���ڵ�ֵ�󣬵���
            heap[j] = heap[i];
            j = i;
            i = (i-1)/2;
        }
        heap[j] = temp; //����
    }
}

//�ѵĲ����㷨
template <class T>
bool MinHeap<T>::Insert(const T &x) {
    //������������x���뵽��С����
    //����
    if(currentSize == maxHeapSize){
        cerr << "Heap Full!" << endl;
        return false;
    }
    heap[currentSize] = x; //����
    siftUp(currentSize); //���ϵ���
    currentSize++; //�Ѽ�����һ
    return true;
}

//�ѵ�ɾ���㷨
//ɾ���Ѷ��ϵ���СԪ�أ�����ȡ����Ԫ�ط���x��
template <class T>
bool MinHeap<T>::RemoveMin(T &x) {
    //�ѿգ�����false
    if(!currentSize){
        cout << "Heap empty!" << endl;
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize-1]; //���Ԫ�ز������ڵ�
    currentSize--;
    siftDown(0, currentSize-1); //�������µ���Ϊ��
    return true;
}

#endif //DATASTRUCTURE_MINHEAP_H