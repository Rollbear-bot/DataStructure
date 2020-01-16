//
// Created by 13592 on 2019/11/11.
// ʵ����˵�

#ifndef DATASTRUCTURE_MENU2_H
#define DATASTRUCTURE_MENU2_H

#include "../UiCollection.h"
#include "..//DsException.h"
#include "List.h"

class Menu2{
public:
    Menu2(){}

public:
    static void menu(){
        int lenOfList, index, value;
        cout << "ʵ���" << endl << "����������" << endl;
        UiCollection::printLine();
        cout << "����������ĳ��ȣ�";
        cin >> lenOfList;
        List<int> lt(lenOfList);

        string menuChoices[] = {"������", "ɾ�����", "���ҽ��", "�������", "��ȡ��", "�����ÿ�"};
        do{
            cmd = UiCollection::choices("false", 6, menuChoices, false);
            switch(cmd){
                case 1:
                    cout << "����������λ�ã�";
                    cin >> index;
                    cout << "����������Ԫ��ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.insert(index, value);
                        cout << "����ɹ���" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }catch (NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "������Ҫɾ����Ԫ�ص��±꣺";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.delByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "������Ҫ���ҵ��±꣺";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        cout << "���±��Ӧ��Ԫ��ֵΪ��";
                        cout << lt.find(index)->data << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NoFound e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    try {
                        lt.printList();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    UiCollection::printLine();
                    cout << "��Ϊ��" << lt.getLen() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::printLine();
                    lt.clear();
                    cout << "�ÿ���ɣ�" << endl;
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
int Menu2::cmd = 0;

#endif //DATASTRUCTURE_MENU2_H
