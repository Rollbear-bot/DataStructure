// ������������
// Created by @rollbear on 2020/2/18.

#ifndef DATASTRUCTURE_THREADTREE_H
#define DATASTRUCTURE_THREADTREE_H

#include "../Exp8/BinTreeByLink.h"

//�������������Ľڵ㶨�壺�̳�����ͨ�������Ľڵ㶨��
template <class T>
struct ThreadNode {
    /*
    explicit ThreadNode(T v,
               BinTreeNode<T> *l = nullptr,
               BinTreeNode<T> *r = nullptr,
               BinTreeNode<T> *p = nullptr)
               : BinTreeNode<T>(v, l, r, p){}
*/
    //���캯��
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


//�������������Ķ���
//����Ϊ������BinTreeByLink����Ԫ��
template <class T>
class ThreadTree{
public:
    //���캯�����ӹ������
    explicit ThreadTree(const string &generalizedTable){
        this->threadState = empty;
        this->root = build(generalizedTable);
    }


public:
    //�������
    List<T> inOrderTraversal(){
        List<T> res; //�����
        List<ThreadNode<T>*> tmp;
        if(threadState != ThreadState::inOrderThread) {
            //����������������ڣ���������
            inOrderTraversal_ptrOnly(root, &tmp); //��ȡ�ö������������������
            createInOrderThread(root, tmp); //����������������������
        }
        //������������Ѵ��ڣ���ֱ��ʹ����������
        inOrderTraversal_thoughThread(root, &res);
        return res;
    }


protected:
    ThreadNode<T> *root; //���ڵ�
    //���������״̬
    enum ThreadState{empty, inOrderThread, preOrderThread, postOrderThread}
    threadState;


    //�ӹ������������������
    static ThreadNode<T> *build(const string &generalizedTable){
        //�Ƚ�������ʵ�ֵĶ����������︴��������ͨ��������ʵ�ֵĽ�������
        ThreadNode<T> *root
            = BinTreeByLink<T>::template
                    BuildByGeneralizedTable<ThreadNode<T>>(generalizedTable);
        return root;
    }


    //�ݹ�Ϊ���������������Ϊ��ǰ�ڵ�����������ӽڵ����������
    //�����������������˳����ӣ�������Ҫ�ṩ������������Ϊ�������������
    static void createInOrderThread(ThreadNode<T> *cur,
            const List<ThreadNode<T>*> &inOrderList){
        if(cur == nullptr) return; //�ݹ����
        //Ϊ��ǰ�ڵ���ӣ����ָ�����Ѿ���ռ�������
        if(cur->leftChild == nullptr){
            //�����ǰ�ڵ�����������ĵ�һ���ڵ㣬��ָ�����
            if(inOrderList.locate(cur)==0)
                cur->leftChild = nullptr;
            else {//������ָ��ָ�������������һ���ڵ�
                cur->leftChild = inOrderList.preFind(inOrderList.locate(cur))->data;
            }
            cur->lTag = true; //�޸ı��
        } else {
            //Ϊ���ӽڵ����
            createInOrderThread(cur->leftChild, inOrderList);
        }
        if(cur->rightChild == nullptr){
            //�����ǰ�ڵ���������������һ���ڵ㣬��ָ�����
            if(inOrderList.locate(cur) == inOrderList.length() - 1)
                cur->rightChild = nullptr;
            else {//����ָ��Ĳ�������
                cur->rightChild =
                        inOrderList.find(inOrderList.locate(cur))->next->data;
            }
            cur->rTag = true; //�޸ı��
        } else {
            //Ϊ����Ů���
            createInOrderThread(cur->rightChild, inOrderList);
        }
    }


    //����������õ�һ�������������ڵ������
    //���ڹ��ܺ��������ڽ���������
    static void inOrderTraversal_ptrOnly(ThreadNode<T> *cur,
            List<ThreadNode<T>*> *const res){
        if(cur == nullptr) return; //�ݹ����
        //�������ӽڵ�
        inOrderTraversal_ptrOnly(cur->leftChild, res);
        //����current�ڵ�
        res->append(cur);
        //�������ӽڵ�
        inOrderTraversal_ptrOnly(cur->rightChild, res);
    }


    //���������ʹ������
    //�ǵݹ�ʵ�֣��˴���������ͨ��������ʵ��
    static List<T> inOrderTraversal_thoughThread(ThreadNode<T> *root, T nullValue = '#'){

    }

};

#endif //DATASTRUCTURE_THREADTREE_H
