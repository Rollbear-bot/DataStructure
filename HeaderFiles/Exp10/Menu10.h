//
// Created by 13592 on 2019/11/11.
// ʵ��ʮ�������ṹ

#ifndef DATASTRUCTURE_MENU10_H
#define DATASTRUCTURE_MENU10_H

#include "staticSearch.h"

class Menu10{
public:
    Menu10(){}
    static void menu(){
        //���õ�һЩ����
        int len, value, index;
        cout << "�Ƚ�����̬������" << endl << "���������";
        cin >> len;
        StaticSrhTable<int> sst(len);
        for(index = 0; index < len; index++){
            cout << "�������" << index+1 << "��Ԫ�أ�";
            cin >> value;
            sst.append(value);
        }
        sst.insertSort();
        string menuChoices[] = {"�����", "���ֲ���", "˳�����"};
        do{
            cmd = UiCollection::choices("��̬���������", 3, menuChoices, false);
            switch (cmd){
                case 1:
                    sst.printTable();
                    break;

                case 2:
                    cout << "��������ҵ�Ԫ�أ�";
                    cin >> value;
                    try {
                        index = sst.binarySearch(value);
                        cout << "���ҳɹ��������ҵ�Ԫ��λ������" << index << endl;
                    }catch(NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "��������ҵ�Ԫ�أ�";
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
