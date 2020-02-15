//
// Created by 13592 on 2019/11/11.
/* 实验一测试菜单
 * 2019.11.26 添加了单链表lt来存放多个线性表，使得菜单支持同时创建多个顺序表来测试
 */

#ifndef DATASTRUCTURE_MENU1_H
#define DATASTRUCTURE_MENU1_H

#include "../UiCollection.h"
#include "LinearTable.h"
#include "../Exp2/List.h"

class Menu1{
public:
    Menu1(){}

public:
    static void menu() {
        int lenOfTable, index, value, tableIndex, index2;
        LinearTable<int> temp;
        cout << "实验一" << endl << "建立线性表" << endl;
        UiCollection::printLine();
        /*
        cout << "请输入表的长度：";
        cin >> lenOfTable;
        LinearTable<int> lt(lenOfTable);
        UiCollection::printLine();
         */

        string menuChoices[] = {"新建线性表", "删除表", "插入元素", "删除元素", "输出表", "输出所有表", "交换两项的值"};
        do {
            cmd = UiCollection::choices("false", 7, menuChoices, false);
            switch (cmd) {
                case 1:
                    cout << "请输入表长：";
                    cin >> lenOfTable;
                    UiCollection::printLine();
                    temp = LinearTable<int>(lenOfTable);
                    lt.append(temp);
                    cout << "新建完成！" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "请输入要删除的顺序表的索引：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.removeByIndex(index);
                        cout << "删除成功！" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "请选择要插入的线性表，请输入它的索引：";
                    cin >> tableIndex;
                    cout << "请输入插入的位置：";
                    cin >> index;
                    cout << "请输入插入的元素值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.find(tableIndex)->data.insert(index, value);
                        cout << "插入成功！" << endl;
                    } catch (IndexOutException e) {
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "请选择要删除元素的线性表，请输入它的索引：";
                    cin >> tableIndex;
                    cout << "请输入要删除的元素的下标：";
                    cin >> index;
                    try {
                        lt.find(tableIndex)->data.delByIndex(index);
                        cout << "删除成功！" << endl;
                    } catch (IndexOutException e) {
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "请选择要输出的表，请输入它的索引：";
                    cin >> tableIndex;
                    UiCollection::printLine();
                    lt.find(tableIndex)->data.printTable();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::printLine();
                    cout << "所有已保存的表为：" << endl;
                    try {
                        for(tableIndex = 0; tableIndex < lt.getLen(); tableIndex++){
                            lt.find(tableIndex)->data.printTable();
                        }
                    }catch (IndexOutException e){
                        e.print();
                    }catch (OverFlowException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 7:
                    /*
                    cout << "请输入要操作的线性表的序号：";
                    cin >> tableIndex;
                    cout << "请输入第一个表项的下标：";
                    cin >> index;
                    cout << "请输入第二个表项的下标：";
                    cin >>index2;
                    UiCollection::printLine();
                    try {
                        lt.find(tableIndex)->data.swap(index, index2);
                        cout << "交换成功！" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;*/

                default:
                    break;
            }
        } while (cmd);
    }

private:
    static int cmd;
    static List<LinearTable<int>> lt;
};

//静态成员的初始化
int Menu1::cmd = 0;
List<LinearTable<int>> Menu1::lt(0);

#endif //DATASTRUCTURE_MENU1_H
