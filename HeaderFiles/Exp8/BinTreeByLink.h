// ������������ʵ�֣���������
// Created by rollbear on 2020/2/2.
/*
 * ʵ��Ҫ��
1���Զ��������ʾ������,����������,ѧ������ 3 �ַ���:
(1)�Ƚ������,�ٽ�����;
(2)ͨ�������(����ֱ���)�����������ļ�������;
(3)����ʽ������
2��������������:���캯�����������������ƹ��캯������ֵ����ȣ��Լ��������ĸ���
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
#include <cmath>
#include <string>
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
    //�޲ι���
    BinTreeByLink(){}


    //���캯������һ������������ַ����й���
    BinTreeByLink(const string& gt, T nullValue){
        this->nullValue = nullValue;
        this->root = BuildByGeneralizedTable(gt);
    }


    //���캯��������ʽ����
    BinTreeByLink(T nullValue){
        this->nullValue = nullValue;
        this->root = BuildInteractive();
    }


    //�������캯��
    BinTreeByLink(const BinTreeByLink<T> &another){
        this->nullValue = another.nullValue;
        List<T> tmp(another.layerTraversalWithoutRecursion());
        this->root = BuildByLayerTraversalList(tmp);
    }


    //��������
    ~BinTreeByLink(){
        remove(root);
    }


    //��ֵ���������
    BinTreeByLink<T> operator =(const BinTreeByLink<T> &operand) {
        this->nullValue = operand.nullValue;
        this->root = BuildByLayerTraversalList(
                operand.layerTraversalWithoutRecursion());
        return *this;
    }

public:
    //�������ߣ��ݹ�ʵ�ֵķ�װ
    int height() const {
        return heightCountRecursion(root, 1);
    }


    //����Ҷ�ӽڵ�ĸ������ݹ�ʵ�ֵķ�װ
    int numOfLeaves() const {
        return leavesNumCountRecursion(root);
    }


    //����ڵ����
    int numOfNodes() const {
        return preOrderTraversalWithoutRecursion().getLen();
    }


    //Ѱ�ҴӸ��ڵ㵽ָ���ڵ��·���������ַ�����ʽ��·��
    string printPathFromRoot(int index) const {
        Stack<bool> goLeft = pathFromRoot(index);
        //todo::��Ҫ��ƴ�T���͵�char���͵�ת������
        string path;
        path += (this->root->value);
        bool turnLeft;
        BinTreeNode<T> *tra = this->root;
        //��������ջ
        while(!goLeft.isEmpty()){
            turnLeft = goLeft.pop();
            if(turnLeft) tra = tra->leftChild;
            else tra = tra->rightChild;
            path += " -> ";
            path += (tra->value);
        }
        return path;
    }


    //���ݲ������Ż�ȡĳ��λ�õĽڵ������ֵ
    //��Ŵ�1��ʼ�����ڵ�������1��
    T getNodeValue(int index) const {
        BinTreeNode<T> *currentNode = getNode(index);
        return currentNode == nullptr? nullValue: currentNode->value;
    }


    //���ݲ�������ɾ��ĳ���ڵ�����������ӽڵ㣬��Ŵ�1��ʼ
    void removeByIndex(int index){
        remove(getNode(index));
    }


    //Ϊĳ���ڵ�����ӽڵ㣬����λ���Ѵ��ڽڵ���ʧ�ܣ�����false
    //���ݲ���������ѡ�񸸽ڵ㣨���ڵ�������1��
    bool append(int index, T value, bool leftAppend){
        return append(getNode(index), value, leftAppend);
    }


    //ǰ������ݹ�ķ�װ������һ��������ʽ�ı������
    List<T> preOrderTraversal() const {
        List<T> result(0);
        preOrderRecursion(root, result);
        return result;
    }


    //��������ݹ�ķ�װ����������
    List<T> inOrderTraversal() const {
        List<T> result(0);
        inOrderRecursion(root, result);
        return result;
    }


    //��������ݹ�ķ�װ����������
    List<T> postOrderTraversal() const {
        List<T> result(0);
        postOrderRecursion(root, result);
        return result;
    }


    //�ǵݹ����������ʹ�ö���
    List<T> layerTraversalWithoutRecursion() const {
        Queue<BinTreeNode<T>*> queue(pow(2, height()) - 1); //��������
        List<T> result;
        BinTreeNode<T> *currentNode;

        //���ȸ��ڵ����
        queue.enter(root);
        //ÿ���ڵ�Ӷ�ͷ�뿪ʱ�����������������������ӽڵ����δӶ�β��ӣ�
        //ֱ�����п�
        while(!queue.isEmpty()){
            currentNode = queue.quit();
            result.append(currentNode->value);
            if(result.getLen() >= (pow(2, height()) - 1)) break;

            //�հ�λ��ҲҪ��¼�����������ֳ���ι�ϵ
            if(currentNode->leftChild == nullptr)
                queue.enter(new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode));
            else queue.enter(currentNode->leftChild);
            if(currentNode->rightChild == nullptr)
                queue.enter(new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode));
            else queue.enter(currentNode->rightChild);
        }//end while

        return result;
    }


    //�ǵݹ�ǰ�����
    List<T> preOrderTraversalWithoutRecursion() const {
        List<T> result(0);
        Stack<BinTreeNode<T>*> stack(20);
        BinTreeNode<T> *currentNode;
        stack.push(root); //���Ƚ����ڵ���ջ

        //ÿ��ջ���ڵ��ջʱ��������Ȼ�������ҡ�����Ů������ջ
        while(!stack.isEmpty()){
            currentNode = stack.pop();
            if(currentNode->value != nullValue)
                result.append(currentNode->value); //����
            if(currentNode->rightChild != nullptr && currentNode->rightChild->value != nullValue)
                stack.push(currentNode->rightChild);
            if(currentNode->leftChild != nullptr && currentNode->leftChild->value != nullValue)
                stack.push(currentNode->leftChild);
        } //end while

        return result;
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
                    //��������Ƿ��Ѿ�����
                    if(currentNode->leftChild != nullptr &&
                        currentNode->leftChild->value != nullValue) throw Ex("������Ĺ����");
                    //�½�һ������ֵΪ�յ����ӽڵ㣬����ָ���Ƶ�����
                    currentNode->leftChild =
                            new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode);
                    currentNode = currentNode->leftChild;
                    break;
                case ')':
                    //ָ�뷵�ظýڵ�ĸ��ڵ�
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode = currentNode->parent;
                    break;
                case ',':
                    //����ֵܽڵ��Ƿ��Ѿ�����
                    if(currentNode->parent->rightChild != nullptr &&
                         currentNode->parent->rightChild->value != nullValue) throw Ex("������Ĺ����");
                    //�����ֵܽڵ㲢��ָ���ƶ�������
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode->parent->rightChild =
                            new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode->parent);
                    currentNode = currentNode->parent->rightChild;
                    break;
                default:
                    //���ýڵ��Ƿ��Ѿ���������ֵ
                    if(currentNode->value != nullValue) throw Ex("������Ĺ����");
                    //Ϊ�ýڵ��������
                    currentNode->value = T(currentChar);
                    break;
            } //end switch
        } while(currentChar != '\0');
        refresh(r); //��׼����ɾ���������ýڵ㣩
        return r;
    }


    /*
     * ����ʽ����������
     * Ҫ���û��Ӽ��������������
     * �������ظö������ĸ��ڵ�
     * todo::������Чָ��ʱӦ����ʾ����Ҫ����������
     * todo::�ڵ㸲��ʱ����
     */
    BinTreeNode<T> *BuildInteractive(){
        int choice = 1;
        T value;
        string exceptionInfo = "�ýڵ��Ѵ��ڣ�";

        cout << "��ʼ����ʽ����������" << endl;

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
            try{
                switch (choice){
                    case 1:
                        if(p->leftChild != nullptr && p->leftChild->value != nullValue){
                            p = p->leftChild;
                            throw Ex(exceptionInfo.append(&(p->leftChild->value)));
                        }
                        cout << "������ڵ��ֵ��" << endl;
                        cin >> value;
                        p->leftChild = new BinTreeNode<T>(T(value), nullptr, nullptr, p);
                        p = p->leftChild;
                        break;
                    case 2:
                        if(p->rightChild != nullptr && p->rightChild->value != nullValue){
                            p = p->rightChild;
                            throw Ex(exceptionInfo.append(&(p->rightChild->value)));
                        }
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
            }
            catch (Ex e){
                e.printInfo();
                cout << "�����λ�õ���ֵ��" << endl;
                cin >> value;
                p->value = value;
            }
        } //end while
        refresh(r); //��׼����ɾ���������ýڵ㣩
        return r;
    }


    //�Ӳ����������н��������������ض������ĸ��ڵ�
    BinTreeNode<T> *BuildByLayerTraversalList(const List<T> &layerList){
        int listIndex = 0;
        BinTreeNode<T> *r = new BinTreeNode<T>(layerList.getEle(listIndex),
                                               nullptr, nullptr, nullptr);
        BinTreeNode<T> *currentNode;

        //ͨ�������������������
        Queue<BinTreeNode<T>*> queue(layerList.getLen()); //��������
        queue.enter(r);
        while(listIndex < layerList.getLen()){
            currentNode = queue.quit();
            currentNode->leftChild =
                    new BinTreeNode<T>(layerList.getEle(++listIndex), nullptr, nullptr,
                                       currentNode);
            if(listIndex >= layerList.getLen()) break;

            currentNode->rightChild =
                    new BinTreeNode<T>(layerList.getEle(++listIndex), nullptr, nullptr,
                                       currentNode);
            queue.enter(currentNode->leftChild);
            queue.enter(currentNode->rightChild);
        }//end while
        refresh(r); //��׼����ɾ���������ýڵ㣩
        return r;
    }

    //�ݹ�ǰ�����
    void preOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result) const {
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        result.append(currentNode->value); //����ǰ�ڵ������ֵ���ӵ��������
        preOrderRecursion(currentNode->leftChild, result); //��������
        preOrderRecursion(currentNode->rightChild, result); //�����Һ���
    }


    //�ݹ��������
    void inOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result) const {
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        inOrderRecursion(currentNode->leftChild, result); //��������
        result.append(currentNode->value); //���ʸ��ڵ�
        inOrderRecursion(currentNode->rightChild, result); //�����Һ���
    }


    //�ݹ�������
    void postOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result) const {
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        postOrderRecursion(currentNode->leftChild, result); //��������
        postOrderRecursion(currentNode->rightChild, result); //�����Һ���
        result.append(currentNode->value); //���ʸ��ڵ�
    }


    //Ѱ�ҴӸ���ָ���ڵ��·����ʹ��һ������ջ��ʵ��
    Stack<bool> pathFromRoot(int index) const {
        //��һ��ջ���洢�Ӹ��ڵ㵽Ŀ��ڵ��·����
        //��������ʾ��ĳ���ڵ���ǰ�����ӻ����Һ���
        Stack<bool> goLeft(numOfNodes());
        do {
            if(index % 2 == 0) {
                goLeft.push(true);
                index /= 2;
            }
            else {
                goLeft.push(false);
                index = (index-1) / 2;
            }
        } while(index > 1);
        return goLeft;
    }


    //���ݽڵ�Ĳ������ţ����ظýڵ㣨���ڵ�����Ϊ1��
    //�������ڸ���ŵĽڵ㣬���ؿ�ָ��
    BinTreeNode<T> *getNode(int index) const {
        Stack<bool> goLeft = pathFromRoot(index);

        //ջ������ϣ���ʼ����
        BinTreeNode<T> *visitor = this->root;
        while(!goLeft.isEmpty()){
            if(goLeft.pop()) {
                if(visitor->leftChild == nullptr || visitor->leftChild->value == nullValue)
                    return nullptr;
                visitor = visitor->leftChild;
            }
            else {
                if(visitor->rightChild == nullptr || visitor->rightChild->value == nullValue)
                    return nullptr;
                visitor = visitor->rightChild;
            }
        }
        return visitor;
    }


    //�ж�ĳ���ڵ��Ƿ���Ҷ�ӽڵ㣨���ӽڵ㣩
    bool isLeaf(BinTreeNode<T> *node) const {
        return  node->leftChild == nullptr
            && node->rightChild == nullptr;
    }


    //�ݹ�ʵ�ּ�������
    int heightCountRecursion(BinTreeNode<T> *currentNode, int h) const {
        if(isLeaf(currentNode)) { return h; } //�ݹ����

        int leftValue = 0, rightValue = 0;
        h++;
        //���������Ǹ���֧�ĳ��ȣ���Ϊ����ȡ������ķ�֧
        if(currentNode->leftChild != nullptr)
            leftValue = heightCountRecursion(currentNode->leftChild, h);
        if(currentNode->rightChild != nullptr)
            rightValue = heightCountRecursion(currentNode->rightChild, h);
        return (leftValue > rightValue)? leftValue: rightValue;
    }


    //�ݹ����Ҷ�ӽڵ������
    int leavesNumCountRecursion(BinTreeNode<T> *currentNode) const {
        if(isLeaf(currentNode)) return 1; //����Ҷ�ӣ��ݹ����
        int leftNum = (currentNode->leftChild == nullptr)?
                0: leavesNumCountRecursion(currentNode->leftChild);
        int rightNum = (currentNode->rightChild == nullptr)?
                0: leavesNumCountRecursion(currentNode->rightChild);
        return leftNum + rightNum;
    }


    //ɾ��ĳ���ڵ��Լ����������ӽڵ�
    void remove(BinTreeNode<T> *node){
        if(node == nullptr) return;

        //������Ӵ��ڣ�ɾ������
        if(node->leftChild != nullptr && node->leftChild->value != nullValue)
            remove(node->leftChild);
        //����Һ��Ӵ��ڣ�ɾ���Һ���
        if(node->rightChild != nullptr && node->rightChild->value != nullValue)
            remove(node->rightChild);
        //ɾ���Լ�
        BinTreeNode<T> *tmp = node;
        bool nodeIsTheLeft;
        if(node->parent != nullptr){
            //�ж�Ŀ��ڵ��Ǹ��ڵ�����ӻ����Һ���
            nodeIsTheLeft = (node == node->parent->leftChild);
            //���ָ�������ռ��ָ��
            if(nodeIsTheLeft) node->parent->leftChild = nullptr;
            else node->parent->rightChild = nullptr;
        }
        delete node; //�ͷſռ�
    }


    //ɾ���������ýڵ㣨��ֵΪnullValue�Ľڵ㣩
    void refresh(BinTreeNode<T> *currentNode){
        if(currentNode == nullptr)
            return;
        if(currentNode->value == nullValue){
            remove(currentNode); //ȥ��ֵΪnullValue�Ľڵ�
            return;
        }
        refresh(currentNode->leftChild);
        refresh(currentNode->rightChild);
    }


    //Ϊָ���Ľڵ�����ӽڵ㣬ʧ���򷵻�false
    bool append(BinTreeNode<T> *currentNode, T value, bool leftAppend){
        if(leftAppend){
            if(currentNode->leftChild != nullptr) return false;
            currentNode->leftChild =
                    new BinTreeNode<T>(value, nullptr, nullptr, currentNode);
        } else {
            if(currentNode->rightChild != nullptr) return false;
            currentNode->rightChild =
                    new BinTreeNode<T>(value, nullptr, nullptr, currentNode);
        }
        return true;
    }

};


#endif //DATASTRUCTURE_BINTREEBYLINK_H
