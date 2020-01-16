//
// Created by 13592 on 2019/11/11.
// 实验十：搜索结构

#ifndef DATASTRUCTURE_MENU10_H
#define DATASTRUCTURE_MENU10_H

#include "staticSearch.h"

class Menu10{
public:
    Menu10(){}
    static void menu(){
        //公用的一些变量
        int len, value, index;
        cout << "先建立静态搜索表" << endl << "请输入表长：";
        cin >> len;
        StaticSrhTable<int> sst(len);
        for(index = 0; index < len; index++){
            cout << "请输入第" << index+1 << "个元素：";
            cin >> value;
            sst.append(value);
        }
        sst.insertSort();
        string menuChoices[] = {"输出表", "二分查找", "顺序查找"};
        do{
            cmd = UiCollection::choices("静态搜索表测试", 3, menuChoices, false);
            switch (cmd){
                case 1:
                    sst.printTable();
                    break;

                case 2:
                    cout << "请输入查找的元素：";
                    cin >> value;
                    try {
                        index = sst.binarySearch(value);
                        cout << "查找成功！所查找的元素位于索引" << index << endl;
                    }catch(NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "请输入查找的元素：";
                    cin >> value;
                    try {
                        index = sst.orderSearch(value);
                    }catch(NoFound e){
                        e.print();
                    }
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

int Menu10::cmd = 0;

#endif //DATASTRUCTURE_MENU10_H
