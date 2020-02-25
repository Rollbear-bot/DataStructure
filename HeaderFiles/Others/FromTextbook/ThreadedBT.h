//
// Created by 13592 on 2019/11/6.
// ���������������������ݽṹ�α�p212

#if 0

#ifndef DATASTRUCTURE_THREADEDBT_H
#define DATASTRUCTURE_THREADEDBT_H

template <class T>
struct ThreadNode{
    int ltag, rtag; //������־
    ThreadNode<T> *leftChild, *rightChild; //��������Ůָ��
    T data; //������
    //���캯��
    ThreadNode(const T item):
    data(item), leftChild(nullptr), rightChild(nullptr), ltag(0), rtag(0){}
};

//������������
template <class T>
class ThreadedBT{
protected:
    ThreadNode<T> *root; //���ĸ�ָ��
    //���������������������
    void createInThread(ThreadNode<T> *current, ThreadNode<T> *&pre);

    //Ѱ�ҽ��t�ĸ��ڵ�
    ThreadNode<T> *parent(ThreadNode<T> *t);

public:
    //���캯������������
    ThreadedBT():root(nullptr){}

    //������������������
    void createInThread();

    //Ѱ�������µ�һ�����
    ThreadNode<T> *First(ThreadNode<T> *current);

    //Ѱ�����������һ�����
    ThreadNode<T> *Last(ThreadNode<T> *current);

    //Ѱ�ҽ�������µĺ�̽��
    ThreadNode<T> *Next(ThreadNode<T> *current);

    //Ѱ�ҽ���������µ�ǰ�����
    ThreadNode<T> *Prior(ThreadNode<T> *current);
};

//-------------------------����Ϊ����ʵ��-----------------------------

//������������Զ�������������������
template <class T>
void ThreadedBT<T>::createInThread() {
    ThreadNode<T> *pre = nullptr; //ǰ�����ָ��
    if(root != nullptr){
        //�ǿն�������������
        createInThread(root, pre); //�������������������
        pre->rightChild = nullptr; //�����������һ�����
        pre->rtag = 1;
    }
}

#endif //DATASTRUCTURE_THREADEDBT_H

#endif