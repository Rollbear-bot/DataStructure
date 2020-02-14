// 最小堆：数组实现
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
    //按层次序列输出最小堆中的元素
    void printLayerOrder(){ for(T it: data) cout << it << endl; }

protected:
    //建立最小堆
    void build(T arr[], int len){
        //首先建立完全二叉树，即把数据元素填充到数据域数组中
        this->last = len-1;
        for(int index = 0; index < len; index++){
            this->data[index] = arr[index];
        }
        //使用滑动算法建立最小堆
        int start = last/2; //找到最后一个节点的父节点
        while(start != 0){
            slide(start);
            start--;
        }
    }

    //滑动算法：检查索引为parent的位置是否需要下滑调整
    void slide(int parent){
        //已经到达堆底，退出递归
        if(parent/2 + 1 > MaxHeapDepth-1 || parent > MaxHeapDepth-1) return;
        //todo::滑动存在问题
        //递归判断是否需要滑动，直到堆底
        if(data[parent] > data[parent/2]) {
            //交换父节点和该子节点的值
            swap(parent, parent/2);
            //指针移动到原来的子节点的位置，继续检测是否需要滑动
            slide(parent/2);
        }
        if(data[parent] > data[parent/2 + 1]) {
            //交换父节点和该子节点的值
            swap(parent, parent/2 + 1);
            //指针移动到原来的子节点的位置，继续检测是否需要滑动
            slide(parent/2 + 1);
        }
    }

    //交换两个位置的数据值
    void swap(int indexA, int indexB){
        T temp = data[indexA];
        data[indexA] = data[indexB];
        data[indexB] = temp;
    }

    T data[MaxHeapDepth]; //数据域
    int last; //指向最小堆的最后一个有效位置
};

#endif //DATASTRUCTURE_HEAP_H
