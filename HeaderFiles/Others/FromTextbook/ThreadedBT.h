//
// Created by 13592 on 2019/11/6.
// 线索化二叉树，来自数据结构课本p212

#if 0

#ifndef DATASTRUCTURE_THREADEDBT_H
#define DATASTRUCTURE_THREADEDBT_H

template <class T>
struct ThreadNode{
    int ltag, rtag; //线索标志
    ThreadNode<T> *leftChild, *rightChild; //线索或子女指针
    T data; //数据域
    //构造函数
    ThreadNode(const T item):
    data(item), leftChild(nullptr), rightChild(nullptr), ltag(0), rtag(0){}
};

//线索化二叉树
template <class T>
class ThreadedBT{
protected:
    ThreadNode<T> *root; //树的根指针
    //中序遍历建立线索二叉树
    void createInThread(ThreadNode<T> *current, ThreadNode<T> *&pre);

    //寻找结点t的父节点
    ThreadNode<T> *parent(ThreadNode<T> *t);

public:
    //构造函数，创建空树
    ThreadedBT():root(nullptr){}

    //建立中序线索二叉树
    void createInThread();

    //寻找中序下第一个结点
    ThreadNode<T> *First(ThreadNode<T> *current);

    //寻找中序下最后一个结点
    ThreadNode<T> *Last(ThreadNode<T> *current);

    //寻找结点中序下的后继结点
    ThreadNode<T> *Next(ThreadNode<T> *current);

    //寻找结点在中序下的前驱结点
    ThreadNode<T> *Prior(ThreadNode<T> *current);
};

//-------------------------以下为类外实现-----------------------------

//利用中序遍历对二叉树进行中序线索化
template <class T>
void ThreadedBT<T>::createInThread() {
    ThreadNode<T> *pre = nullptr; //前驱结点指针
    if(root != nullptr){
        //非空二叉树，线索化
        createInThread(root, pre); //中序遍历线索化二叉树
        pre->rightChild = nullptr; //后处理中序最后一个结点
        pre->rtag = 1;
    }
}

#endif //DATASTRUCTURE_THREADEDBT_H

#endif