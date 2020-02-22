//
// Created by 13592 on 2019/11/11.
// 主菜单

#if 1
#include "../HeaderFiles/TestSystem.h"

int main(){
    try {
        //欢迎界面
        TestSystem::welcome();
        //启动主菜单
        TestSystem::mainMenu();
    }catch(exception &e) {
        cout << e.what() << endl;
    }
}

#endif
