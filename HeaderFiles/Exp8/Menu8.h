//
// Created by 13592 on 2019/11/11.
// ʵ��ˣ���������ͼ

#ifndef DATASTRUCTURE_MENU8_H
#define DATASTRUCTURE_MENU8_H

#include "../Others/FromTextbook/MinHeap.h"
#include "../Others/FromTextbook/BinaryTree.h"
#include "../Exp2/List.h"
#include "BinTreeByLinearTable.h"
#include"..//UiCollection.h"

class Menu8{
public:
    Menu8(){}

public:
    static void menu(){
        string menuChoices[] = {"�Ѳ���", "����������"};
        do{
            cmd = UiCollection::choices("ʵ���", 2, menuChoices, false);
            switch(cmd){
                case 1:
                    heapMenu();
                    break;

                case 2:
                    binTreeMenu();
                    break;

                default:
                    break;
            }
        }while(cmd);
    }

public:
    //�Ѳ��Բ˵�
    static void heapMenu(){
        int preCmd, value = 0, len, carrier = 0;
        int arr[] = {1};
        cout << "�Ƚ�����" << endl << "������ѵ����������";
        cin >> len;
        MinHeap<int> mp(arr, len);
        for(int index = 0; index < len; index++){
            cout << "�������" << index+1 << "��Ԫ�أ�";
            cin >> value;
            mp.alter(index, value);
        }
        string menuChoices[] = {"����Ԫ��", "ɾ��Ԫ��", "�����"};
        do{
            preCmd = UiCollection::choices("�Ѳ��Բ˵�", 3, menuChoices, false);
            switch(preCmd){
                case 1:
                    cout << "������Ҫ�����Ԫ��ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    mp.Insert(value);
                    cout << "����ɹ���" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    UiCollection::printLine();
                    mp.RemoveMin(carrier);
                    cout << "������ֵΪ��" << carrier << endl;
                    cout << "ɾ���ɹ���" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    mp.printHeap();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                default:
                    break;
            }
        }while (preCmd);
    }

    //���������Բ˵���˳���ʵ��
    static void binTreeMenu(){
        int preCmd, index, value, len;
        List<int> inputList(0), outputList;

        /*
        cout << "��������˳���ʵ�֣�����" << endl << "���Ƚ�����" << endl;
        UiCollection::printLine();
        cout << "������Ҫ�����Ԫ�صĸ�����";
        cin >> len;
        UiCollection::printLine();
        for(index = 0; index < len; index++){
            cout << "�������" << index+1 << "��Ԫ�أ�";
            cin >> value;
            inputList.append(value);
        }
        //ʹ�������Ԫ�����������������
         */

        //test
        int arr[] = {1,2,3,4,5,6,7,8};
        inputList = List<int>(8,arr);
        BinTreeByLinearTable<int> bt(inputList);

        cout << "�����������ɹ���" << endl;
        string menuChoice[] = {"���������������", "���ǰ���������", "��������������", "��������������", "ɾ�����"};
        do{
            preCmd = UiCollection::choices("���������Բ˵���˳���ʵ��", 5, menuChoice, false);
            switch (preCmd){
                case 1:
                    UiCollection::printLine();
                    try {
                        outputList = bt.levelVisit();
                        cout << "��������Ϊ��" << endl;
                        outputList.printList();
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    //��һ��֧���쳣�������ڽӿ������
                    UiCollection::printLine();
                    outputList = bt.preVisit();
                    cout << "ǰ��������Ϊ��" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    outputList = bt.inVisit();
                    cout << "����������Ϊ��" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    outputList = bt.postVisit();
                    cout << "����������Ϊ��" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "������Ҫɾ���Ľ��Ĳ����������";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        bt.delByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
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

    static int cmd;
};

//��̬��Ա�ĳ�ʼ��
int Menu8::cmd = 0;

#endif //DATASTRUCTURE_MENU8_H