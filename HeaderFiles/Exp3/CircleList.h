//
// Created by 13592 on 2019/11/1.
//

#ifndef DATASTRUCTURE_CIRCLELIST_H
#define DATASTRUCTURE_CIRCLELIST_H

#include "../Exp2/List.h"

/*
 * 循环链表
 * 使用单链表实现，实现代码复用
 *
 * 未实现附加头节点
 * */
template <class T>
class CircleList{
public:
    //无参的构造函数
    CircleList(){
        //默认为构造一个空表
        CircleList(0);
    }

    //指定表长，使用单链表实现
    CircleList(int len){
        //len=0等特殊情况已经在List.h中处理，在这里不需要再考虑
        this->data = List<T>(len);
        this->first = data.getFirst();
        this->last = data.getLast();
        //将单链表的尾结点（该节点不存放数据，为last指向的结点即链表结束的标志）的地址域连接到链表首结点，实现循环链表
        last->next = this->first;
    }

    //从数组构造
    CircleList(int len, int lenOfArr, T arr[]){
        this->data = List<T>(len, lenOfArr, arr);
        this->first = data.getFirst();
        this->last = data.getLast();
        //将单链表的尾结点（该节点不存放数据，为last指向的结点即链表结束的标志）的地址域连接到链表首结点，实现循环链表
        last->next = first;
    }

public:
    //删除结点
    void delByIndex(int index){
        ListNode<T> *temp = data.find(index);
        data.preFind(index)->next = temp->next;
        delete temp;
    }

    //获取表长
    int getLen(){
        int len = 0;
        for(ListNode<T> *flag = first; flag != last; flag = flag->next){
            len++;
        }
        return len;
    }

    //判满
    bool isFull(){ return last == first;}

    //判空
    bool isEmpty(){ return first == nullptr;}

    //根据结点的值返回下标，未找到返回-1
    int locate(T item){ return data.locate(item);}

    //修改结点
    void alter(int index, T value){ data.alter(index, value);}

    //输出表
    void printList(){ data.printList();}

    //插入
    void insert(int index, T value){ data.insert(index, value);}

    //根据下标索引结点，返回指向该结点的指针
    ListNode<T> *find(int index){ return data.find(index);}

    //返回下标指向的元素的前一个元素的地址
    ListNode<T> *preFind(int index){ return data.preFind(index);}

protected:
    List<T> data;
    ListNode<T> *first;
    ListNode<T> *last;
};

#endif //DATASTRUCTURE_CIRCLELIST_H
