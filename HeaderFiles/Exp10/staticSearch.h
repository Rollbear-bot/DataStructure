//
// Created by 13592 on 2019/11/25.
/* 静态搜索表：使用线性表实现
 * 2019.11.25 添加查找方式：顺序查找、二分查找
 * */

#ifndef DATASTRUCTURE_STATICSEARCH_H
#define DATASTRUCTURE_STATICSEARCH_H

#include "../Exp1/LinearTable.h"

template <class T>
class StaticSrhTable: public LinearTable<T>{
public:
    //应当在构造函数中完成排序
    //在构造函数中初始化父类LinearTable
    StaticSrhTable(int maxLen): LinearTable<T>(maxLen){}
    StaticSrhTable(int maxLen, int arrLen, T arr[]):
        LinearTable<T>(maxLen, arrLen, arr){ insertSort(); }

    //拷贝构造函数：使用另一个对象来初始化父类
    StaticSrhTable(StaticSrhTable<T> &another):
        LinearTable<T>(another.getMax(), another.getMax(), another.data){}

public:
    //顺序查找：返回索引
    int orderSearch(T item){
        for(int index = 0; index < LinearTable<T>::last; index++){
            if(LinearTable<T>::data[index] == item)return index;
        }
        throw NoFound();
    }

    //二分查找：返回索引
    int binarySearch(T item){
        insertSort();
        int sln = 0;
        int start = 0;
        int end = LinearTable<T>::last-1;
        int mid = end/2;
        bool found = false;
        while (true){
            if(LinearTable<T>::data[mid] == item){
                //已找到，退出
                sln = mid;
                found = true;
                break;
            }
            if(LinearTable<T>::data[end] == item){
                //已找到，退出
                sln = end;
                found = true;
                break;
            }
            //未找到，搜索结束，退出
            if(start == mid || end == mid)break;
            if(item < LinearTable<T>::data[mid]){
                //搜索范围缩小为左侧
                end = mid;
                mid = end/2;
            }else {
                //搜索范围缩小为右侧
                start = mid;
                mid = (start + end)/2;
            }
        }//end while
        if(!found)throw NoFound();
        return sln;
    }

public:
    //排序函数尽量不在类外调用
    //插入排序：从小到大
    void insertSort(){
        int i, j, k;
        T temp;
        for(int i = 0; i < this->last-1; i++){
            k = i;
            for(int j = i + 1; j < this->last; j++){
                if(LinearTable<T>::data[k] > LinearTable<T>::data[j]) k = j;
            }
            //交换索引为i和k的元素的值
            temp = LinearTable<T>::data[i];
            LinearTable<T>::data[i] = LinearTable<T>::data[k];
            LinearTable<T>::data[k] = temp;
        }
    }

    /*
    //归并排序：使用递归
    void mergeSort(){
        int i;
        T temp;
        int mid = (last-1)/2;
    }
     */
};

#endif //DATASTRUCTURE_STATICSEARCH_H
