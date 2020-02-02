// 二叉树：链接实现
// Created by rollbear on 2020/2/2.

#ifndef DATASTRUCTURE_BINTREEBYLINK_H
#define DATASTRUCTURE_BINTREEBYLINK_H

#include <iostream>
#include "../Exp2/List.h"
using namespace std;

//二叉树节点的定义
template <class T>
struct BinTreeNode{
    //构造函数：孩子指针和父指针默认值为nullptr
    explicit BinTreeNode(T value,
            BinTreeNode<T> *l = nullptr,
            BinTreeNode<T> *r = nullptr,
            BinTreeNode<T> *p = nullptr):
        value(value), leftChild(l), rightChild(r), parent(p){}
    T value; //数据域
    BinTreeNode<T> *leftChild; //左孩子
    BinTreeNode<T> *rightChild; //右孩子
    BinTreeNode<T> *parent; //父指针
};


//二叉树模板的定义
template <class T>
class BinTreeByLink{
public:
    //构造函数：从一个代表广义表的字符串中构造
    BinTreeByLink(const string& gt, T nullValue){
        this->nullValue = nullValue;
        this->root = BuildByGeneralizedTable(gt);
    }

    //构造函数：交互式建立
    BinTreeByLink(){
        this->root = BuildInteractive();
    }

public:
    /*
     * 从广义表构造二叉树，返回该二叉树的根节点
     * 具体步骤：
     * 遇到左括号时新建该节点的左孩子，并将指针移到那里
     * 遇到右括号时，指针返回该节点的父节点
     * 遇到数据值时，初始化指针指向的节点
     * 遇到逗号时，创建当前位置的兄弟节点，并将指针移到那里
     */
    BinTreeNode<T> *BuildByGeneralizedTable(string gt){
        int charIndex = 0;
        char currentChar = gt[charIndex];
        //todo::需要添加从char类型转化为T类型的方法
        //初始化根节点
        auto *r = new BinTreeNode<T>(T(currentChar));
        BinTreeNode<T> *currentNode = r;

        do{
            charIndex++;
            currentChar = gt[charIndex];
            if(!currentChar) break;
            switch (currentChar){
                case '(':
                    //新建一个数据值为空的孩子节点，并将指针移到那里
                    currentNode->leftChild = new BinTreeNode<T>(nullValue,
                            nullptr, nullptr, currentNode);
                    currentNode = currentNode->leftChild;
                    break;
                case ')':
                    //指针返回该节点的父节点
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode = currentNode->parent;
                    break;
                case ',':
                    //创建兄弟节点并将指针移动到那里
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode->parent->rightChild = new BinTreeNode<T>(nullValue,
                            nullptr, nullptr, currentNode->parent);
                    currentNode = currentNode->parent->rightChild;
                    break;
                default:
                    currentNode->value = T(currentChar);
            } //end switch
        } while(currentChar != '\0');
        return r;
    }

    /*
     * 交互式建立二叉树
     * 要求用户从键盘输入各类数据
     * 函数返回该二叉树的根节点
     * todo::输入无效指令时应该提示，并要求重新输入
     * todo::新建节点的位置已经存在节点是应该提示
     */
    BinTreeNode<T> *BuildInteractive(){
        int choice = 1;
        T value;

        cout << "开始交互式建立二叉树" << endl;
        cout << "请输入代表空位置的数据值：" << endl;
        cin >> this->nullValue;

        cout << "请输入根节点：" << endl;
        BinTreeNode<T> *r = new BinTreeNode<T>(nullValue);
        cin >> value;
        r->value = T(value);
        BinTreeNode<T> *p = r; //遍历指针

        while(choice){
            UiCollection::printLine();
            cout << "当前节点：" << p->value << endl;
            cout << "1:建立左孩子 2:建立右孩子 3:返回父节点 0:结束" << endl;
            cin >> choice;
            switch (choice){
                case 1:
                    cout << "请输入节点的值：" << endl;
                    cin >> value;
                    p->leftChild = new BinTreeNode<T>(T(value), nullptr, nullptr, p);
                    p = p->leftChild;
                    break;
                case 2:
                    cout << "请输入节点的值：" << endl;
                    cin >> value;
                    p->rightChild = new BinTreeNode<T>(T(value), nullptr, nullptr, p);
                    p = p->rightChild;
                    break;
                case 3:
                    p = p->parent;
                    cout << "指针已返回到父节点" << endl;
                    break;
            } //end switch
        } //end while
        return r;
    }

    //根据节点的层次序序号，返回该节点（序号从１开始）
    BinTreeNode<T> *getNode(int index){

    }

    //前序遍历递归的封装：返回一个链表形式的遍历结果
    List<T> preOrderTraversal(){
        List<T> result(0);
        preOrderRecursion(root, result);
        return result;
    }


protected:
    BinTreeNode<T> *root; //根节点
    T nullValue; //代表空位置的值

    //递归前序遍历
    void preOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result){
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //递归出口
        result.append(currentNode->value); //将当前节点的数据值附加到结果链表
        preOrderRecursion(currentNode->leftChild, result); //访问左孩子
        preOrderRecursion(currentNode->rightChild, result); //访问右孩子
    }
};

#endif //DATASTRUCTURE_BINTREEBYLINK_H
