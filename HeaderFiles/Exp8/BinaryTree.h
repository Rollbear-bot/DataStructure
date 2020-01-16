//
// Created by Junhong Wu on 2019/10/30.
// 来自数据结构课本

#ifndef DATASTRUCTURE_BINARYTREE_H
#define DATASTRUCTURE_BINARYTREE_H

#include "../Exp5/Stack.h"
#include "BinTree.h"

#include<iostream>
using namespace std;

template<class T>
//二叉树结点
struct BinTreeNode{
    T data; //数据域
    BinTreeNode<T> *leftChild, *rightChild; //左右子女链域
    BinTreeNode():leftChild(nullptr), rightChild(nullptr){}
    BinTreeNode(T x, BinTreeNode<T> *l = nullptr, BinTreeNode<T> *r = nullptr)
        :data(x), leftChild(l), rightChild(r){}
};

template <class T>
//二叉树类定义
class BinaryTree{
public:
    //构造函数
    BinaryTree():root(nullptr){}

    BinaryTree(T value):RefValue(value), root(nullptr){}

    BinaryTree(BinaryTree<T> &s); //复制构造函数

    ~BinaryTree(){ destroy(root);} //析构函数

public:
    bool IsEmpty(){return root == nullptr;} //判空

    //返回父节点
    BinTreeNode<T> *Parent(BinTreeNode<T> *current){
        return (root == nullptr||root == current)? nullptr:Parent(root, current);
    }

    //返回左子女
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current){
        return (current == nullptr)?current->leftChild:nullptr;
    }

    //返回右子女
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current){
        return (current == nullptr)?current->rightChild:nullptr;
    }

    //返回树高度
    int Height(){return Height(root);}

    //返回结点数
    int Size(){return Size(root);}

    //取根
    BinTreeNode<T>* getRoot()const { return  root;}

    //前序遍历
    void preOrder(void (*visit)(BinTreeNode<T> *p)){
        preOrder(root, visit);
    }

    //中序遍历
    void inOrder(void (*visit)(BinTreeNode<T> *p)){
        inOrder(root, visit);
    }

    //后序遍历
    void postOrder(void (*visit)(BinTreeNode<T> *p)){
        postOrder(root, visit);
    }

    //层次序遍历
    void levelOrder(void (*visit)(BinTreeNode<T> *p));

    //插入新元素
    int Insert(const T& item);

    //搜索
    BinTreeNode<T> *Find(T& item)const;

    T RefValue;  //数据输入停止标志

protected:
    BinTreeNode<T> *root; //二叉树的根指针



    //从文件读入建树
    void CreateBinTree(istream& in, BinTreeNode<T> *&subTree);

    //插入
    bool Insert(BinTreeNode<T> *&subTree, const T& x)const;

    //删除
    void destroy(BinTreeNode<T> *&subTree);

    //查找
    //bool Find(BinTreeNode)

    //遍历（类外实现）
    void Traverse(BinTreeNode<T> *subTree, ostream& out);

    //友元函数
    friend istream &operator >> (istream &in, BinaryTree<T>& Tree);
    friend ostream &operator << (ostream &out, BinaryTree<T> &Tree);
    friend void CreateBinTree(istream &in, BinTreeNode<char> *&BT);
};

//--------------------------类外实现----------------------------------
template <class T>
//若指针subTree不为空，则删除根为subTree的子树
void BinaryTree<T>::destroy(BinTreeNode<T> *&subTree) {
    if(subTree != nullptr){
        destroy(subTree->leftChild); //递归删除subTree的左子树
        destroy(subTree->rightChild); //递归删除subTree的右子树
        delete subTree;
    }
}

//template <class T>
//BinTreeNode<T> *BinaryTree<T>::*Parent()

template <class T>
//私有函数：搜索并输出根为subTree的二叉树
void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream& out){
    if(subTree != nullptr){
        out << subTree->data <<" ";
        Traverse(subTree->leftChild, out); //递归搜索并输出subTree的左子树
        Traverse(subTree->rightChild, out); //递归搜索并输出subTree的右子树
    }
}

template <class T>
//重载操作：输入并建立一棵二叉树Tree。in是输入流对象
istream& operator >> (istream &in, BinaryTree<T>& Tree){
    CreateBinTree(in, Tree.root); //建立二叉树
    return in;
}

template <class T>
//重载操作：输出一棵二叉树Tree，out是输出流对象
ostream &operator <<(ostream &out, BinaryTree<T> &Tree){
    out <<"二叉树的前序遍历"<<endl;
    Tree.Traverse(Tree.root, out);
    out << endl;
    return out;
}

template <class T>
//从输入流in输入二叉树的广义表表示建立对应的二叉链表
void CreateBinTree(istream &in, BinTreeNode<char> *&BT){
    Stack<BinTreeNode<char>*> s;
    BT = nullptr; //置空二叉树
    BinTreeNode<char> *p, *t; int k; //用k作为处理左右子树的标记
    char ch;
    in >> ch;
    while(ch != BinaryTree<T>::RefValue){ //逐个字符处理
        switch (ch){
            case '(':  //进入子树
                s.push(p);
                k = 1;
                break;

            case ')': //退出子树
                t = s.pop();
                break;

            case ',':
                k = 2;
                break;

            default:
                p = new BinTreeNode<T>(ch);
                BT = p;
        } //end switch
        in >> ch;
    }
}



template <class T>
class BinTree{
public:
    BinTree(){}
    ~BinTree(){}

public:
    //建立二叉树：从链表构造
    void build(List<T> lt){
        for(int index = 0; index < lt.getLen(); index++){

        }
    }

    //插入新结点
    void insert(T item){

    }


protected:
    BinTreeNode<T> *root; //二叉树的根指针
    BinTreeNode<T> *last; //尾指针，指向最后一个有效数据的下一个位置，排序方式为层次序
};

//#endif //DATASTRUCTURE_BINTREE_H


#endif //DATASTRUCTURE_BINARYTREE_H
