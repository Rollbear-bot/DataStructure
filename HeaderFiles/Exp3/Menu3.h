//
// Created by 13592 on 2019/11/11.
// 第三次实验

#ifndef DATASTRUCTURE_MENU3_H
#define DATASTRUCTURE_MENU3_H

#include "../UiCollection.h"
#include "CircleList.h"
#include "DoubleLinkedList.h"

//实验三：循环链表与双向链表
class Menu3{
public:
    Menu3(){}

public:
    static void menu(){
        int index, value, len;
        string choi[] = {"循环链表测试", "双向链表测试"};
        do{
            cmd = UiCollection::choices("实验三：循环链表与双向链表", 2, choi, false);
            switch(cmd){
                case 1:
                    listMenu<CircleList<int>>();
                    break;

                case 2:
                    listMenu<DoubleLinkedList<int>>();
                    break;

                default:
                    break;
            }
        }while (cmd);

    }

private:
    //使用函数模板来统一测试循环链表和双向链表
    template<class Type>
    static void listMenu(){
        int preCmd, index, value, len;
        cout << "建立链表" << endl << "请输入链表的长度：";
        cin >> len;
        UiCollection::printLine();
        Type lt(len);
        string menuChoices[] = {"插入结点", "删除结点", "输出链表", "修改结点的值", "检索结点"};
        do{
            preCmd = UiCollection::choices("false", 5, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "请输入插入的位置：";
                    cin >> index;
                    cout << "请输入要插入的元素的值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.insert(index, value);
                        cout << "插入成功！" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "请输入要删除的结点的下标：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.delByIndex(index);
                        cout << "删除成功！" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    lt.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "请输入要修改的结点的下标：";
                    cin >> index;
                    cout << "请输入修改后的结点的值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.alter(index, value);
                        cout << "修改成功！" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "请输入要检索的下标：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        cout << "该下标对应的结点的值为：" << lt.find(index)->data << endl;
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
/*
    static void DLLMenu(){
        int preCmd, index, value, len;
        cout << "建立双向链表" << endl << "请输入链表的长度：";
        cin >> len;
        UiCollection::printLine();
        DoubleLinkedList<int> dll(len);
        string menuChoices[] = {"插入结点", "删除结点", "输出链表", "修改结点的值", "检索结点"};
        do{
            preCmd = UiCollection::choices("双向链表测试菜单", 5, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "请输入插入的位置：";
                    cin >> index;
                    cout << "请输入要插入的元素的值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        dll.insert(index, value);
                        cout << "插入成功！" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "请输入要删除的结点的下标：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        dll.delByIndex(index);
                        cout << "删除成功！" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    dll.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "请输入要修改的结点的下标：";
                    cin >> index;
                    cout << "请输入修改后的结点的值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        dll.alter(index, value);
                        cout << "修改成功！" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "请输入要检索的下标：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        cout << "该下标对应的结点的值为：" << dll.find(index)->data << endl;
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
*/
    static int cmd;
};

//静态成员的初始化
int Menu3::cmd = 0;

#endif //DATASTRUCTURE_MENU3_H
