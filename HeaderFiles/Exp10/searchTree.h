// Created by 13592 on 2019/12/1.
// 二叉搜索树：二叉树（顺序表实现）复用
/*
 * 2019.12.2 二叉搜索树需要定义单独的结点类型来储存关键码key
 * 2019.12.2 静态成员build：提示用户输入元素值和关键码来构造二叉搜索树，函数返回一个searchTree对象
 */

#ifndef DATASTRUCTURE_SEARCHTREE_H
#define DATASTRUCTURE_SEARCHTREE_H

#include "../Exp8/BinTreeByLinearTable.h"

//二叉搜索树的结点定义
template <class K, class T>
class searchTree;
template <class K, class T>
class searchTreeNode{
    //二叉搜索树类是该类的友元类，方便修改key
    friend class searchTree<K, T>;
public:
    searchTreeNode(K key, T data):key(key), data(data){}
    searchTreeNode(T data):key(0), data(data){}
    searchTreeNode():key(0), data(0){}

    K getKey(){ return key;}
    void setKey(K key){ this->key = key;}
    T getData(){ return data;}
    void setData(T data){ this->data = data;}
protected:
    K key; //关键码域
    T data; //数据域
};


//二叉搜索树定义
template <class K, class T>
class searchTree: public BinTreeByLinearTable<searchTreeNode<K, T>> {
public:
    //构造函数：从链表构造二叉树
    searchTree(List<searchTreeNode<K, T>> lt): BinTreeByLinearTable(lt){}
    //searchTree(){}
    ~searchTree(){}

public:
    //建立二叉搜索树：提示输入元素值和关键码来构造二叉搜索树
    static searchTree &build(){
        int len=0, index=0, value=0, key=0;
        List<searchTreeNode<K, T>> lt(0);
        searchTreeNode<K, T> tempNode;
        cout << "请输入要建立搜索树的元素个数：";
        cin >> len;
        for(index = 0; index < len; index++){
            cout << "请输入第" << index+1 << "个元素的值：";
            cin >> value;
            cout << "请输入第" << index+1 << "个元素的关键码：";
            cin >> key;
            tempNode = searchTreeNode<K, T>(key, value);
            lt.append(tempNode);
        }
        //cout << "建立完成！" << endl;
        //下面完成结点的顺序化，即从链表建立二叉树
        table.alter(0, lt.find(0)->data);
        for(index = 1; index < lt.length(); index++){
            if(table.find(index).getKey() <= table.find(getParent(index)).getKey()){
                //如果结点的关键码小于它的父结点的关键码，它成为左子女

            }
            if(table.find(index).getKey() > table.find(getParent(index)).getKey()){
                //如果结点的关键码大于它的父结点的关键码，它成为右子女

            }
        }
        return searchTree(lt);
    }

/*
    //将搜索二叉树的结点排序
    void sort(){
        List<T> sortedList = levelVisit();
        sortedList.insertSort();
        int mid = sortedList.length()/2;
        alter(0, sortedList.find(mid)->data);

    }
*/
};

#endif //DATASTRUCTURE_SEARCHTREE_H
