//
// Created by 13592 on 2019/11/4.
/* 双向链表
 * 该容器中大量复用了单链表中的方法
 * 2019.11.19 起修改为附加头节点的双向链表
 * */

#ifndef DATASTRUCTURE_DOUBLELINKEDLIST_H
#define DATASTRUCTURE_DOUBLELINKEDLIST_H

#include "../Exp2/List.h"

template <class T>
struct DoubleLLNode{
    DoubleLLNode(){
        this->next = nullptr;
        this->front = nullptr;
    }
    DoubleLLNode(DoubleLLNode<T> *front, DoubleLLNode<T> *next, T data = 0){
        this->data = data;
        this->front = front;
        this->next = next;
    }
    T data; //数据域
    DoubleLLNode<T> *front; //前一个结点的地址
    DoubleLLNode<T> *next; //后一个结点的地址
};

template <class T>
class DoubleLinkedList{
public:
    //默认的构造函数
    DoubleLinkedList(){
        DoubleLinkedList(0);
    }

    //给定表长来建表
    DoubleLinkedList(int len){
        this->len = len;
        //长度为0即为空表
        if(!len){
            this->first = new DoubleLLNode<T>;
            this->last = new DoubleLLNode<T>;
            first->next = last;
            last->front = first;
        }
        else{
            //长度不为0时
            //头节点的front域为空指针
            this->first = new DoubleLLNode<T>(nullptr, new DoubleLLNode<T>, 0);
            DoubleLLNode<T> *flag = first->next;
            for(int count = 0; count < len; count++){
                flag->next = new DoubleLLNode<T>;
                flag = flag->next;
            }
            this->last = flag;
            //开始构造逆向的指针链
            for(int index = 1; index < len; index++){
                //前一个结点的地址放到当前结点的front域
                find(index)->front = preFind(index);
            }
        }
    }

    //拷贝构造函数
    DoubleLinkedList(const DoubleLinkedList<T> &another){
        this->len = another.len;
        this->first = new ListNode<T>;
        ListNode<T> *flag = first;
        //复制表中的值
        for(int index = 0; index < len; index++){
            flag->next = new ListNode<T>;
            flag = flag->next;
            flag->data = another.find(index)->data;
        }
        flag->next = new ListNode<T>;
        flag = flag->next;
        this->last = flag;
        for(int index = 1; index < len; index++){
            //前一个结点的地址放到当前结点的front域
            find(index)->front = preFind(index);
        }
    }

public:
    //追加结点到表尾
    void append(T item){
        last->data = item;
        //将原来的尾结点的地址放到新节点的front域中
        last->front = preFind(len);
        last->next = new DoubleLLNode<T>;
        //尾指针移动到新节点
        last = last->next;
        len++;
    }

    //根据下标返回其指针
    DoubleLLNode<T> *find(int index){
        if(index > len || index < 0)throw IndexOutException();
        DoubleLLNode<T> *flag = first->next;
        for(int count = 0; count < index; count++){
            flag = flag->next;
        }
        return flag;
    }

    //返回下标表示的前一个结点的指针，index=0时抛出异常
    DoubleLLNode<T> *preFind(int index){
        if(index < 0 || index >= len)throw IndexOutException();
        if(index == 0)return first;
        else return find(index-1);
    }

    //插入元素
    void insert(int index, T item){
        DoubleLLNode<T> *temp = this->find(index);
        this->preFind(index)->next = new DoubleLLNode<T>(preFind(index), temp, item);
        len++;
    }

    //修改某个结点的值
    void alter(int index, T value){
        this->find(index)->data = value;
    }

    //输出表
    void printList(){
        DoubleLLNode<T> *flag = first->next;
        while(true){
            cout << flag->data << " ";
            flag = flag->next;
            if(flag == last)break;
        }
        cout << endl;
    }

    //根据下标删除
    void delByIndex(int index){
        DoubleLLNode<T> *thisNode = this->find(index);
        DoubleLLNode<T> *nextNode = thisNode->next;
        DoubleLLNode<T> *preNode = this->preFind(index);
        preNode->next = nextNode;
        nextNode->front = preNode;
        delete thisNode;
    }

    DoubleLLNode<T> *getFirst(){ return this->first;}
    DoubleLLNode<T> *getLast(){ return this->last;}
    int getLen(){ return this->len;}


protected:
    DoubleLLNode<T> *first; //指向附加头节点，该结点不存放有效数据
    DoubleLLNode<T> *last; //尾指针，指向最后一个有效数据的下一个结点，该结点不存放有效数据
    int len;
};

#endif //DATASTRUCTURE_DOUBLELINKEDLIST_H