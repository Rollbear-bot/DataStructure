//
// Created by 13592 on 2019/11/17.
// p248 5.25 非递归实现数的前序遍历

#include "../../HeaderFiles/Exp8/BinaryTree.h"
#include "../../HeaderFiles/Exp5/Stack.h"

//消去右递归后的前序遍历算法
template <class T>
void PreOrder(BinTreeNode<T> *root){
    //用循环来代替右子女的递归
    while(root){
        cout << root->data << endl;
        //左子女递归前序遍历
        PreOrder(root->leftChild);
        root = root->rightChild;
    }
}

//前序遍历的非递归算法
template <class T>
void PreOrderX(BinTreeNode<T> *root){
    BinTreeNode<T> *temp;
    Stack<BinTreeNode<T>*> st;
    //根节点入栈
    st.push(root);
    while (!st.isEmpty()){
        //出栈并输出栈顶的值
        temp = st.pop();
        cout << temp->data << endl;
        //右子树先入栈，所以在出栈时在左子树之后，符合前序遍历的要求
        if(temp->rightChild != nullptr) st.push(temp->rightChild);
        //左子树后入栈
        if(temp->leftChild != nullptr) st.push(temp->leftChild);
    }
}
