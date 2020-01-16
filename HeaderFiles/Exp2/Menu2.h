//
// Created by 13592 on 2019/11/11.
// 实验二菜单

#ifndef DATASTRUCTURE_MENU2_H
#define DATASTRUCTURE_MENU2_H

#include "../UiCollection.h"
#include "..//DsException.h"
#include "List.h"

class Menu2{
public:
    Menu2(){}

public:
    static void menu(){
        int lenOfList, index, value;
        cout << "实验二" << endl << "建立单链表" << endl;
        UiCollection::printLine();
        cout << "请输入链表的长度：";
        cin >> lenOfList;
        List<int> lt(lenOfList);

        string menuChoices[] = {"插入结点", "删除结点", "查找结点", "输出链表", "获取表长", "链表置空"};
        do{
            cmd = UiCollection::choices("false", 6, menuChoices, false);
            switch(cmd){
                case 1:
                    cout << "请输入插入的位置：";
                    cin >> index;
                    cout << "请输入插入的元素值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.insert(index, value);
                        cout << "插入成功！" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }catch (NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "请输入要删除的元素的下标：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.delByIndex(index);
                        cout << "删除成功！" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "请输入要查找的下标：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        cout << "该下标对应的元素值为：";
                        cout << lt.find(index)->data << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    try {
                        lt.printList();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    UiCollection::printLine();
                    cout << "表长为：" << lt.getLen() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::printLine();
                    lt.clear();
                    cout << "置空完成！" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (cmd);
    }

private:
    static int cmd;
};

//静态成员的初始化
int Menu2::cmd = 0;

#endif //DATASTRUCTURE_MENU2_H
