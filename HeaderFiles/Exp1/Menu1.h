//
// Created by 13592 on 2019/11/11.
/* ʵ��һ���Բ˵�
 * 2019.11.26 ����˵�����lt����Ŷ�����Ա�ʹ�ò˵�֧��ͬʱ�������˳���������
 */

#ifndef DATASTRUCTURE_MENU1_H
#define DATASTRUCTURE_MENU1_H

#include "../UiCollection.h"
#include "LinearTable.h"
#include "../Exp2/List.h"

class Menu1{
public:
    Menu1(){}

public:
    static void menu() {
        int lenOfTable, index, value, tableIndex, index2;
        LinearTable<int> temp;
        cout << "ʵ��һ" << endl << "�������Ա�" << endl;
        UiCollection::printLine();
        /*
        cout << "�������ĳ��ȣ�";
        cin >> lenOfTable;
        LinearTable<int> lt(lenOfTable);
        UiCollection::printLine();
         */

        string menuChoices[] = {"�½����Ա�", "ɾ����", "����Ԫ��", "ɾ��Ԫ��", "�����", "������б�", "���������ֵ"};
        do {
            cmd = UiCollection::choices("false", 7, menuChoices, false);
            switch (cmd) {
                case 1:
                    cout << "���������";
                    cin >> lenOfTable;
                    UiCollection::printLine();
                    temp = LinearTable<int>(lenOfTable);
                    lt.append(temp);
                    cout << "�½���ɣ�" << endl;
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 2:
                    cout << "������Ҫɾ����˳����������";
                    cin >> index;
                    UiCollection::printLine();
                    try {
                        lt.removeByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 3:
                    cout << "��ѡ��Ҫ��������Ա�����������������";
                    cin >> tableIndex;
                    cout << "����������λ�ã�";
                    cin >> index;
                    cout << "����������Ԫ��ֵ��";
                    cin >> value;
                    UiCollection::printLine();
                    try {
                        lt.find(tableIndex)->data.insert(index, value);
                        cout << "����ɹ���" << endl;
                    } catch (IndexOutException e) {
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 4:
                    cout << "��ѡ��Ҫɾ��Ԫ�ص����Ա�����������������";
                    cin >> tableIndex;
                    cout << "������Ҫɾ����Ԫ�ص��±꣺";
                    cin >> index;
                    try {
                        lt.find(tableIndex)->data.delByIndex(index);
                        cout << "ɾ���ɹ���" << endl;
                    } catch (IndexOutException e) {
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 5:
                    cout << "��ѡ��Ҫ����ı�����������������";
                    cin >> tableIndex;
                    UiCollection::printLine();
                    lt.find(tableIndex)->data.printTable();
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 6:
                    UiCollection::printLine();
                    cout << "�����ѱ���ı�Ϊ��" << endl;
                    try {
                        for(tableIndex = 0; tableIndex < lt.getLen(); tableIndex++){
                            lt.find(tableIndex)->data.printTable();
                        }
                    }catch (IndexOutException e){
                        e.print();
                    }catch (OverFlowException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;

                case 7:
                    /*
                    cout << "������Ҫ���������Ա����ţ�";
                    cin >> tableIndex;
                    cout << "�������һ��������±꣺";
                    cin >> index;
                    cout << "������ڶ���������±꣺";
                    cin >>index2;
                    UiCollection::printLine();
                    try {
                        lt.find(tableIndex)->data.swap(index, index2);
                        cout << "�����ɹ���" << endl;
                    }catch (IndexOutException e){
                        e.print();
                    }catch (NullPointer e){
                        e.print();
                    }
                    UiCollection::pause();
                    UiCollection::clear();
                    break;*/

                default:
                    break;
            }
        } while (cmd);
    }

private:
    static int cmd;
    static List<LinearTable<int>> lt;
};

//��̬��Ա�ĳ�ʼ��
int Menu1::cmd = 0;
List<LinearTable<int>> Menu1::lt(0);

#endif //DATASTRUCTURE_MENU1_H
