//
// Created by 13592 on 2019/11/11.
// 实验六：队列

#ifndef DATASTRUCTURE_MENU6_H
#define DATASTRUCTURE_MENU6_H

#include "Queue.h"

//实验六：队列
class Menu6{
public:
    Menu6(){}

public:
    static void menu(){
        int len, value;
        cout << "建立队列" << endl << "请输入队列的长度：";
        cin >> len;
        Queue<int> qe(len);
        string menuChoices[] = {"入队", "出队", "输出队列", "判空", "判满", "清空队列"};
        do{
            cmd = UiCollection::choices("队列测试", 6, menuChoices, false);
            switch(cmd){
                case 1:
                    cout << "请输入要入队的元素值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        qe.enter(value);
                        cout << "入队成功！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    try {
                        cout << "出队的元素值为：" << qe.quit() << endl;
                        cout << "出队成功！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    cout << "队列的内容为：" << endl;
                    qe.printQueue();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    if(qe.isEmpty())cout << "队空：是" << endl;
                    else cout << "队空：否" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    UiCollection::printLine();
                    if(qe.isFull())cout << "队满：是" << endl;
                    else cout << "队满：否" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::pause();
                    qe.clear();
                    cout << "队列置空完成！" << endl;
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
int Menu6::cmd = 0;


#endif //DATASTRUCTURE_MENU6_H
