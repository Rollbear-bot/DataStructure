//
// Created by 13592 on 2019/11/15.
// 多项式运算

#ifndef DATASTRUCTURE_POLYCAL_H
#define DATASTRUCTURE_POLYCAL_H

#include "../Exp2/List.h"
#include "PolyByList.h"

template <class T>
class PolyCal{
public:
    PolyCal(){}

public:
    //将数据域中的两条多项式（通过索引来选择）相加，返回运算结果多项式的引用
    static PolyByList<T> &add(int index1, int index2){
        return data.find(index1)->data + data.find(index2)->data;
    }

    //将数据域中的两条多项式（通过索引来选择）相减，返回引用
    static PolyByList<T> &sub(int index1, int index2){
        return data.find(index1)->data - data.find(index2)->data;
    }

    //输出所有已保存的多项式
    static void printPolys(){
        for(int index = 0; index < last; index++){
            cout << index << ": ";
            data.find(index)->data.printPoly();
            cout << endl;
        }
    }

private:
    //数据域：存放要进行运算的多项式
    static List<PolyByList<T>> data;
    static int last; //last指向最后一个元素的下一个位置
};

//静态成员的初始化
template <class T>
List<PolyByList<T>> PolyCal<T>::data = List<PolyByList<T>>();

template <class T>
int PolyCal<T>::last = 0;

#endif //DATASTRUCTURE_POLYCAL_H
