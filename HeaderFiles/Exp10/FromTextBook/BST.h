//
// Created by 13592 on 2019/12/4.
// 二叉搜索树：课本p309
// 需要修改p314的递归错误

#ifndef DATASTRUCTURE_BST_H
#define DATASTRUCTURE_BST_H

#include <iostream>
using namespace std;

template <class E, class K>
struct BSTNode{
    E data; //数据域
    BSTNode<E, K> *left, *right; //左子女和右子女

    //无参构造函数
    BSTNode(): left(nullptr), right(nullptr){}

    //构造函数
    BSTNode(const E d, BSTNode<E, K> *L = nullptr, BSTNode<E, K> *R = nullptr):
        data(d), left(L), right(R){}

    //析构函数
    ~BSTNode(){}

    //修改数据域
    void setData(E d){data = d;}

    //获取数据域
    E getData(){ return data;}
};

//二叉搜索树类定义
template <class E, class K>
class BST{
public:
    //构造函数
    BST(): root(nullptr){}

    //构造函数
    BST(K value);

    //析构函数
    ~BST(){}

public:
    //搜索
    bool Search(const K x)const{
        return Search(x, root) != nullptr;
    }

    //赋值
    BST<E, K> &operator =(const BST<E, K> &R);

    //置空
    void makeEmpty(){
        makeEmpty(root);
        root = nullptr;
    }

    //输出
    void PrintTree()const{
        PrintTree(root);
    }

    //求最小
    E Min(){ return Min(root)->data;}

    //求最大
    E Max(){ return Max(root)->data;}

    //插入新元素
    bool Insert(const E& el){
        return Insert(el, root);
    }

    //删除含x的结点
    bool Remove(const K x){
        return Remove(x, root);
    }


private:
    BSTNode<E, K> *root; //根指针
    K RefValue; //输入停止标志，用于输入
    //递归搜索
    BSTNode<E, K> *Search(const K x, BSTNode<E, K> *ptr);

    //递归置空
    void makeEmpty(BSTNode<E, K> *&ptr);

    //递归打印
    void PrintTree(BSTNode<E, K> *ptr)const;

    //递归复制
    BSTNode<E, K> *Copy(const BSTNode<E, K> *ptr);

    //递归求最小
    BSTNode<E, K> *Min(BSTNode<E, K> *ptr)const;

    //递归求最大
    BSTNode<E, K> *Max(BSTNode<E, K> *ptr)const;

    //递归插入
    bool Insert(const E& el, BSTNode<E, K> *&ptr);

    //递归删除
    bool Remove(const K x, BSTNode<E, K> *&ptr);
};

//私有函数：在以ptr为根的二叉搜索树中插入所含值为el的结点，若在树中已经含有el的结点，则不插入
template<class E, class K>
bool BST<E, K>::Insert(const E &el, BSTNode<E, K> *&ptr) {
    if(ptr == nullptr){
        ptr = new BSTNode<E, K>(el);
        return true;
    }
    else if(el < ptr->data)Insert(el, ptr->left); //左子树插入
        else if(el > ptr->data)Insert(el, ptr->right); //右子树插入
            else return false; //已在树中，不再插入
}

//输入一个元素序列，建立一棵二叉搜索树
template<class E, class K>
BST<E, K>::BST(K value) {
    E x;
    //置空树
    root = nullptr;
    RefValue = value;
    cin >> x;
    while(x.key != RefValue){
        //RefValue是输入结束标志
        Insert(x, root);
        cin >> x; //插入后再输入数据
    }//end while
}

template<class E, class K>
void BST<E, K>::PrintTree(BSTNode<E, K> *ptr) const {
    if(ptr == nullptr) return;
    PrintTree(ptr->left);
    cout << ptr->data << " ";
    PrintTree(ptr->right);
}


#endif //DATASTRUCTURE_BST_H
