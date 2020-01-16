//
// Created by 13592 on 2019/11/27.
// 有序顺序表：继承自搜索表

#ifndef DATASTRUCTURE_SORTEDLIST_H
#define DATASTRUCTURE_SORTEDLIST_H

#include "searchList.h"

//有序顺序表：需要声明为dataNode的友元类
template <class E, class K>
class SortedList: public searchList<E, K>{
public:
    //构造函数
    SortedList(int sz = 100): searchList<E, K>(sz){}

    //析构函数
    ~SortedList(){}

    //顺序搜索
    int SequentSearch(const K x)const;

    //折半搜索
    int BinarySearch(const K x)const;

    //有序插入
    bool Insert(const E &el);

    //定位第一个
    int Begin(){
        return (CurrentSize == 0)? 0: 1;
    }

    //定位下一个
    int Next(int i){
        return (i>=1 && i <= CurrentSize)? i+1: 0;
    }
};

//----------------以下为类外定义-------------------

//有序顺序表的顺序搜索算法
template <class E, class K>
int SortedList<E, K>::SequentSearch(const K x) const {
    //顺序搜索关键码为x的数据元素
    for(int i = 1; i <= CurrentSize; i++){
        //搜索成功，停止搜索
        if(Element[i-1].key == x)return i;
        //搜索不成功，停止搜索
        else if(Element[i-1].key > x)break;
    }
    //顺序搜索失败
    return 0;
}

//有序顺序表的折半搜索算法
template <class E, class K>
int SortedList<E,K>::BinarySearch(const K x) const {
    //迭代算法
    int high = CurrentSize-1, low =0, mid;
    while (low<=high){
        mid = (low + high)/2;
        if(x > Element[mid].key)low = mid+1;
        else if(x<Element[mid].key)high = mid-1;
            else return mid+1;
    }
    return 0; //搜索失败
}

#endif //DATASTRUCTURE_SORTEDLIST_H