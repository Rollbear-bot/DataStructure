//
// Created by 13592 on 2019/11/11.
// ���˵�

#if 1
#include "../HeaderFiles/TestSystem.h"

int main(){
    try {
        //��ӭ����
        TestSystem::welcome();
        //�������˵�
        TestSystem::mainMenu();
    }catch(exception &e) {
        cout << e.what() << endl;
    }
}

#endif
