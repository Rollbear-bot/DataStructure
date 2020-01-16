//
// Created by 13592 on 2019/11/11.
// ������ʵ��

#ifndef DATASTRUCTURE_MENU3_H
#define DATASTRUCTURE_MENU3_H

#include "../UiCollection.h"
#include "CircleList.h"
#include "DoubleLinkedList.h"

//ʵ������ѭ��������˫������
class Menu3{
public:
    Menu3(){}

public:
    static void menu(){
        int index, value, len;
        string choi[] = {"ѭ���������", "˫���������"};
        do{
            cmd = UiCollection::choices("ʵ������ѭ��������˫������", 2, choi, false);
            switch(cmd){
                case 1:
                    listMenu<CircleList<int>>();
                    break;

                case 2:
                    listMenu<DoubleLinkedList<int>>();
                    break;

                default:
                    break;
            }
        }while (cmd);

    }

private:
    //ʹ�ú���ģ����ͳһ����ѭ�������˫������
    template<class Type>
    static void listMenu(){
        int preCmd, index, value, len;
        cout << "��������" << endl << "����������ĳ��ȣ�";
        cin >> len;
        UiCollection::printLine();
        Type lt(len);
        string menuChoices[] = {"������", "ɾ�����", "�������", "�޸Ľ���ֵ", "�������"};
        do{
            preCmd = UiCollection::choices("false", 5, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "����������λ�ã�";
                    cin >> index;
                    cout << "������Ҫ�����Ԫ�ص�ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.insert(index, value);
                        cout << "����ɹ���" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "������Ҫɾ���Ľ����±꣺";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.delByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    lt.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "������Ҫ�޸ĵĽ����±꣺";
                    cin >> index;
                    cout << "�������޸ĺ�Ľ���ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.alter(index, value);
                        cout << "�޸ĳɹ���" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "������Ҫ�������±꣺";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        cout << "���±��Ӧ�Ľ���ֵΪ��" << lt.find(index)->data << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (preCmd);
    }
/*
    static void DLLMenu(){
        int preCmd, index, value, len;
        cout << "����˫������" << endl << "����������ĳ��ȣ�";
        cin >> len;
        UiCollection::printLine();
        DoubleLinkedList<int> dll(len);
        string menuChoices[] = {"������", "ɾ�����", "�������", "�޸Ľ���ֵ", "�������"};
        do{
            preCmd = UiCollection::choices("˫��������Բ˵�", 5, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "����������λ�ã�";
                    cin >> index;
                    cout << "������Ҫ�����Ԫ�ص�ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        dll.insert(index, value);
                        cout << "����ɹ���" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "������Ҫɾ���Ľ����±꣺";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        dll.delByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    dll.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "������Ҫ�޸ĵĽ����±꣺";
                    cin >> index;
                    cout << "�������޸ĺ�Ľ���ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        dll.alter(index, value);
                        cout << "�޸ĳɹ���" << endl;
                    }catch(IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "������Ҫ�������±꣺";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        cout << "���±��Ӧ�Ľ���ֵΪ��" << dll.find(index)->data << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (preCmd);
    }
*/
    static int cmd;
};

//��̬��Ա�ĳ�ʼ��
int Menu3::cmd = 0;

#endif //DATASTRUCTURE_MENU3_H
