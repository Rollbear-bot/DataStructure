//
// Created by 13592 on 2019/11/11.
// 实验五：栈与链栈

#ifndef DATASTRUCTURE_MENU5_H
#define DATASTRUCTURE_MENU5_H

#include "../UiCollection.h"
#include "LinkedStack.h"
#include "Stack.h"

//实验五：栈与链栈
class Menu5{
public:
    Menu5(){}

public:
    static void menu(){
        string menuChoices[] = {"栈测试", "链栈测试"};
        do{
            cmd = UiCollection::choices("实验五：栈与链栈", 2, menuChoices, false);
            switch (cmd){
                case 1:
                    stackMenu<Stack<int>>();
                    break;

                case 2:
                    stackMenu<LinkedStack<int>>();
                    break;

                default:
                    break;
            }
        }while (cmd);
    }

private:
    //栈测试菜单：使用函数模板实现
    template <class Type>
    static void stackMenu(){
        int preCmd, len, index, value;
        string menuChoices[] = {"入栈", "出栈", "输出栈", "栈置空", "输出栈中元素个数", "输出栈深", "判空", "判满"};
        cout << "建立栈" << endl << "请输入栈深：";
        cin >> len;
        Type st(len);
        do{
            preCmd = UiCollection::choices("false", 8, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "请输入入栈的元素的值：";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        st.push(value);
                        cout << "入栈成功！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    try {
                        cout << "出栈的元素是：" << st.pop() << endl;
                        cout << "出栈成功！" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    cout << "栈中的元素为：" << endl;
                    try {
                        st.printStack();
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    st.clear();
                    cout << "置空完成！" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    UiCollection::printLine();
                    cout << "栈中的元素个数为：" << st.getEleNum() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::printLine();
                    cout << "栈深为：" << st.getMaxLen() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 7:
                    UiCollection::printLine();
                    if(st.isEmpty()) cout << "栈空：是" << endl;
                    else cout << "栈空：否" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 8:
                    UiCollection::printLine();
                    if(st.isFull()) cout << "栈满：是" << endl;
                    else cout << "栈满：否" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;

            } //end switch
        }while (preCmd);
    }

    static int cmd;
};

//静态成员初始化
int Menu5::cmd = 0;

#endif //DATASTRUCTURE_MENU5_H
