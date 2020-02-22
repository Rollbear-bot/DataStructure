// Created by 13592 on 2019/10/31.
/* 2019.11.23 添加了表合并函数add
 * 2019.11.26 新增从单链表List构造的构造函数
 * 2019.11.27 修改元素接口alter现在会自动调整尾指针last
 * 2019.11.30 新增接口：swap，交换两个表项的值
 * 2019.12.1  不可以在该类析构函数中调用delete释放data，会出现野指针问题
 * */

#ifndef DATASTRUCTURE_LINEARTABLE_H
#define DATASTRUCTURE_LINEARTABLE_H

#define MaxLen 50

#include <iostream>
#include "../DsException.h"
#include "../Exp2/List.h"
using namespace std;

//线性表的顺序实现
template <class T>
class LinearTable{
public:
    //下标运算符重载
    T &operator[](int index){
        return *find(index);
    }


    //指定表长的构造函数
    LinearTable(int maxLen = MaxLen-1){
        if(maxLen >= MaxLen)throw OverFlowException();
        this->max = maxLen;
    }

    //从数组构造
    LinearTable(int maxLen, int arrLen, T arr[]){
        if(maxLen >= MaxLen)throw OverFlowException();
        if(arrLen>maxLen)throw OverFlowException();
        this->max = maxLen;
        this->last = arrLen;
        for(int index = 0; index < arrLen; index++){
            data[index] = arr[index];
        }
    }


    //拷贝构造函数
    LinearTable(LinearTable& another){
        this->max = another.max;
        this->last = another.last;
        for(int index = 0; index < last; index++){
            this->data[index] = another.data[index];
        }
    }

    //析构函数
    ~LinearTable(){
        //delete[] data;
    }

public:
    //将顺序表中的元素序列输出为链表
    List<T> toList(){
        List<T> lt(0);
        for(int index = 0; index < this->last; index++){
            lt.append(this->data[index]);
        }
        return lt;
    }

    //追加一个元素到表尾
    void append(T item){
        if(last+1 > max)throw IndexOutException();
        data[last] = item;
        last++;
    }


    //查找元素是否在表中
    bool inTable(T item){
        return locate(item) != -1;
    }


    //下标方式删除元素
    void delByIndex(int index){
        for(int tra = index; tra < last; tra++){
            data[tra] = data[tra+1];
        }
        last--;
    }

    //查找元素：查找失败返回-1
    int locate(T item){
        for(int index = 0; index <= max; index++){
            if(data[index] == item)return index;
        }
        return -1;
    }

    //使用下标检索
    T& find(int index){
        if(index > last)throw IndexOutException();
        return data[index];
    }

    //插入：新元素放到指定的下标，该位置的原元素及其后的所有元素后移一个单位
    void insert(int index, T value){
        if(last+1 > max)throw IndexOutException();
        for(int temp = last; temp > index; temp--){
            data[temp] = data[temp-1];
        }
        data[index] = value;
        last++;
    }

    //输出表
    void printTable(){
        if(isEmpty())cout << "Empty Table!" << endl;
        for(int index = 0; index < last; index++){
            cout << data[index] << " ";
        }
        cout << endl;
    }

    //合并表：将第二个表附加到当前表尾，函数返回新表
    LinearTable<T> &add(LinearTable<T> &another){
        //新表的最大长度为两表最大长度之和
        LinearTable<T> sln(this->max + another.getMax());
        //复制表中元素值到新表
        for(int index = 0; index < this->length() + another.length(); index++){
            if(index < this->length()) sln.alter(index, this->data[index]);
            else sln.alter(index, another.find(index - this->length()));
        }
        return sln;
    }

    //修改某项的值
    void alter(int index, T value) {
        data[index] = value;
        if(this->last <= index)last = index + 1;
    }

    //交换两个表项的值
    void swap(int indexA, int indexB){
        T temp = find(indexA);
        alter(indexA, find(indexB));
        alter(indexB, temp);
    }

    //清空表
    void clear() { this->last = 0;}

    bool isEmpty() { return (last == 0);}
    bool isFull() { return (last == max);}
    int length(){ return this->last;}
    int getMax(){ return this->max;}

protected:
    T data[MaxLen]; //数据空间
    int last = 0; //最后一个有效数据单元的下一个位置，标记表尾，不存放有效数据
    int max; //最大长度
};

#endif //DATASTRUCTURE_LINEARTABLE_H
