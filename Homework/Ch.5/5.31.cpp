//
// Created by 13592 on 2019/11/17.
// p249 5.31 编写一个算法，把一个新节点l作为s结点的左子女插入到一课线索化二叉树中，
// s原来的左子女变成l的左子女
#include "../../HeaderFiles/Exp9/ThreadedBT.h"

/*
void addNode()*/

template <class T>
void leftInsert(ThreadNode<T> *s, ThreadNode<T> *p){
    if(s != nullptr && p!= nullptr){
        if(s->ltag){ //如果原来s没有左子女
            //将s的左线索复制给p
            p->leftChild = s->leftChild;
            p->ltag = 1;
        }
        else{ //如果原来s有左子女
            p->leftChild = s->leftChild;
            p->ltag = 0;
            p->rightChild = s;
            p->rtag = 1; //修改p的右线索指向s
            ThreadNode<T> *q = p->leftChild;
            while (!q->rtag) q = q->rightChild;
            //
            p->rightChild = p;
        }
        s->leftChild = p;
        s->ltag = 0;
    }
}
