//
// Created by 13592 on 2019/11/11.
// 实验八：二叉树与图



#ifndef DATASTRUCTURE_MENU8_H
#define DATASTRUCTURE_MENU8_H

#if 1

#include "../Others/FromTextbook/MinHeap.h"
#include "../Others/FromTextbook/BinaryTree.h"
#include "../Exp2/List.h"
#include "BinTreeByLinearTable.h"
#include"..//UiCollection.h"
#include "BinTreeByLink.h"

class Menu8{
public:
    Menu8(){}

public:
    static void menu(){
        string menuChoices[] = {"堆测试", "二叉树测试"};
        do{
            cmd = UiCollection::choices("实验八", 2, menuChoices, false);
            switch(cmd){
                case 1:
                    heapMenu();
                    break;

                case 2:
                    binTreeMenu();
                    break;

                default:
                    break;
            }
        }while(cmd);
    }

public:
    //堆测试菜单
    static void heapMenu(){
        int preCmd, value = 0, len, carrier = 0;
        int arr[] = {1};
        cout << "先建立堆" << endl << "请输入堆的最大容量：";
        cin >> len;
        MinHeap<int> mp(arr, len);
        for(int index = 0; index < len; index++){
            cout << "请输入第" << index+1 << "个元素：";
            cin >> value;
            mp.alter(index, value);
        }
        string menuChoices[] = {"插入元素", "删除元素", "输出堆"};
        do{
            preCmd = UiCollection::choices("堆测试菜单", 3, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "请输入要插入的元素值：";
                    cin >> value;
                    UiCollection::printLine();
                    mp.Insert(value);
                    cout << "插入成功！" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    mp.RemoveMin(carrier);
                    cout << "弹出的值为：" << carrier << endl;
                    cout << "删除成功！" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    mp.printHeap();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (preCmd);
    }

    //二叉树测试菜单
    static void binTreeMenu(){
        int preCmd, index, value, len, choice;
        string GTable;
        List<char> outputList;


        BinTreeByLink<char> bt;
        cout << "0: 通过广义表建立二叉树 1:交互式建立二叉树" << endl;
        cin >> choice;
        if(choice){
            bt = BinTreeByLink<char>('#');
        } else {
            cout << "请输入广义表：" << endl;
            cin >> GTable;
            bt = BinTreeByLink<char>(GTable);
        }

        cout << "二叉树建立成功！" << endl;
        string menuChoice[] = {"输出层次序遍历序列",
                               "输出前序遍历序列",
                               "输出中序遍历序列",
                               "输出后序遍历序列",
                               "删除结点",
                               "统计树高",
                               "统计树节点数",
                               "统计叶子节点数",
                               "获取某个节点的数据值",
                               "展示从根节点到某个节点的路径"};
        do{
            preCmd = UiCollection::choices("二叉树测试菜单", 10, menuChoice, false);
            switch (preCmd){
                case 1:
                    UiCollection::printLine();
                    try {
                        outputList = bt.layerTraversalWithoutRecursion();
                        cout << "层次序输出为：" << endl;
                        outputList.printList();
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    //这一分支的异常处理已在函数内完成
                    UiCollection::printLine();
                    outputList = bt.preOrderTraversal();
                    cout << "前序遍历输出为：" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    outputList = bt.inOrderTraversal();
                    cout << "中序遍历输出为：" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    outputList = bt.postOrderTraversal();
                    cout << "后序遍历输出为：" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "请输入要删除的结点的层次序索引：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        bt.removeByIndex(index);
                        cout << "删除成功！" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    cout << "树高为：" << bt.height() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 7:
                    cout << "节点数为：" << bt.numOfNodes() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 8:
                    cout << "叶子节点数为：" << bt.numOfLeaves() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 9:
                    cout << "请输入该节点的层次序序号（根节点的序号为1）：";
                    cin >> index;
                    cout << "该节点的数据值为：" << bt.getNodeValue(index) << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 10:
                    cout << "请输入该节点的层次序序号（根节点的序号为1）：";
                    cin >> index;
                    cout << "路径为：" << bt.printPathFromRoot(index) << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (preCmd);
    }

    static int cmd;
};

//静态成员的初始化
int Menu8::cmd = 0;


#endif

#endif //DATASTRUCTURE_MENU8_H
