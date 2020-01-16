//
// Created by 13592 on 2019/11/27.
// 静态搜索表：课本p298

#ifndef DATASTRUCTURE_DATALIST_H
#define DATASTRUCTURE_DATALIST_H

#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int defaultSize = 100;

//提前声明类
template <class E, class K>
class dataList;
template <class E, class K>
class searchList;
template <class E, class K>
class SortedList;

//数据表中结点类的定义
template <class E, class K>
class dataNode{
    //声明友元类为dataList
    friend class dataList<E, K>;
    //声明searchList为友元类
    friend class searchList<E, K>;
    //声明SortedList为友元类
    friend class SortedList<E, K>;
public:
    //构造函数
    dataNode(const K x): key(x) {}

    //读取关键码
    K getKey() const { return key;}

    //修改关键码
    void setKey(K k){ key = k;}

private:
    K key; //关键码域
    E other; //其他域（已修正，添加变量类型E）
};

//数据表定义
template <class E, class K>
class dataList{
public:


    dataList(int sz = defaultSize): ArraySize(sz), CurrentSize(0){
        Element = new dataNode<E, K>[sz];
        assert(Element != NULL);
    }

    //复制构造函数
    dataList(dataList<E, K> &R);

    //析构函数
    virtual ~dataList(){ delete []Element;}

    //求表的长度
    virtual int Length(){ return CurrentSize;}

    //提取第i（从1开始）元素值
    virtual K getKey(int i)const{
        assert(i > 0||i <= CurrentSize);
        return Element[i-1].key;
    }

    //修改第i（从1开始）元素值
    virtual void setKey(K x, int i){
        assert(i>0||i<=CurrentSize);
        Element[i-1].key = x;
    }

    //搜索
    virtual int SeqSearch(const K x)const;

    //插入
    virtual bool Insert(E &el);

    //删除
    virtual bool Remove(const K x, E &xl);

    friend ostream &operator <<(ostream &out, const dataList<E, K> &OutList);
    friend istream &operator >>(istream &in, dataList<E, K> &InList);

protected:
    dataNode<E, K> *Element; //数据表中存储数据的数组
    int ArraySize; //数组最大长度
    int CurrentSize; //数组当前长度
};



//-----------------以下为函数的类外定义----------------------

//类外定义：在dataList尾端插入新元素el，插入失败返回false，否则返回true
template <class E, class K>
bool dataList<E, K>::Insert(E &el) {
    if(CurrentSize == ArraySize)return false;
    Element[CurrentSize] = el; //插入在尾端
    CurrentSize++;
    return true;
}

//类外定义：在dataList中删除关键码为x的元素，通过el返回，用尾元素填补被删除元素
template <class E, class K>
bool dataList<E, K>::Remove(const K x, E &xl) {
    if(CurrentSize == 0)return false;
    //在表中顺序查找关键码为x的元素（将i定位到此处）
    for(int i = 0; i < CurrentSize && Element[i].key != x; i++);
    if(i == CurrentSize)return false; //未找到，返回
    el = Element[i]; //找到，保存被删除的值
    Element[i] = Element[CurrentSize-1]; //用尾元素填补
    CurrentSize--;
    return true;
}

//数据表类的友元函数
//重载插入运算符用于输出
template <class E, class K>
ostream &operator <<(ostream &out, const dataList<E, K> &OutList){
    //输出表的所有表项到out
    out << "Array Contents:" << endl;
    for(int i = 1; i <= OutList.CurrentSize; i++){
        out << OutList.Element[i-1] << " ";
    }
    out << endl;
    //输出表的当前长度到out
    out << "Array Current Size:" << OutList.CurrentSize << endl;
    return out;
}

//重载提取运算符用于输入
template <class E, class K>
istream &operator >>(istream &in, dataList<E, K> &InList){
    cout << "Enter array Current Size:";
    in >> InList.CurrentSize;
    cout << "Enter array element:" << endl;
    for(int i = 1; i < InList.CurrentSize; i++){
        cout <<"Element" << i << ":";
        cin >> InList.Element[i-1];
    }
    return in;
}

#endif //DATASTRUCTURE_DATALIST_H
