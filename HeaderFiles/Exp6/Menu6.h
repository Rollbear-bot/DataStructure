//
// Created by 13592 on 2019/11/11.
// ʵ����������

#ifndef DATASTRUCTURE_MENU6_H
#define DATASTRUCTURE_MENU6_H

#include "Queue.h"

//ʵ����������
class Menu6{
public:
    Menu6(){}

public:
    static void menu(){
        int len, value;
        cout << "��������" << endl << "��������еĳ��ȣ�";
        cin >> len;
        Queue<int> qe(len);
        string menuChoices[] = {"���", "����", "�������", "�п�", "����", "��ն���"};
        do{
            cmd = UiCollection::choices("���в���", 6, menuChoices, false);
            switch(cmd){
                case 1:
                    cout << "������Ҫ��ӵ�Ԫ��ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        qe.enter(value);
                        cout << "��ӳɹ���" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    try {
                        cout << "���ӵ�Ԫ��ֵΪ��" << qe.quit() << endl;
                        cout << "���ӳɹ���" << endl;
                    }catch (exception &e){
                        cout << e.what() << endl;
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    cout << "���е�����Ϊ��" << endl;
                    qe.printQueue();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    if(qe.isEmpty())cout << "�ӿգ���" << endl;
                    else cout << "�ӿգ���" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    UiCollection::printLine();
                    if(qe.isFull())cout << "��������" << endl;
                    else cout << "��������" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::pause();
                    qe.clear();
                    cout << "�����ÿ���ɣ�" << endl;
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

//��̬��Ա�ĳ�ʼ��
int Menu6::cmd = 0;


#endif //DATASTRUCTURE_MENU6_H
