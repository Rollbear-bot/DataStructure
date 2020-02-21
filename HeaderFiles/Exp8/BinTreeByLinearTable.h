//
// Created by 13592 on 2019/11/27.
/* 二叉树：顺序表实现
 * 索引的顺序为二叉树的层次序排序
 * 根结点的索引为0
 * 2019.12.4 为某个结点添加左子女leftAppend，添加右子女rightAppend
 * */

#ifndef DATASTRUCTURE_BINTREEBYLINEARTABLE_H
#define DATASTRUCTURE_BINTREEBYLINEARTABLE_H

#include "../Exp1/LinearTable.h"
#include "../Exp2/List.h"
#include "../Exp5/Stack.h"

//二叉树的顺序表实现
//该类为线性表LinearTable的友元类
template <class T>
class BinTreeByLinearTable{
public:
    //构造函数：从链表构造
    BinTreeByLinearTable(List<T> lt){ build(lt);}
    ~BinTreeByLinearTable(){}

public: //以下为公有接口
    //返回某个结点左子女的索引，无左子女返回-1
    int getLeftChild(int index){
        int leftChildIndex = index*2+1;
        if(!realIndex(leftChildIndex)) return -1;
        else return leftChildIndex;
    }

    //返回某个结点右子女的索引，无右子女返回-1
    int getRightChild(int index){
        int rightChildIndex = index*2+2;
        if(!realIndex(rightChildIndex)) return -1;
        else return rightChildIndex;
    }

    //返回某个结点的父节点的索引，无父节点返回-1
    int getParent(int index){
        //若该节点为二叉树的根，那么它没有父节点
        if(index == 0)return -1;
        //如果该结点的索引为偶数，那么它一定是右子女
        if(index % 2 == 0) return (index-2)/2;
        else return (index-1)/2;
    }

    //修改某个结点的值，索引为层次序索引
    void alter(int index, T item){
        table.alter(index, item);
    }

    //获取某个结点的元素值：索引为层次序索引
    T getEle(int index){
        return table.find(index);
    }

    //层次序遍历：返回一个存放层次序遍历元素序列的链表
    List<T> &levelVisit(){
        List<T> sln(0);
        for(int index = 0; index < table.length(); index++){
            sln.append(table.find(index));
        }
        return sln;
    }

    //前序遍历：返回链表
    List<T> &preVisit(){
        List<T> sln(0);
        //递归访问
        preOrder(0, sln);
        return sln;
    }

    //中序遍历：返回链表
    List<T> &inVisit(){
        List<T> sln(0);
        inOrder(0, sln);
        return sln;
    }

    //后序访问：返回链表
    List<T> &postVisit(){
        List<T> sln(0);
        postOrder(0, sln);
        return sln;
    }

    //交换两个结点：索引为层次序索引
    void swap(int indexA, int indexB){
        if(realIndex(indexA) && realIndex(indexB))
            table.swap(indexA, indexB);
        else throw IndexOutException();
    }

    //删除结点：索引为层次序索引，该节点的子节点也被删除
    void delByIndex(int index){
        if(!realIndex(index))return;
        //递归删除左子树
        delByIndex(getLeftChild(index));
        //递归删除右子树
        delByIndex(getRightChild(index));

        //删除根节点，这里不能直接调用顺序表的delByIndex接口，因为该接口会将后面的元素全部前移
        //将删除的结点的值改为NULL
        table.alter(index, NULL);
        //不需要修改尾指针last
    }

    //新增一个结点，成为当前结点的左子女
    void leftAppend(int currentIndex, T item){
        //如果该结点已经存在左子女，则不可以添加
        if(realIndex(getLeftChild(currentIndex)))throw IndexOutException();
        //alter方法会自动调整顺序表的尾指针last
        table.alter(currentIndex*2 + 1, item);
    }

    //新增一个结点，成为当前结点的右子女
    void rightAppend(int currentIndex, T item){
        //如果该结点已经存在右子女，则不可以添加
        if(realIndex(getRightChild(currentIndex)))throw IndexOutException();
        //alter方法会自动调整顺序表的尾指针last
        table.alter(currentIndex*2 + 2, item);
    }

    //二叉树的结点个数
    int size(){ return table.length();}

protected: //以下为类内调用的类内功能接口
    //类内方法：从单链表建立二叉树，在构造函数中调用
    void build(List<T> lt){
        this->table = LinearTable<T>(49);
        for(int index = 0; index < lt.length(); index++){
            table.alter(index, lt.find(index)->data);
        }
    }

    //类内方法：判断某个索引的结点是否存在
    bool realIndex(int index){
        //这两条语句不能放在一个或语句中判断，因为下标溢出的时候find会抛出异常
        if(index >= table.length() || index < 0) return false;
        return !(table.find(index) == NULL);
    }

    //类内方法：递归实现的中序访问
    void inOrder(int subTreeIndex, List<T> &sln){
        if(!realIndex(subTreeIndex))return;
        //首先访问左子树
        inOrder(getLeftChild(subTreeIndex), sln);
        //然后访问根结点
        sln.append(table.find(subTreeIndex));
        //最后访问右子树
        inOrder(getRightChild(subTreeIndex), sln);
    }

    //类内方法：递归实现的后序访问
    void postOrder(int subTreeIndex, List<T> &sln){
        if(!realIndex(subTreeIndex))return;
        //首先访问左子树
        postOrder(getLeftChild(subTreeIndex), sln);
        //然后访问右子树
        postOrder(getRightChild(subTreeIndex), sln);
        //最后访问根节点
        sln.append(table.find(subTreeIndex));
    }

    //类内方法：递归实现的前序访问
    void preOrder(int subTreeIndex, List<T> &sln){
        if(!realIndex(subTreeIndex)) return;
        try {
            //test
            //cout << "index:" << subTreeIndex << endl;
            //首先访问根节点，将根节点的元素放入结果链表中
            sln.append(table.find(subTreeIndex));
        }
        catch(IndexOutException e){ cout << "preOrder IndexOut! index:" << subTreeIndex << endl;}
        //然后递归访问左子树
        try { preOrder(getLeftChild(subTreeIndex), sln);} catch (IndexOutException e){
            cout << "getLeftChild IndexOut! index:" << subTreeIndex << endl;}
        //然后递归访问右子树
        try { preOrder(getRightChild(subTreeIndex), sln);} catch (IndexOutException e){
            cout << "getRightChild IndexOut! index:" << subTreeIndex << endl;}
    }

protected:
    //数据域：顺序表
    LinearTable<T> table;
};

#endif //DATASTRUCTURE_BINTREEBYLINEARTABLE_H