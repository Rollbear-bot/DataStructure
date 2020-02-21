//
// Created by 13592 on 2019/11/11.
// 串测试类

#ifndef DATASTRUCTURE_MENU7_H
#define DATASTRUCTURE_MENU7_H

#include "String.h"
#include "..//UiCollection.h"

class Menu7{
public:
    Menu7(){}

public:
    static void menu(){
        int index, value, len, index2, matchIndex;
        String<char> temp;
        char c;
        string menuChoice[] = {"新建串", "查看所有已保存的串", "连接串", "修改串", "删除串", "串的朴素匹配"};
        do{
            cmd = UiCollection::choices("串测试菜单", 6, menuChoice,  false);
            switch (cmd){
                case 1:
                    cout << "请输入新建串的长度：";
                    cin >> len;
                    UiCollection::printLine();
                    temp = String<char>(len);
                    temp.rewrite(len);
                    lt.append(temp);
                    cout << "新串已添加！" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    cout << "已保存的串：" << endl;
                    try {
                        for(int index = 0; index < lt.length(); index++){
                            cout << index << ":";
                            lt.find(index)->data.printString();
                        }
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "请选择第一个串，输入一个已保存的串的索引：";
                    cin >> index;
                    cout << "请输入附加到上一个串后面的串的索引：";
                    cin >> index2;
                    try {
                        //将链接产生的新串添加到串库的末尾
                        temp = lt.find(index)->data.append(lt.find(index2)->data);
                        lt.append(temp);
                        cout << "产生的新串已添加！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "请输入要修改的串的索引：";
                    cin >> index;
                    cout << "请输入新串的长度：";
                    cin >> len;
                    UiCollection::printLine();
                    try {
                        lt.find(index)->data.rewrite(len);
                        cout << "修改完成！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "请输入要删除的串的索引：";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.removeByIndex(index);
                        cout << "删除成功！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    cout << "输入目标串的索引：";
                    cin >> index;
                    cout << "输入模式串的索引：";
                    cin >> index2;
                    try {
                        matchIndex = lt.find(index)->data.match(lt.find(index2)->data);
                        if(matchIndex==-1)cout << "匹配失败！" << endl;
                        else cout << "匹配成功！匹配位置为：" << matchIndex << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (cmd);
    }

protected:
    static int cmd;
    static List<String<char>> lt; //存放已保存的串的链表
};

//静态成员的初始化
int Menu7::cmd = 1;
List<String<char>> Menu7::lt(0);

#endif //DATASTRUCTURE_MENU7_H
