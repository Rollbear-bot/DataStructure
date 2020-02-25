// 线索化二叉树
// Created by @rollbear on 2020/2/18.

#ifndef DATASTRUCTURE_THREADTREE_H
#define DATASTRUCTURE_THREADTREE_H

#include "../Exp8/BinTreeByLink.h"

//线索化二叉树的节点定义：继承了普通二叉树的节点定义
template <class T>
struct ThreadNode {
    /*
    explicit ThreadNode(T v,
               BinTreeNode<T> *l = nullptr,
               BinTreeNode<T> *r = nullptr,
               BinTreeNode<T> *p = nullptr)
               : BinTreeNode<T>(v, l, r, p){}
*/
    //构造函数
    explicit ThreadNode(
            T d = 0,
            ThreadNode<T> *lc = nullptr,
            ThreadNode<T> *rc = nullptr,
            ThreadNode<T> *p = nullptr,
            bool lt = false,
            bool rt = false
            )
    : lTag(lt), rTag(rt), leftChild(lc), rightChild(rc), value(d), parent(p){}

    bool lTag = false;
    bool rTag = false;
    ThreadNode<T> *leftChild;
    ThreadNode<T> *rightChild;
    ThreadNode<T> *parent;
    T value;

};


//线索化二叉树的定义
//声明为二叉树BinTreeByLink的友元类
template <class T>
class ThreadTree{
public:
    //构造函数：从广义表建立
    explicit ThreadTree(const string &generalizedTable){
        this->threadState = empty;
        this->root = build(generalizedTable);
    }


public:
    //中序遍历
    List<T> inOrderTraversal(){
        List<T> res; //结果集
        List<ThreadNode<T>*> tmp;
        if(threadState != ThreadState::inOrderThread) {
            //若中序的线索不存在，则建立线索
            inOrderTraversal_ptrOnly(root, &tmp); //获取该二叉树的中序遍历序列
            createInOrderThread(root, tmp); //根据中序遍历序列添加线索
        }
        //若中序的线索已存在，则直接使用线索访问
        inOrderTraversal_thoughThread(root, &res);
        return res;
    }


protected:
    ThreadNode<T> *root; //根节点
    //标记线索的状态
    enum ThreadState{empty, inOrderThread, preOrderThread, postOrderThread}
    threadState;


    //从广义表建立线索化二叉树
    static ThreadNode<T> *build(const string &generalizedTable){
        //先建立链接实现的二叉树，这里复用了在普通二叉树中实现的建立方法
        ThreadNode<T> *root
            = BinTreeByLink<T>::template
                    BuildByGeneralizedTable<ThreadNode<T>>(generalizedTable);
        return root;
    }


    //递归为二叉树添加线索（为当前节点和它的所有子节点添加线索）
    //线索按照中序遍历的顺序添加，函数需要提供中序遍历结果作为添加线索的依据
    static void createInOrderThread(ThreadNode<T> *cur,
            const List<ThreadNode<T>*> &inOrderList){
        if(cur == nullptr) return; //递归出口
        //为当前节点添加，如果指针域已经被占用则不添加
        if(cur->leftChild == nullptr){
            //如果当前节点是中序遍历的第一个节点，则指针域空
            if(inOrderList.locate(cur)==0)
                cur->leftChild = nullptr;
            else {//否则左指针指向中序遍历的上一个节点
                cur->leftChild = inOrderList.preFind(inOrderList.locate(cur))->data;
            }
            cur->lTag = true; //修改标记
        } else {
            //为左子节点添加
            createInOrderThread(cur->leftChild, inOrderList);
        }
        if(cur->rightChild == nullptr){
            //如果当前节点是中序遍历的最后一个节点，则指针域空
            if(inOrderList.locate(cur) == inOrderList.length() - 1)
                cur->rightChild = nullptr;
            else {//与左指针的操作类似
                cur->rightChild =
                        inOrderList.find(inOrderList.locate(cur))->next->data;
            }
            cur->rTag = true; //修改标记
        } else {
            //为右子女添加
            createInOrderThread(cur->rightChild, inOrderList);
        }
    }


    //中序遍历：得到一个储存遍历结果节点的链表
    //类内功能函数（用于建立线索）
    static void inOrderTraversal_ptrOnly(ThreadNode<T> *cur,
            List<ThreadNode<T>*> *const res){
        if(cur == nullptr) return; //递归出口
        //访问左子节点
        inOrderTraversal_ptrOnly(cur->leftChild, res);
        //访问current节点
        res->append(cur);
        //访问右子节点
        inOrderTraversal_ptrOnly(cur->rightChild, res);
    }


    //中序遍历：使用线索
    //非递归实现，此处复用了普通二叉树的实现
    static List<T> inOrderTraversal_thoughThread(ThreadNode<T> *root, T nullValue = '#'){

    }

};

#endif //DATASTRUCTURE_THREADTREE_H
