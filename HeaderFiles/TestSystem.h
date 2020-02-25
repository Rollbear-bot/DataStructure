//
// Created by 13592 on 2019/11/11.
// 系统类

#ifndef DATASTRUCTURE_TESTSYSTEM_H
#define DATASTRUCTURE_TESTSYSTEM_H

#include "Exp1//Menu1.h"
#include "Exp2//Menu2.h"
#include "Exp3//Menu3.h"
#include "Exp4//Menu4.h"
#include "Exp5//Menu5.h"
#include "Exp6//Menu6.h"
#include "Exp7//Menu7.h"
#include "Exp8//Menu8.h"
#include "Exp9//Menu9.h"
#include "Exp10//Menu10.h"
#include "Exp11/Menu11.h"

//系统信息
#define author "Wu Junhong"
#define Date "2020.02.20"

#include <iostream>
#include "UiCollection.h"
using namespace std;

/*系统类
 * 提供各级菜单
 * */
class TestSystem{
public:
    TestSystem(){}

public:
    //欢迎界面
    static void welcome(){
        cout << "数据结构测试系统" << endl;
        UiCollection::printLine();
        cout << "By " << author << " " << Date << endl;
        UiCollection::printLine();
    }

    //主菜单：选择章节
    static void mainMenu(){
        cmd = 0;
        string mainMenu[] = {"实验一：线性表的顺序表示与实现",
                             "实验二：线性表的链接表示与实现",
                             "实验三：循环链表、双向链表与静态链表",
                             "实验四：多项式计算",
                             "实验五：顺序栈与链栈的基本运算算法",
                             "实验六：队列的基本运算算法",
                             "实验七：顺序串的基本运算算法",
                             "实验八：二叉树的基本操作（建立）及遍历",
                             "实验九：线索化二叉树和树的基本操作（建立）和遍历",
                             "实验十：搜索结构",
                             "实验十一：图计算"};
        do{
            cmd = UiCollection::choices("请输入要测试的章节选项：", 11, mainMenu, true);
            switch (cmd){
                case 1:
                    Menu1::menu();
                    break;
                case 2:
                    Menu2::menu();
                    break;
                case 3:
                    Menu3::menu();
                    break;
                case 4:
                    Menu4::menu();
                    break;
                case 5:
                    Menu5::menu();
                    break;
                case 6:
                    Menu6::menu();
                    break;
                case 7:
                    Menu7::menu();
                    break;
                case 8:
                    Menu8::menu();
                    break;
                case 9:
                    //Menu9::meun();
                    break;
                case 10:
                    Menu10::menu();
                    break;
                case 11:
                    Menu11::menu();
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
int TestSystem::cmd = 0;


#endif //DATASTRUCTURE_TESTSYSTEM_H
