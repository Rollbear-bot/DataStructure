//
// Created by 13592 on 2019/11/13.
// 最小堆：课本p236

#ifndef DATASTRUCTURE_MINHEAP_H
#define DATASTRUCTURE_MINHEAP_H

#define DefaultSize 10

#include "../Exp6/PQueue.h"
#include<iostream>
using namespace std;

//最小堆容器
template <class T>
class MinHeap{
public:
    //构造函数：建立空堆
    MinHeap(int sz = DefaultSize);

    //构造函数：通过一个数组建堆
    MinHeap(T arr[], int n);

    //析构函数
    ~MinHeap(){delete []heap;}

public:
    //将x插入到最小堆中
    bool Insert(const T &x);

    //删除堆顶上的最小元素
    bool RemoveMin(T &x);

    //判空
    bool IsEmpty()const{
        return currentSize == 0;
    }

    //判满
    bool IsFull()const{
        return currentSize == maxHeapSize;
    }

    //置空堆
    void MakeEmpty(){
        currentSize = 0;
    }

    //输出堆
    void printHeap(){
        cout << "堆的内容为：" << endl;
        for(int index = 0; index < currentSize; index++){
            cout << heap[index] << " ";
        }
        cout << endl;
    }

    //修改结点的值：索引依照层次序遍历
    void alter(int index, T value){
        heap[index] = value;
    }

private:
    T *heap; //存放最小堆中元素的数组
    int currentSize; //最小堆中当前元素的个数
    int maxHeapSize; //最小堆中最多允许元素个数
    void siftDown(int start, int m); //从start到m下滑调整成为最小堆
    void siftUp(int start); //从start到0上滑调整成为最小堆
};

//------------------------类外定义-----------------------------

//构造函数：通过一个数组建堆
template <class T>
MinHeap<T>::MinHeap(T *arr, int n) {
    maxHeapSize = (DefaultSize < n)? n: DefaultSize;
    heap = new T[maxHeapSize];
    if(heap == nullptr){
        cerr << "堆存储分配失败！" << endl;
        exit(1);
    }
    for(int i = 0; i < n; i++){
        heap[i] = arr[i];
    }
    //复制堆数组，建立当前大小
    currentSize = n;

    //找最初调整位置：最后分支结点
    int currentPos = (currentSize - 2)/2;

    //自底向上逐步扩大形成堆
    while(currentPos >= 0){
        siftDown(currentPos, currentSize - 1); //局部自上向下下滑调整
        currentPos--; //再向前换一个分支结点
    }
}

//最小堆的下滑调整算法
template <class T>
void MinHeap<T>::siftDown(int start, int m) {
    //私有函数：从结点start开始到m为止，自上向下比较，如果子女的值小于父节点的值，
    //则关键码小的上浮，继续向下层比较，这样将一个集合局部调整为最小堆
    //j是i的左子女位置
    int i = start;
    int j = 2 * i + 1;
    T temp = heap[i];

    //检查是否到最后位置
    while(j <= m){
        //让j指向两子女中的小者
        if(j < m && heap[j] > heap[j+1]) j++;

        //小则不做调整
        if(temp <= heap[j])break;

            //否则小者上移，i，j下降
        else{
            heap[i] = heap[j];
            i = j;
            j = 2* j +1;
        }
        //回放temp中暂存的元素
        heap[i] = temp;
    }
}

//最小堆的上滑调整算法
template <class T>
void MinHeap<T>::siftUp(int start) {
    //私有函数：从结点start开始到结点0为止，自下向上比较，如果子女的值小于父节点的值
    //则互相交换，这样将集合重新调整为最小堆，关键码比较符"<="在T中定义
    int j = start;
    int i = (j-1)/2;
    T temp = heap[j];

    //沿父节点路径向上直到根
    while(j > 0){
        if(heap[i] <= temp)break; //父节点值小，不调整
        else{
            //父节点值大，调整
            heap[j] = heap[i];
            j = i;
            i = (i-1)/2;
        }
        heap[j] = temp; //回送
    }
}

//堆的插入算法
template <class T>
bool MinHeap<T>::Insert(const T &x) {
    //公共函数：将x插入到最小堆中
    //堆满
    if(currentSize == maxHeapSize){
        cerr << "Heap Full!" << endl;
        return false;
    }
    heap[currentSize] = x; //插入
    siftUp(currentSize); //向上调整
    currentSize++; //堆计数加一
    return true;
}

//堆的删除算法
//删除堆顶上的最小元素，并将取出的元素放入x中
template <class T>
bool MinHeap<T>::RemoveMin(T &x) {
    //堆空，返回false
    if(!currentSize){
        cout << "Heap empty!" << endl;
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize-1]; //最后元素补到根节点
    currentSize--;
    siftDown(0, currentSize-1); //自上向下调整为堆
    return true;
}

#endif //DATASTRUCTURE_MINHEAP_H