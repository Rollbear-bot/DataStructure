//
// Created by 13592 on 2019/11/11.
// ϵͳ��

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

//ϵͳ��Ϣ
#define author "Wu Junhong"
#define Date "2020.02.20"

#include <iostream>
#include "UiCollection.h"
using namespace std;

/*ϵͳ��
 * �ṩ�����˵�
 * */
class TestSystem{
public:
    TestSystem(){}

public:
    //��ӭ����
    static void welcome(){
        cout << "���ݽṹ����ϵͳ" << endl;
        UiCollection::printLine();
        cout << "By " << author << " " << Date << endl;
        UiCollection::printLine();
    }

    //���˵���ѡ���½�
    static void mainMenu(){
        cmd = 0;
        string mainMenu[] = {"ʵ��һ�����Ա��˳���ʾ��ʵ��",
                             "ʵ��������Ա�����ӱ�ʾ��ʵ��",
                             "ʵ������ѭ������˫�������뾲̬����",
                             "ʵ���ģ�����ʽ����",
                             "ʵ���壺˳��ջ����ջ�Ļ��������㷨",
                             "ʵ���������еĻ��������㷨",
                             "ʵ���ߣ�˳�򴮵Ļ��������㷨",
                             "ʵ��ˣ��������Ļ���������������������",
                             "ʵ��ţ������������������Ļ����������������ͱ���",
                             "ʵ��ʮ�������ṹ",
                             "ʵ��ʮһ��ͼ����"};
        do{
            cmd = UiCollection::choices("������Ҫ���Ե��½�ѡ�", 11, mainMenu, true);
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

//��̬��Ա�ĳ�ʼ��
int TestSystem::cmd = 0;


#endif //DATASTRUCTURE_TESTSYSTEM_H
