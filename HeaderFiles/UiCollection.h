#ifndef OPSYSTEM_UICOLLECTION_H
#define OPSYSTEM_UICOLLECTION_H

#include <iostream>
using namespace std;

class UiCollection{
public: //构造函数，无需初始化变量
    UiCollection()= default;

public: //以下为公有接口

    //输出分割线
    static void printLine(){
        cout<<"---------------------"<<endl;
    }


    //程序暂停
    static void pause(){
        int temp;
        printLine();
        cout << "输入任意指令返回菜单：" ;
        cin >> temp;
    }


    static void pauseAndClear(){
        pause();
        clear();
    }


    //输出选择列表，并返回用户输入的指令，处理非法指令与指令0（退出）
    static int choices(const string& title, int numOfChoices, string choiceMenu[], bool isMainMenu = false){
        int cmdInput;
        do{
            //首先输出可选指令列表
            printChoice(title, numOfChoices, choiceMenu, isMainMenu);
            //接收用户输入的指令，默认指令0为退出本级菜单
            cin >> cmdInput;
            //如果输入的指令在指令集中，则函数直接返回该指令
            for(int cmd = 0; cmd <= numOfChoices; cmd++){
                if(cmd == cmdInput) {
                    return cmd;
                }
            } //end for

            //未找到该指令，则要求重新输入
            clear();
            printLine();
            cout << "非法指令！" << endl <<"请重新输入！" << endl;
            printLine();
        }while(cmdInput);
        return 0;
    } //end define


    //清屏函数，通过换行100次来清屏
    static void clear(){
        for(int count = 0; count < 100; count++){
            cout << endl;
        }
    }


private: //以下私有功能模块
    //输出选择指引信息
    static void printChoice(const string& title, int numOfChoices, string choiceInfo[], bool isMainMenu = false){
        if(title != "false")cout << title << endl;
        printLine();
        for(int index = 0; index < numOfChoices; index++){
            cout<<index+1<<"：";
            cout<<choiceInfo[index]<<endl;
        }
        if(!isMainMenu){
            cout << "0：返回上一级菜单" << endl;
        }else{
            //若为主菜单，指令0应为退出系统
            cout << "0：退出系统" << endl;
        }
        printLine();
        cout << "请输入指令：" << endl;
    }
};

#endif //OPSYSTEM_UICOLLECTION_H