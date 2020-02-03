//
// Created by 13592 on 2019/11/11.
// 实验八：二叉树与图

#ifndef DATASTRUCTURE_MENU8_H
#define DATASTRUCTURE_MENU8_H

#include "../Others/FromTextbook/MinHeap.h"
#include "../Others/FromTextbook/BinaryTree.h"
#include "../Exp2/List.h"
#include "BinTreeByLinearTable.h"
#include"..//UiCollection.h"

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

    //二叉树测试菜单：顺序表实现
    static void binTreeMenu(){
        int preCmd, index, value, len;
        List<int> inputList(0), outputList;

        /*
        cout << "二叉树（顺序表实现）测试" << endl << "首先建立树" << endl;
        UiCollection::printLine();
        cout << "请输入要输入的元素的个数：";
        cin >> len;
        UiCollection::printLine();
        for(index = 0; index < len; index++){
            cout << "请输入第" << index+1 << "个元素：";
            cin >> value;
            inputList.append(value);
        }
        //使用输入的元素链表来构造二叉树
         */

        //test
        int arr[] = {1,2,3,4,5,6,7,8};
        inputList = List<int>(8,arr);
        BinTreeByLinearTable<int> bt(inputList);

        cout << "二叉树建立成功！" << endl;
        string menuChoice[] = {"输出层次序遍历序列", "输出前序遍历序列", "输出中序遍历序列", "输出后序遍历序列", "删除结点"};
        do{
            preCmd = UiCollection::choices("二叉树测试菜单：顺序表实现", 5, menuChoice, false);
            switch (preCmd){
                case 1:
                    UiCollection::printLine();
                    try {
                        outputList = bt.levelVisit();
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
                    //这一分支的异常处理已在接口内完成
                    UiCollection::printLine();
                    outputList = bt.preVisit();
                    cout << "前序遍历输出为：" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    outputList = bt.inVisit();
                    cout << "中序遍历输出为：" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    outputList = bt.postVisit();
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
                        bt.delByIndex(index);
                        cout << "删除成功！" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }
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

#endif //DATASTRUCTURE_MENU8_H