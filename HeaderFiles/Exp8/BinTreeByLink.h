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

#include "../Exp2/List.h"
#include <cmath>
#include <string>

//�������ڵ�Ķ���
template <class T>
struct BinTreeNode{
    //���캯��������ָ��͸�ָ��Ĭ��ֵΪnullptr
    explicit BinTreeNode(T v,
            BinTreeNode<T> *l = nullptr,
            BinTreeNode<T> *r = nullptr,
            BinTreeNode<T> *p = nullptr):
            value(v), leftChild(l), rightChild(r), parent(p){}
    T value; //������
    BinTreeNode<T> *leftChild; //����
    BinTreeNode<T> *rightChild; //�Һ���
    BinTreeNode<T> *parent; //��ָ��
};


//������ģ��Ķ���
template <class T>
class BinTreeByLink{
    template <class E>
    friend class ThreadTree;
public:
    //�޲ι���
    //BinTreeByLink(){}


    //���캯������һ������������ַ����й���
    BinTreeByLink(const string& gt){
        this->root = BuildByGeneralizedTable<BinTreeNode<T>>(gt);
    }


    //���캯��������ʽ����
    BinTreeByLink(bool interactive = false){
        if(interactive)
            this->root = BuildInteractive();
    }


    //�������캯��
    BinTreeByLink(const BinTreeByLink<T> &another){
        //this->nullValue = another.nullValue;
        List<T> tmp(another.layerTraversalWithoutRecursion());
        this->root = BuildByLayerTraversalList(tmp);
    }


    //��������
    ~BinTreeByLink(){
        remove(root);
    }


    //��ֵ���������
    BinTreeByLink<T> operator =(const BinTreeByLink<T> &operand) {
        //this->nullValue = operand.nullValue;
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
    T getNodeValue(int index, T nullValue = '#') const {
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
    //Ϊ�˷����������ĸ��ã��޸�Ϊ����ģ��
    template <class NodeType>
    List<T> inOrderTraversal() const {
        List<T> result(0);
        inOrderRecursion<NodeType>(root, result);
        return result;
    }


    //��������ݹ�ķ�װ����������
    List<T> postOrderTraversal() const {
        List<T> result(0);
        postOrderRecursion(root, result);
        return result;
    }


    //�ǵݹ����������ʹ�ö���
    List<T> layerTraversalWithoutRecursion(T nullValue = '#') const {
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
    List<T> preOrderTraversalWithoutRecursion(T nullValue = '#') const {
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


    //�ǵݹ��������
    List<T> inOrderTraversalWithoutRecursion(T nullValue = '#') const {
        List<T> res;
        Stack<BinTreeNode<T>*> stack;
        BinTreeNode<T> *cur = root;
        //����ջһ����ʶջ�׵�Ԫ��
        stack.push(new BinTreeNode<T>(nullValue));

        //��ĳ���ڵ������ӽڵ㣬������ջ��ָ���Ƶ��������ӽڵ�
        //���ڵ�û�����ӽڵ㣬���������Ȼ��ָ���Ƶ����ӽڵ�
        //���ڵ���Ҷ�ӽڵ㣬���������Ȼ���ջ��ȡ��һ���ڵ㣬�ظ�ֱ��ջ��
        //����ջ�еĽڵ�ֻ�ڳ�ջʱ����
        do{
            if(isLeaf(cur)) { //��ǰ�ڵ�ΪҶ��
                res.append(cur->value);
                while(true){
                    cur = stack.pop();
                    if(cur->value == nullValue) break; //��ջ����
                    res.append(cur->value);
                    if(cur->rightChild != nullptr){
                        //��ջȡ���Ľڵ㲻�������ӽڵ㣬ֱ�ӿ������ӽڵ�
                        cur = cur->rightChild;
                        break;
                    }
                }//end while
            }
            else {
                if(cur->leftChild != nullptr){
                    //��ǰ�ڵ������ӽڵ�
                    stack.push(cur);
                    cur = cur->leftChild;
                } else {
                    //��ǰ�ڵ�û�����ӽڵ�
                    res.append(cur->value);
                    cur = cur->rightChild;
                }
            }
        }while(!stack.isEmpty());
        return res;
    }


    //�ǵݹ�������
    List<T> postOrderTraversalWithoutRecursion(T nullValue = '#') const {
        List<T> res; //�����
        Stack<BinTreeNode<T>*> stack;
        BinTreeNode<T> *cur = root;
        //���ջ��
        stack.push(new BinTreeNode<T>(nullValue));

        //����ĳ���ڵ㣬�����ӽڵ���ڣ���ǰ�ڵ���ջ��ָ���Ƶ����ӽڵ�
        //�����ӽڵ㲻���ڣ���ָ���Ƶ����ӽڵ�
        do{
            if(isLeaf(cur)){
                //����ǰ�ڵ���Ҷ�ӣ��������������ջ��ȡ����һ���ڵ�
                res.append(cur->value);
                while(true){
                    cur = stack.pop();
                    if(cur->value == nullValue) return res; //����
                    //��ջ�Ľڵ㲻�ټ����߷�֧����Ϊջ�еĽڵ�����ӽڵ�һ���Ѿ�����
                    if(cur->rightChild != nullptr){
                        cur = cur->rightChild;
                        break;
                    } else res.append(cur->value);
                }//end while
            }
            if(cur->leftChild != nullptr){
                //�����ӽڵ����
                stack.push(cur);
                cur = cur->leftChild;
            } else {
                //�����ӽڵ㲻���ڣ����ӽڵ���ڣ�
                cur = cur->rightChild;
            }
        }while(!stack.isEmpty());
        return res;
    }


    /*
     * ��һ�ַǵݹ���������˼·��
     * ʹ�á�ջ��ջ�����Ӹ��ڵ㿪ʼ�����������ӽڵ�̽�⣨�������ʣ���·���Ľڵ���ջ
     * ֱ������һ��û�����ӽڵ�Ľڵ㣬��ʼ��ջ��
     * ��ջ������ÿ���ڵ㣬��������Ƿ������ӽڵ㣬�����򲻷���������ѹ��ջ������ջ��棻
     * �½�һ��ջ�����ӽڵ���ջ��������ջѹ�롰ջ��ջ��
     * ѭ��ֱ������ջ��
     */
    List<T> postOrderTraversalWithoutRecursion2(T nullValue = '#') const {
        List<T> res; //�����
        Stack<Stack<BinTreeNode<T>*>*> branches; //��֧ջ��������з�֧
        Stack<BinTreeNode<T>*> *mainBranch
            = new Stack<BinTreeNode<T>*>; //�������ڵ������֧

        BinTreeNode<T> *curNode = root; //��ǵ�ǰ�ڵ�
        Stack<BinTreeNode<T>*> *curBranch = mainBranch; //��ǵ�ǰ��֧
        do{
            curBranch->push(curNode); //������ÿ���ڵ���ջ
            if(curNode->leftChild != nullptr){
                //�����ӽڵ���ڣ��ڵ�ָ���Ƶ����ӽڵ�
                curNode = curNode->leftChild;
            } else {
                //�����ӽڵ㲻���ڣ���ʼ�ͷŸ÷�֧����ջ��
                while(true){
                    if(curBranch->isEmpty()){
                        //����÷�֧�ѿգ���������һ����֧
                        curBranch = branches.pop();
                        //��һ����֧ջ���Ľڵ��Ѿ���������֧��
                        //���Ըýڵ㲻�ܿ�����֧��ֱ�ӷ���
                        curNode = curBranch->pop();
                        res.append(curNode->value);
                        //���ڵ������һ����Ҫ���ʵĽڵ㣬�����ڵ��Ѿ�������ϣ��㷨����
                        if(curNode == root) return res;
                        else continue; //�����һ����֧�Ƿ��
                    }
                    else curNode = curBranch->pop(); //��֧δ�գ�ȡ����֧���Ľڵ�

                    if(curNode->rightChild != nullptr){
                        //����֧�е�ĳ���ڵ������ӽڵ㣬�򲻷��ʣ�����ѹ��ջ
                        curBranch->push(curNode);
                        //��ǰ��֧ѹ���֧ջ������
                        branches.push(curBranch);
                        //�����·�֧
                        curBranch = new Stack<BinTreeNode<T>*>;
                        //�·�֧����һ���ڵ�����ӽڵ㿪ʼ
                        curNode = curNode->rightChild;
                        break;
                    }
                    //���ͷŷ�֧����ջ����ͬʱ���ʽڵ�
                    res.append(curNode->value);
                }//end while
            }
        }while(curBranch==mainBranch || !branches.isEmpty());
        return res; //������������ʱ���ﲻ�Ǻ����ĳ���
    }


protected:
    BinTreeNode<T> *root; //���ڵ�


    /*
     * �ӹ����������������ظö������ĸ��ڵ�
     * ���岽�裺
     * ����������ʱ�½��ýڵ�����ӣ�����ָ���Ƶ�����
     * ����������ʱ��ָ�뷵�ظýڵ�ĸ��ڵ�
     * ��������ֵʱ����ʼ��ָ��ָ��Ľڵ�
     * ��������ʱ��������ǰλ�õ��ֵܽڵ㣬����ָ���Ƶ�����
     */
    template <class NodeType>
    static NodeType *BuildByGeneralizedTable(string gt, T nullValue = '#'){
        int charIndex = 0;
        char currentChar = gt[charIndex];
        //todo::��Ҫ��Ӵ�char����ת��ΪT���͵ķ���
        //��ʼ�����ڵ�
        auto *r = new NodeType(T(currentChar));
        NodeType *currentNode = r;

        do{
            charIndex++;
            currentChar = gt[charIndex];
            if(!currentChar) break;
            switch (currentChar){
                case '(':
                    //��������Ƿ��Ѿ�����
                    if(currentNode->leftChild != nullptr &&
                        currentNode->leftChild->value != nullValue)
                            throw Ex("������Ĺ����");
                    //�½�һ������ֵΪ�յ����ӽڵ㣬����ָ���Ƶ�����
                    currentNode->leftChild =
                            new NodeType(nullValue, nullptr, nullptr, currentNode);
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
                         currentNode->parent->rightChild->value != nullValue)
                            throw Ex("������Ĺ����");
                    //�����ֵܽڵ㲢��ָ���ƶ�������
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode->parent->rightChild =
                            new NodeType(nullValue,
                                nullptr,
                                nullptr,
                                currentNode->parent);
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
        refresh<NodeType>(r); //��׼����ɾ���������ýڵ㣩
        return r;
    }


    /*
     * ����ʽ����������
     * Ҫ���û��Ӽ��������������
     * �������ظö������ĸ��ڵ�
     * todo::������Чָ��ʱӦ����ʾ����Ҫ����������
     * todo::�ڵ㸲��ʱ����
     */
    BinTreeNode<T> *BuildInteractive(T nullValue = '#'){
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
        refresh<BinTreeNode<T>>(r); //��׼����ɾ���������ýڵ㣩
        return r;
    }


    //�Ӳ����������н��������������ض������ĸ��ڵ�
    BinTreeNode<T> *BuildByLayerTraversalList(const List<T> &layerList){
        int listIndex = 0;
        BinTreeNode<T> *r = new BinTreeNode<T>(layerList.getElem(listIndex),
                                               nullptr, nullptr, nullptr);
        BinTreeNode<T> *currentNode;

        //ͨ�������������������
        Queue<BinTreeNode<T>*> queue(layerList.getLen()); //��������
        queue.enter(r);
        while(listIndex < layerList.getLen()){
            currentNode = queue.quit();
            currentNode->leftChild =
                    new BinTreeNode<T>(layerList.getElem(++listIndex), nullptr, nullptr,
                                       currentNode);
            if(listIndex >= layerList.getLen()) break;

            currentNode->rightChild =
                    new BinTreeNode<T>(layerList.getElem(++listIndex), nullptr, nullptr,
                                       currentNode);
            queue.enter(currentNode->leftChild);
            queue.enter(currentNode->rightChild);
        }//end while
        refresh<BinTreeNode<T>>(r); //��׼����ɾ���������ýڵ㣩
        return r;
    }


    //�ݹ�ǰ�����
    void preOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result, T nullValue = '#') const {
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        result.append(currentNode->value); //����ǰ�ڵ������ֵ���ӵ��������
        preOrderRecursion(currentNode->leftChild, result); //��������
        preOrderRecursion(currentNode->rightChild, result); //�����Һ���
    }


    //�ݹ��������
    template <class NodeType>
    static void inOrderRecursion(NodeType *currentNode, List<T> &result, T nullValue = '#'){
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //�ݹ����
        inOrderRecursion<NodeType>(currentNode->leftChild, result); //��������
        result.append(currentNode->value); //���ʸ��ڵ�
        inOrderRecursion<NodeType>(currentNode->rightChild, result); //�����Һ���
    }


    //�ݹ�������
    void postOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result, T nullValue = '#') const {
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
    BinTreeNode<T> *getNode(int index, T nullValue = '#') const {
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
    template <class NodeType>
    static void remove(NodeType *node, T nullValue = '#'){
        if(node == nullptr) return;

        //������Ӵ��ڣ�ɾ������
        if(node->leftChild != nullptr && node->leftChild->value != nullValue)
            remove(node->leftChild);
        //����Һ��Ӵ��ڣ�ɾ���Һ���
        if(node->rightChild != nullptr && node->rightChild->value != nullValue)
            remove(node->rightChild);
        //ɾ���Լ�
        NodeType *tmp = node;
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
    template <class NodeType>
    static void refresh(NodeType *currentNode, T nullValue = '#'){
        if(currentNode == nullptr)
            return;
        if(currentNode->value == nullValue){
            remove(currentNode); //ȥ��ֵΪnullValue�Ľڵ�
            return;
        }
        refresh<NodeType>(currentNode->leftChild);
        refresh<NodeType>(currentNode->rightChild);
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
