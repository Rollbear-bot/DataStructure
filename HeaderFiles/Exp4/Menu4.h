//
// Created by 13592 on 2019/11/11.
// 实验四：多项式计算

#ifndef DATASTRUCTURE_MENU4_H
#define DATASTRUCTURE_MENU4_H

#include "PolyByList.h"
#include "PolyByArr.h"
#include "PolyByLinearTable.h"

class Menu4{
public:
    Menu4(){}

public:
    //链表测试菜单
    static void menu(){
        string menuChoice[] = {"多项式：链表实现", "多项式：数组实现", "多项式：循序表实现"};
        do{
            cmd = UiCollection::choices("多项式测试菜单", 3, menuChoice, false);
            switch(cmd){
                case 1:
                    polyMenu<PolyByList<int>>();
                    break;

                case 2:
                    polyMenu<PolyByArr<int>>();
                    break;

                case 3:
                    polyMenu<PolyByLinearTable<int>>();
                    break;

                default:
                    break;
            }
        }while (cmd);
    }


protected:
    //多项式操作菜单，函数模板实现，适用于链表或者数组实现的多项式
    template <class T>
    static void polyMenu(){
        int hig = 0, value = 0, index = 0, preCmd = 0;
        //启动菜单前，应当先对多项式初始化
        cout << "建立多项式" << endl << "请输入最高次项的次数：";
        cin >> hig;
        //类型T为数组实现或者链表实现
        T pl(hig);
        for(int ind = hig; ind >= 0; ind--){
            cout << "请输入" << ind << "次项的系数：";
            cin >> value;
            pl.alter(ind, value);
        }
        string menuChoices[] = {"修改某项的系数", "输出多项式", "多项式运算"};
        //启动操作菜单
        do{
            preCmd = UiCollection::choices("false", 3, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "请输入要修改的项的次数：";
                    cin >> index;
                    cout << "请输入修改后的系数值：";
                    cin >> value;
                    UiCollection::printLine();
                    try{
                        pl.alter(index, value);
                        cout << "修改成功！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    try {
                        pl.printPoly();
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    try {
                        calculate<T>(pl);
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    break;

                default:
                    break;
            }
        }while(preCmd);
    }

    //多项式运算菜单
    template <class T>
    static void calculate(T thisPoly){
        int index, value = 0, hig = 0;
        //创建第二个多项式
        cout << "建立第二个多项式" << endl << "请输入最高次项的次数：";
        cin >> hig;
        T another(hig);
        for(int ind = hig; ind >= 0; ind--){
            cout << "请输入" << ind << "次项的系数：";
            cin >> value;
            another.alter(ind, value);
        }
        int preCmd;
        T sln(1);
        string menuChoices[] = {"加法运算", "减法运算"};
        do{
            preCmd = UiCollection::choices("多项式运算菜单", 2, menuChoices, false);
            switch(preCmd){
                case 1:
                    sln = thisPoly + another;
                    UiCollection::printLine();
                    cout << "运算结果为：" << endl;
                    sln.printPoly();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                /*减法运算存在问题
                case 2:
                    sln = thisPoly - another;
                    UiCollection::printLine();
                    cout << "运算结果为：" << endl;
                    sln.printPoly();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;
                    */

                default:
                    break;
            }
        }while (preCmd);
    }

    static int cmd;
};

//静态成员的初始化
int Menu4::cmd = 0;

#endif //DATASTRUCTURE_MENU4_H
