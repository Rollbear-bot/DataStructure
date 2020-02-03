// ������������ʵ�֣���������
// Created by rollbear on 2020/2/2.
/*
 * ʵ��Ҫ��
1���Զ��������ʾ������,����������,ѧ������ 3 �ַ���:
(1)�Ƚ������,�ٽ�����;
(2)ͨ�������(����ֱ���)�����������ļ�������;
(3)����ʽ������
2��������������:���캯�����������������ƹ��캯������ֵ�����,�Լ��������ĸ���
��ɾ������������
2�����������
3�����������������򡢺�������Ͱ������(�ݹ�ͷǵݹ�)
4��ͳ�ƺ�����������ṹ����(�������������ʵ��):
(1)����������Һ��ӡ�Ҷ�ӽ�㡣
(2)ͳ��:��������Ҷ�Ӹ�������(��)�ȡ���Ϊ 1 �� 2 �Ľ����������Ĳ�Ρ�
(3)������������㷨����Ӹ���Ҷ�ӽ���·���Լ���Ҷ�ӽ�㵽�ĸ���·����
 */

#ifndef DATASTRUCTURE_BINTREEBYLINK_H
#define DATASTRUCTURE_BINTREEBYLINK_H

#include <iostream>
#include "../Exp2/List.h"
using namespace std;

//�������ڵ�Ķ���
template <class T>
struct BinTreeNode{
    //���캯��������ָ��͸�ָ��Ĭ��ֵΪnullptr
    explicit BinTreeNode(T value,
            BinTreeNode<T> *l = nullptr,
            BinTreeNode<T> *r = nullptr,
            BinTreeNode<T> *p = nullptr):
        value(value), leftChild(l), rightChild(r), parent(p){}
    T value; //������
    BinTreeNode<T> *leftChild; //����
    BinTreeNode<T> *rightChild; //�Һ���
    BinTreeNode<T> *parent; //��ָ��
};


//������ģ��Ķ���
template <class T>
class BinTreeByLink{
public:
    //���캯������һ������������ַ����й���
    BinTreeByLink(const string& gt, T nullValue){
        this->nullValue = nullValue;
        this->root = BuildByGeneralizedTable(gt);
    }

    //���캯��������ʽ����
    BinTreeByLink(){
        this->root = BuildInteractive();
    }

    //�������캯��
    BinTreeByLink(const BinTreeByLink<T> &another){
        this->nullValue = another.nullValue;
        //todo::�������캯��
    }

public:
    //���ݽڵ�Ĳ������ţ����ظýڵ㣨��Ŵӣ���ʼ��
    BinTreeNode<T> *getNode(int index){

    }

    //ǰ������ݹ�ķ�װ������һ��������ʽ�ı������
    List<T> preOrderTraversal(){
        List<T> result(0);
        preOrderRecursion(root, result);
        return result;
    }

    //��������ݹ�ķ�װ����������
    List<T> inOrderTraversal(){
        List<T> result(0);
        inOrderRecursion(root, result);
        return result;
    }

    //��������ݹ�ķ�װ����������
    List<T> postOrderTraversal(){
        List<T> result(0);
        postOrderRecursion(root, result);
        return result;
    }

    //�ǵݹ�ǰ�����
    List<T> preOrderTraversalWithoutRecursion(){
        List<T> result(0);
        Stack<T> stack(0);
    }


protected:
    BinTreeNode<T> *root; //���ڵ�
    T nullValue; //�����λ�õ�ֵ


    /*
     * �ӹ����������������ظö������ĸ��ڵ�
     * ���岽�裺
     * ����������ʱ�½��ýڵ�����ӣ�����ָ���Ƶ�����
     * ����������ʱ��ָ�뷵�ظýڵ�ĸ��ڵ�
     * ��������ֵʱ����ʼ��ָ��ָ��Ľڵ�
     * ��������ʱ��������ǰλ�õ��ֵܽڵ㣬����ָ���Ƶ�����
     */
    BinTreeNode<T> *BuildByGeneralizedTable(string gt){
        int charIndex = 0;
        char currentChar = gt[charIndex];
        //todo::��Ҫ��Ӵ�char����ת��ΪT���͵ķ���
        //��ʼ�����ڵ�
        auto *r = new BinTreeNode<T>(T(currentChar));
        BinTreeNode<T> *currentNode = r;

        do{
            charIndex++;
            currentChar = gt[charIndex];
            if(!currentChar) break;
            switch (currentChar){
                case '(':
                    //�½�һ������ֵΪ�յĺ��ӽڵ㣬����ָ���Ƶ�����
                    currentNode->leftChild = new BinTreeNode<T>(nullValue,
                                                                nullptr, nullptr, currentNode);
                    currentNode = currentNode->leftChild;
                    break;
                case ')':
                    //ָ�뷵�ظýڵ�ĸ��ڵ�
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode = currentNode->parent;
                    break;
                case ',':
                    //�����ֵܽڵ㲢��ָ���ƶ�������
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
     * ����ʽ����������
     * Ҫ���û��Ӽ��������������
     * �������ظö������ĸ��ڵ�
     * todo::������Чָ��ʱӦ����ʾ����Ҫ����������
     * todo::�½��ڵ��λ���Ѿ����ڽڵ���Ӧ����ʾ
     */
    BinTreeNode<T> *BuildInteractive(){
        int choice = 1;
        T value;

        cout << "��ʼ����ʽ����������" << endl;
        cout << "����������λ�õ�����ֵ��" << endl;
        cin >> this->nullValue;

        cout << "��������ڵ㣺" << endl;
        BinTreeNode<T> *r = new BinTreeNode<T>(nullValue);
        cin >> value;
        r->value = T(value);
        BinTreeNode<T> *p = r; //����ָ��

        while(choice){
            UiCollection::printLine();
            cout << "��ǰ�ڵ㣺" << p->value << endl;
            cout << "1:�������� 2:�����Һ��� 3:���ظ��ڵ� 0:����" << endl;
            cin >> choice;
            switch (choice){
                case 1:
                    cout << "������ڵ��ֵ��" << endl;
                    cin >> value;
                    p->leftChild = new BinTreeNode<T>(T(value), nullptr, nullptr, p);
                    p = p->leftChild;
                    break;
                case 2:
                    cout << "������ڵ��ֵ��" << endl;
                    cin >> value;
                    p->rightChild = new BinTreeNode<T>(T(value), nullptr, nullptr, p);
                    p = p->rightChild;
                    break;
                case 3:
                    p = p->parent;
                    cout << "ָ���ѷ��ص����ڵ�" << endl;
                    break;
            } //end switch
        } //end while
        return r;
    }

    //�ݹ�ǰ�����
    void preOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result){
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        result.append(currentNode->value); //����ǰ�ڵ������ֵ���ӵ��������
        preOrderRecursion(currentNode->leftChild, result); //��������
        preOrderRecursion(currentNode->rightChild, result); //�����Һ���
    }

    //�ݹ��������
    void inOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result){
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        inOrderRecursion(currentNode->leftChild, result); //��������
        result.append(currentNode->value); //���ʸ��ڵ�
        inOrderRecursion(currentNode->rightChild, result); //�����Һ���
    }

    //�ݹ�������
    void postOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result){
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        postOrderRecursion(currentNode->leftChild, result); //��������
        postOrderRecursion(currentNode->rightChild, result); //�����Һ���
        result.append(currentNode->value); //���ʸ��ڵ�
    }
};

#endif //DATASTRUCTURE_BINTREEBYLINK_H
