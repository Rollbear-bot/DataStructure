//
// Created by 13592 on 2019/11/27.
// 搜索表：继承自数据表（来自课本）

#ifndef DATASTRUCTURE_SEARCHLIST_H
#define DATASTRUCTURE_SEARCHLIST_H

#include "dataList.h"

//搜索表：继承了dataList，并增加了成员函数Search()
//需要声明为dataNode的友元类
template <class E, class K>
class searchList: public dataList<E, K>{
public:
    //构造函数
    searchList(int sz = defaultSize): dataList<E, K>(sz){}
    virtual int SeqSearch(const K x)const;
    virtual int SeqSearch(const K k, int loc)const; //递归搜索算法
};

//------------------以下为类外定义------------------------

//使用监视哨的顺序搜索算法
template <class E, class K>
int searchList<E, K>::SeqSearch(const K x) const {
    //在搜索表searchList中顺序搜索其关键码为x的数据元素，
    //要求数据元素在表中从下标0开始存放，
    //第CurrentSize号位置作为控制搜索过程自动结束的“监视哨”使用。
    //若找到则函数返回该元素在表中的位置i，否则返回CurrentSize。
    Element[CurrentSize].key = x;
    //将x设置为监视哨
    int i =0;
    while (Element[i].key != x)i++; //从前往后顺序搜索
    return i+1;
}

//顺序搜索的递归算法
//调用时需要设置 int loc=1; int Poc = SeqSearch(x, loc);
template <class E, class K>
int searchList<E, K>::SeqSearch(const K x, int loc) const {
    if(loc > CurrentSize)return 0; //搜索不成功
    else if(Element[loc-1].key == x)
}

#endif //DATASTRUCTURE_SEARCHLIST_H
