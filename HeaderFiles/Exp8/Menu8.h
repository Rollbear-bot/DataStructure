//
// Created by 13592 on 2019/11/11.
// ʵ��ˣ���������ͼ



#ifndef DATASTRUCTURE_MENU8_H
#define DATASTRUCTURE_MENU8_H

#if 1

#include "../Others/FromTextbook/MinHeap.h"
#include "../Others/FromTextbook/BinaryTree.h"
#include "../Exp2/List.h"
#include "BinTreeByLinearTable.h"
#include"..//UiCollection.h"
#include "BinTreeByLink.h"

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

    //���������Բ˵�
    static void binTreeMenu(){
        int preCmd, index, value, len, choice;
        string GTable;
        List<char> outputList;


        BinTreeByLink<char> bt;
        cout << "0: ͨ��������������� 1:����ʽ����������" << endl;
        cin >> choice;
        if(choice){
            bt = BinTreeByLink<char>('#');
        } else {
            cout << "����������" << endl;
            cin >> GTable;
            bt = BinTreeByLink<char>(GTable);
        }

        cout << "�����������ɹ���" << endl;
        string menuChoice[] = {"���������������",
                               "���ǰ���������",
                               "��������������",
                               "��������������",
                               "ɾ�����",
                               "ͳ������",
                               "ͳ�����ڵ���",
                               "ͳ��Ҷ�ӽڵ���",
                               "��ȡĳ���ڵ������ֵ",
                               "չʾ�Ӹ��ڵ㵽ĳ���ڵ��·��"};
        do{
            preCmd = UiCollection::choices("���������Բ˵�", 10, menuChoice, false);
            switch (preCmd){
                case 1:
                    UiCollection::printLine();
                    try {
                        outputList = bt.layerTraversalWithoutRecursion();
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
                    //��һ��֧���쳣�������ں��������
                    UiCollection::printLine();
                    outputList = bt.preOrderTraversal();
                    cout << "ǰ��������Ϊ��" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    UiCollection::printLine();
                    outputList = bt.inOrderTraversal();
                    cout << "����������Ϊ��" << endl;
                    outputList.printList();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    UiCollection::printLine();
                    outputList = bt.postOrderTraversal();
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
                        bt.removeByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    cout << "����Ϊ��" << bt.height() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 7:
                    cout << "�ڵ���Ϊ��" << bt.numOfNodes() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 8:
                    cout << "Ҷ�ӽڵ���Ϊ��" << bt.numOfLeaves() << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 9:
                    cout << "������ýڵ�Ĳ������ţ����ڵ�����Ϊ1����";
                    cin >> index;
                    cout << "�ýڵ������ֵΪ��" << bt.getNodeValue(index) << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 10:
                    cout << "������ýڵ�Ĳ������ţ����ڵ�����Ϊ1����";
                    cin >> index;
                    cout << "·��Ϊ��" << bt.printPathFromRoot(index) << endl;
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


#endif

#endif //DATASTRUCTURE_MENU8_H
