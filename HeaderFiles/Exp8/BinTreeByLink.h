// 二叉树：链接实现（三叉链表）
// Created by rollbear on 2020/2/2.
/*
 * 实验要求：
1、以二叉链表表示二叉树,创建二叉树,学会以下 3 种方法:
(1)先建立结点,再建立树;
(2)通过广义表(或各种遍历)以输入流或文件流建立;
(3)交互式建立。
2、基本操作函数:构造函数、析构函数、复制构造函数、赋值运算等，以及二叉树的复制
和删除基本操作。
2、输出二叉树
3、二叉树的先序、中序、后序遍历和按层遍历(递归和非递归)
4、统计和输出二叉树结构特征(包含部分设计性实验):
(1)输出结点的左右孩子、叶子结点。
(2)统计:结点个数、叶子个数、深(高)度、度为 1 和 2 的结点个数、结点的层次。
(3)采用先序遍历算法输出从根到叶子结点的路径以及从叶子结点到的根逆路径。
 */

#ifndef DATASTRUCTURE_BINTREEBYLINK_H
#define DATASTRUCTURE_BINTREEBYLINK_H

#include <iostream>
#include "../Exp2/List.h"
#include <cmath>
#include <string>
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
    //无参构造
    BinTreeByLink(){}


    //构造函数：从一个代表广义表的字符串中构造
    BinTreeByLink(const string& gt, T nullValue){
        this->nullValue = nullValue;
        this->root = BuildByGeneralizedTable(gt);
    }


    //构造函数：交互式建立
    BinTreeByLink(T nullValue){
        this->nullValue = nullValue;
        this->root = BuildInteractive();
    }


    //拷贝构造函数
    BinTreeByLink(const BinTreeByLink<T> &another){
        this->nullValue = another.nullValue;
        List<T> tmp(another.layerTraversalWithoutRecursion());
        this->root = BuildByLayerTraversalList(tmp);
    }


    //析构函数
    ~BinTreeByLink(){
        remove(root);
    }


    //赋值运算符重载
    BinTreeByLink<T> operator =(const BinTreeByLink<T> &operand) {
        this->nullValue = operand.nullValue;
        this->root = BuildByLayerTraversalList(
                operand.layerTraversalWithoutRecursion());
        return *this;
    }

public:
    //计算树高：递归实现的封装
    int height() const {
        return heightCountRecursion(root, 1);
    }


    //计算叶子节点的个数：递归实现的封装
    int numOfLeaves() const {
        return leavesNumCountRecursion(root);
    }


    //计算节点个数
    int numOfNodes() const {
        return preOrderTraversalWithoutRecursion().getLen();
    }


    //寻找从根节点到指定节点的路径，返回字符串格式的路径
    string printPathFromRoot(int index) const {
        Stack<bool> goLeft = pathFromRoot(index);
        //todo::需要设计从T类型到char类型的转化方法
        string path;
        path += (this->root->value);
        bool turnLeft;
        BinTreeNode<T> *tra = this->root;
        //解析布尔栈
        while(!goLeft.isEmpty()){
            turnLeft = goLeft.pop();
            if(turnLeft) tra = tra->leftChild;
            else tra = tra->rightChild;
            path += " -> ";
            path += (tra->value);
        }
        return path;
    }


    //根据层次序序号获取某个位置的节点的数据值
    //序号从1开始（根节点的序号是1）
    T getNodeValue(int index) const {
        BinTreeNode<T> *currentNode = getNode(index);
        return currentNode == nullptr? nullValue: currentNode->value;
    }


    //根据层次序序号删除某个节点和它的所有子节点，序号从1开始
    void removeByIndex(int index){
        remove(getNode(index));
    }


    //为某个节点添加子节点，若该位置已存在节点则失败，返回false
    //根据层次序序号来选择父节点（根节点的序号是1）
    bool append(int index, T value, bool leftAppend){
        return append(getNode(index), value, leftAppend);
    }


    //前序遍历递归的封装：返回一个链表形式的遍历结果
    List<T> preOrderTraversal() const {
        List<T> result(0);
        preOrderRecursion(root, result);
        return result;
    }


    //中序遍历递归的封装：返回链表
    List<T> inOrderTraversal() const {
        List<T> result(0);
        inOrderRecursion(root, result);
        return result;
    }


    //后序遍历递归的封装：返回链表
    List<T> postOrderTraversal() const {
        List<T> result(0);
        postOrderRecursion(root, result);
        return result;
    }


    //非递归层次序遍历：使用队列
    List<T> layerTraversalWithoutRecursion() const {
        Queue<BinTreeNode<T>*> queue(pow(2, height()) - 1); //建立队列
        List<T> result;
        BinTreeNode<T> *currentNode;

        //首先根节点入队
        queue.enter(root);
        //每个节点从队头离开时，访问它，并将它的左右子节点依次从队尾入队，
        //直到队列空
        while(!queue.isEmpty()){
            currentNode = queue.quit();
            result.append(currentNode->value);
            if(result.getLen() >= (pow(2, height()) - 1)) break;

            //空白位置也要记录，否则不能体现出层次关系
            if(currentNode->leftChild == nullptr)
                queue.enter(new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode));
            else queue.enter(currentNode->leftChild);
            if(currentNode->rightChild == nullptr)
                queue.enter(new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode));
            else queue.enter(currentNode->rightChild);
        }//end while

        return result;
    }


    //非递归前序遍历
    List<T> preOrderTraversalWithoutRecursion() const {
        List<T> result(0);
        Stack<BinTreeNode<T>*> stack(20);
        BinTreeNode<T> *currentNode;
        stack.push(root); //首先将根节点入栈

        //每次栈顶节点出栈时访问它，然后它的右、左子女依次入栈
        while(!stack.isEmpty()){
            currentNode = stack.pop();
            if(currentNode->value != nullValue)
                result.append(currentNode->value); //访问
            if(currentNode->rightChild != nullptr && currentNode->rightChild->value != nullValue)
                stack.push(currentNode->rightChild);
            if(currentNode->leftChild != nullptr && currentNode->leftChild->value != nullValue)
                stack.push(currentNode->leftChild);
        } //end while

        return result;
    }


protected:
    BinTreeNode<T> *root; //根节点
    T nullValue; //代表空位置的值


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
                    //检测左孩子是否已经存在
                    if(currentNode->leftChild != nullptr &&
                        currentNode->leftChild->value != nullValue) throw Ex("不合理的广义表！");
                    //新建一个数据值为空的左孩子节点，并将指针移到那里
                    currentNode->leftChild =
                            new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode);
                    currentNode = currentNode->leftChild;
                    break;
                case ')':
                    //指针返回该节点的父节点
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode = currentNode->parent;
                    break;
                case ',':
                    //检测兄弟节点是否已经存在
                    if(currentNode->parent->rightChild != nullptr &&
                         currentNode->parent->rightChild->value != nullValue) throw Ex("不合理的广义表！");
                    //创建兄弟节点并将指针移动到那里
                    if(currentNode->parent == nullptr) throw NullPointer();
                    currentNode->parent->rightChild =
                            new BinTreeNode<T>(nullValue, nullptr, nullptr, currentNode->parent);
                    currentNode = currentNode->parent->rightChild;
                    break;
                default:
                    //检测该节点是否已经存在数据值
                    if(currentNode->value != nullValue) throw Ex("不合理的广义表！");
                    //为该节点添加数据
                    currentNode->value = T(currentChar);
                    break;
            } //end switch
        } while(currentChar != '\0');
        refresh(r); //标准化（删除所有无用节点）
        return r;
    }


    /*
     * 交互式建立二叉树
     * 要求用户从键盘输入各类数据
     * 函数返回该二叉树的根节点
     * todo::输入无效指令时应该提示，并要求重新输入
     * todo::节点覆盖时出错
     */
    BinTreeNode<T> *BuildInteractive(){
        int choice = 1;
        T value;
        string exceptionInfo = "该节点已存在：";

        cout << "开始交互式建立二叉树" << endl;

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
            try{
                switch (choice){
                    case 1:
                        if(p->leftChild != nullptr && p->leftChild->value != nullValue){
                            p = p->leftChild;
                            throw Ex(exceptionInfo.append(&(p->leftChild->value)));
                        }
                        cout << "请输入节点的值：" << endl;
                        cin >> value;
                        p->leftChild = new BinTreeNode<T>(T(value), nullptr, nullptr, p);
                        p = p->leftChild;
                        break;
                    case 2:
                        if(p->rightChild != nullptr && p->rightChild->value != nullValue){
                            p = p->rightChild;
                            throw Ex(exceptionInfo.append(&(p->rightChild->value)));
                        }
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
            }
            catch (Ex e){
                e.printInfo();
                cout << "输入该位置的新值：" << endl;
                cin >> value;
                p->value = value;
            }
        } //end while
        refresh(r); //标准化（删除所有无用节点）
        return r;
    }


    //从层次序遍历序列建立二叉树，返回二叉树的根节点
    BinTreeNode<T> *BuildByLayerTraversalList(const List<T> &layerList){
        int listIndex = 0;
        BinTreeNode<T> *r = new BinTreeNode<T>(layerList.getEle(listIndex),
                                               nullptr, nullptr, nullptr);
        BinTreeNode<T> *currentNode;

        //通过层次序遍历结果来构造
        Queue<BinTreeNode<T>*> queue(layerList.getLen()); //建立队列
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
        refresh(r); //标准化（删除所有无用节点）
        return r;
    }

    //递归前序遍历
    void preOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result) const {
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //递归出口
        result.append(currentNode->value); //将当前节点的数据值附加到结果链表
        preOrderRecursion(currentNode->leftChild, result); //访问左孩子
        preOrderRecursion(currentNode->rightChild, result); //访问右孩子
    }


    //递归中序遍历
    void inOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result) const {
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //递归出口
        inOrderRecursion(currentNode->leftChild, result); //访问左孩子
        result.append(currentNode->value); //访问根节点
        inOrderRecursion(currentNode->rightChild, result); //访问右孩子
    }


    //递归后序遍历
    void postOrderRecursion(BinTreeNode<T> *currentNode, List<T> &result) const {
        if(currentNode == nullptr || currentNode->value == nullValue)
            return; //递归出口
        postOrderRecursion(currentNode->leftChild, result); //访问左孩子
        postOrderRecursion(currentNode->rightChild, result); //访问右孩子
        result.append(currentNode->value); //访问根节点
    }


    //寻找从根到指定节点的路径，使用一个布尔栈来实现
    Stack<bool> pathFromRoot(int index) const {
        //用一个栈来存储从根节点到目标节点的路径，
        //布尔量表示在某个节点是前往左孩子还是右孩子
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


    //根据节点的层次序序号，返回该节点（根节点的序号为1）
    //若不存在该序号的节点，返回空指针
    BinTreeNode<T> *getNode(int index) const {
        Stack<bool> goLeft = pathFromRoot(index);

        //栈构造完毕，开始访问
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


    //判断某个节点是否是叶子节点（无子节点）
    bool isLeaf(BinTreeNode<T> *node) const {
        return  node->leftChild == nullptr
            && node->rightChild == nullptr;
    }


    //递归实现计算树高
    int heightCountRecursion(BinTreeNode<T> *currentNode, int h) const {
        if(isLeaf(currentNode)) { return h; } //递归出口

        int leftValue = 0, rightValue = 0;
        h++;
        //保留长的那个分支的长度，因为树高取决于最长的分支
        if(currentNode->leftChild != nullptr)
            leftValue = heightCountRecursion(currentNode->leftChild, h);
        if(currentNode->rightChild != nullptr)
            rightValue = heightCountRecursion(currentNode->rightChild, h);
        return (leftValue > rightValue)? leftValue: rightValue;
    }


    //递归计算叶子节点的数量
    int leavesNumCountRecursion(BinTreeNode<T> *currentNode) const {
        if(isLeaf(currentNode)) return 1; //到达叶子，递归出口
        int leftNum = (currentNode->leftChild == nullptr)?
                0: leavesNumCountRecursion(currentNode->leftChild);
        int rightNum = (currentNode->rightChild == nullptr)?
                0: leavesNumCountRecursion(currentNode->rightChild);
        return leftNum + rightNum;
    }


    //删除某个节点以及它的所有子节点
    void remove(BinTreeNode<T> *node){
        if(node == nullptr) return;

        //如果左孩子存在，删除左孩子
        if(node->leftChild != nullptr && node->leftChild->value != nullValue)
            remove(node->leftChild);
        //如果右孩子存在，删除右孩子
        if(node->rightChild != nullptr && node->rightChild->value != nullValue)
            remove(node->rightChild);
        //删除自己
        BinTreeNode<T> *tmp = node;
        bool nodeIsTheLeft;
        if(node->parent != nullptr){
            //判断目标节点是父节点的左孩子还是右孩子
            nodeIsTheLeft = (node == node->parent->leftChild);
            //清除指向垃圾空间的指针
            if(nodeIsTheLeft) node->parent->leftChild = nullptr;
            else node->parent->rightChild = nullptr;
        }
        delete node; //释放空间
    }


    //删除所有无用节点（即值为nullValue的节点）
    void refresh(BinTreeNode<T> *currentNode){
        if(currentNode == nullptr)
            return;
        if(currentNode->value == nullValue){
            remove(currentNode); //去除值为nullValue的节点
            return;
        }
        refresh(currentNode->leftChild);
        refresh(currentNode->rightChild);
    }


    //为指定的节点添加子节点，失败则返回false
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
